
/*
* 虚假编译器 VC 6.6.666 (Virtual Compiler 6.6.666)
*
* @author zhongjie mo
* @21/3/2024
*
* ——————声明———————
* 程序基于C语言
* 运行环境为Microsoft Visual Studio Community 2022 (64 位) - Current  版本 17.9.1
*
* ——————主要功能及缺陷———————
* 不支持指针及指针相关操作
* 支持struct及struct数组,但由于'{'、'}'的可能省略,部分结构体初始化可能与vs2022有出入
* 支持int、float、char类型及数组,支持字符串,支持void（函数返回值部分）
* 支持变量初始化判定
* 支持全局变量、局部变量、多层局部变量 
* 支持简单的头文件判定
* 不支持++/--
* 支持检测未定义的变量与函数名
*支持检测函数实参、形参一致性 
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <setjmp.h> 
#include <stdbool.h>

#define maxsize 300
#define line    50			//申请的行数（链表数）
#define capacity 200		
#define stack_size 30
#define var_size 30
#define mem_size 10
#define type_size 20
#define	Is_type()  (Kw_char<=pcur->KwCode&&Kw_float>=pcur->KwCode)
#define Is_fit_type(a) ((!strcmp((*p)->type,a)))		//处理结构体内部成员用
#define Is_this(a)  (a == pcur->KwCode)

typedef enum  Key_Word_Code {
	/* 运算符及分隔符 */
	Kw_plus,		// + 加号
	Kw_minus,		// - 减号
	Kw_star,		// * 星、乘号
	Kw_divide,		// / 除号
	Kw_mod,			// % 求余运算符
	Kw_eq,			// == 等于号
	Kw_neq,			// != 不等于号
	Kw_lt,			// < 小于号
	Kw_leq,			// <= 小于等于号
	Kw_gt,			// > 大于号
	Kw_geq,			// >= 大于等于号
	Kw_assign,		// = 赋值运算符
	Kw_not,			// !  逻辑非运算符
	Kw_and,			// && 逻辑与运算符
	Kw_or,			// || 逻辑或运算符

	Kw_addr,		// & 取地址、与运算符
	Kw_pointsto,	// -> 指向结构体成员运算符
	Kw_dot,			// . 结构体成员运算符
	Kw_openpa,		// ( 左圆括号
	Kw_closepa,		// ) 右圆括号
	Kw_openbr,		// [ 左中括号
	Kw_closebr,		// ] 右中括号
	Kw_begin,		// { 左大括号
	Kw_end,			// } 右大括号
	Kw_semicolon,	// ; 分号 
	Kw_comma,		// , 逗号
	Kw_hash,		// # 号
	Kw_eof,			// 文件结束符



	/* 常量 */
	Kw_cchar,		// 字符常量
	Kw_cint,		// 整型常量
	Kw_cfloat,		// 浮点型常量	
	Kw_cstr,		// 字符串常量

	/* 关键字 */
	Kw_char,		// char关键字
	Kw_int,			// int关键字
	Kw_float,		// float关键字
	Kw_void,		// void关键字 
	Kw_struct,		// struct关键字
	Kw_if,			// if关键字
	Kw_else,		// else关键字
	Kw_for,			// for关键字
	Kw_while,		// while关键字
	Kw_continue,	// continue关键字
	Kw_break,		// break关键字
	Kw_return,		// return关键字
	Kw_include,		//include关键字

	Kw_notes,		//注释标记
	Kw_space,		//空格
	Kw_tabs,		//制表符

	/* 标识符 */
	Kw_identv,		//变量名
	Kw_identf		//函数名
}Key_Word_Code;



typedef struct Key_Word {			//存储单词结构
	struct Key_Word* prior;			//指向前一个单词
	int KwCode;						//单词编码
	char spell[capacity];			//单词字符串
	struct Key_Word* next;			//指向哈希冲突的其他单词，或指向同一行的下一个单词
	int row_tail_flag;
}Key_Word;

typedef struct words {
	int count;						//容量
	int row;						//已使用几行
	Key_Word** list;		//一行内存放的单词链表
}words;

typedef struct member {					//结构体内部成员
	char word[var_size];				//每行存放一个变量
	char type[type_size];							//变量的类型(int、float、char)
	int array_flag;						//是否为数组
	int array_count;					//若是数组，其容量
	int init_flag;						//是否已初始化
	int* part_init;						//其余数组成员是否已初始化
	struct member* next;				//结构体成员指针
}member;

typedef struct {						//	结构体数组其余成员
	int* init_flag;
	member** mem;						//其余结构体的内部成员
}array_next;

typedef struct {				//存放声明的变量，标记其是否已经初始化
	int count;							//容量
	int row;							//已使用几行
	char(*word)[var_size];				//每行存放一个变量(此为空，不存在或是结构体声明。不为空，即为变量)
	char(*type)[type_size];				//变量的类型(char、int、float、struct ^)
	int* array_flag;					//是否为数组
	int* array_count;					//若是数组，其容量
	int* init_flag;						//是否已初始化(对非struct变量（不包含struct数组）来说)
	member** mem;						//结构体成员指针数组
	array_next** part;					//数组/结构体数组其余成员
	int* grade;							//若是局部变量，实在函数体内的第几层{}定义的
}variable;


typedef struct parameter {					//函数内部参数
	char word[var_size];				//参数名
	char type[type_size];				//参数的类型(int、float、char)
	int array_flag;						//是否为数组
	int array_count;					//若是数组，其容量
	member* mem;						//结构体成员指针
	struct parameter* next;				//下一个参数
}parameter;

typedef struct {						//存放声明的函数
	int count;							//容量
	int row;							//已使用几行
	int* is_define;						//函数定义还是函数声明
	char(*word)[var_size];				//每行存放一个函数名
	char(*type)[type_size];				//函数返回值类型(暂时只支持char、int、float、void)
	parameter** para;						//参数
}function;


jmp_buf jmpbuf;
int JmpJud;//是否编译成功的标志
extern int row;
extern int main_flag;		//main函数是否已出现,用来判断include是否在main函数之前

enum Error_type {				//从1开始
	program_start,

	func_undefined,				//使用未知函数
	func_repeat_definition,		//重复定义函数
	var_undefined,				//使用未定义变量
	var_uninitialzed,			//使用未初始化变量
	var_repeat_definition,		//重复定义变量

	lack_parameter,				//缺少参数
	lack_openpa,				//缺少左圆括号
	lack_closepa,				//缺少右圆括号
	lack_openbr,				//缺少左中括号
	lack_closebr,				//缺少右中括号
	lack_begin,					//缺少左花括号
	lack_end,					//缺少右花括号
	lack_semicolon,				//缺少分号
	lack_if,					//else或else if使用错误
	lack_expression,			//缺乏表达式
	lack_quotation_mark,		//缺少引号
	lack_dquotation_mark,		//缺少双引号
	lack_space,					//缺少空格
	lack_identv,				//缺少变量名
	lack_identf,				//缺少函数名
	lack_value,					//丢失精确数据

	type_error,					//变量类型不一致		
	array_error,				//数组错误(不完整)
	struct_error,				//结构体错误
	expression_error,			//错误的表达式
	func_parameter_error,		//函数的参数不一致
	func_define_error,			//函数内部参数不合规范
	continue_use_error,			//continue使用场景错误
	break_use_error,			//break使用场景错误
	return_error,				//return类型错误				（若函数未声明类型，默认返回值为int）
	headfile_error,				//头文件引用错误
	main_error,					//主函数返回值类型不是int
	para_type_error,			//参数类型错误

	init_value_more,				//初始值设定项过多
	unknown_struct_type,			//未知的结构体类型
	struct_lack_mem,				//结构体内部缺少成员变量
	repeat_struct_statement,		//重复的结构体声明
	need_Kw_begin_Kw_end,			//需要带大括号的表达式
	statememnt_should_front,		//函数声明应放在main函数之前
	para_too_more,					//函数传递参数过多
	para_too_less					//函数传递参数过少
};



//----------------------------词法分析函数------------------------------------
void Inithashtable(Key_Word keywords[], int kw_length, Key_Word* kword_hashtable[]);
int elf_hash(char* key);
void word_storage(words* array);
void word_split(words* array, Key_Word* kword_hashtable[]);
void word_expand(words* array);
void printf_words(words* array);
void printf_color(Key_Word* x);
void print_hashtable(Key_Word* kword_hashtable[]);
void grammar_clear(words array, variable* pvar, variable* pvar_in, function* pfunc);
void External_dec(variable* pvar, variable* pvar_in, function* pfunc);
void variable_storage(variable* var);//存储出现的变量或结构体声明
void variable_expand(variable* var);//空间不够扩容

//-----------------------------语法分析函数------------------------------------
bool have_space_judge();
void next_node();
void quote_dispose();
void struct_dispose(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag);
void struct_array_part_storage(variable* pvar);
void same_struct_mem_copy(variable* pvar, int k);
void struct_mem_array_part_storage(member* temp);




bool statement_valid_ok_judge(variable* pvar);
bool identv_valid_ok_judge(variable* pnow);
int repeat_judge(variable* pvar);
member* struct_mem_repeat_judge(variable* pvar, int posi);
void struct_statement(variable* pvar, variable* pvar_in, function* pfunc, member* temp, int in_func_flag);
void struct_statement_one(variable* pvar, variable* pvar_in, function* pfunc, member* temp, Key_Word* memo, int in_func_flag);
void struct_statement_two(variable* pvar, variable* pvar_in, function* pfunc, int from, member* temp, Key_Word* memo, int in_func_flag);
void struct_init(variable* pvar, variable* pvar_in, function* pfunc, int from, int assign, int in_func_flag);
void struct_mem_init(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag);
void struct_mem_init_one(variable* pvar, variable* pvar_in, function* pfunc, member** p, int in_func_flag);
void struct_mem_init_two(variable* pvar, variable* pvar_in, function* pfunc, member** p, int count, int flag, int in_func_flag);
void struct_mem_init_three(variable* pvar, variable* pvar_in, function* pfunc, member** p, int count, int from, int flag, int in_func_flag);
void struct_rest_mem(member* rest);
void struct_mem_array_part(member* p);

void Is_init_too_more(int flag);
void Is_init_more(int flag);

void more_struct_mem_init(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag);
void more_struct_mem_init_one(variable* pvar, variable* pvar_in, function* pfunc, member** p, int* pi, int exchange, int in_func_flag);
void more_struct_mem_init_two(variable* pvar, variable* pvar_in, function* pfunc, member** p, int count, int* pi, int flag, int exchange, int in_func_flag);
void more_struct_mem_init_three(variable* pvar, variable* pvar_in, function* pfunc, member** p, int count, int* pi, int from, int flag, int exchange, int in_func_flag);



void type_dispose(variable* pvar, variable* pvar_in, function* pfunc);
void function_storage(function* pfunc);//存放声明的函数
void function_expand(function* pfunc);//空间不够扩容
int have_func_define(function* pfunc, int pos);
parameter* have_func_var(function* pfunc);
int have_identv(variable* pnow);
member* parameter_mem_repeat_judge(parameter* pfunc_var);
bool cmp_para(function* pfunc, variable* pnow);

void function_handle(variable* pvar, variable* pvar_in, function* pfunc, Key_Word* memo, int in_func_flag);
int have_func_statement(function* pfunc, int pos);
void parameter_handle(variable* pvar, function* pfunc, parameter* temp);
bool parameter_name_examine(function* pfunc, int pos);

void identv_array_part_storage(variable* pvar);
void identv_statement_one(variable* pvar, variable* pvar_in, function* pfunc, Key_Word* memo, int in_func_flag);
void identv_statement_two(variable* pvar, variable* pvar_in, function* pfunc, int from, Key_Word* memo, int assign, int in_func_flag);


void more_identv_init(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag);
void more_identv_init_one(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag);
void more_identv_init_two(variable* pvar, variable* pvar_in, function* pfunc, int count, int flag, int in_func_flag);
void more_identv_init_three(variable* pvar, variable* pvar_in, function* pfunc, int count, int from, int flag, int in_func_flag);
void identv_array_part_init(variable* pvar);



void expression(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag);
void seventh(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag);
void sixth(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag);
void fifth(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag);
void fourth(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag);
void third(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag);
void second(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag, int from);
void in_func_first(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag, int from);
int top_first(variable* pvar);

void func_type(variable* pvar, variable* pvar_in, function* pfunc, Key_Word* memo, int in_func_flag);
void func_other(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag);


int string_value(char* str);

void  out_func_first(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag, int from);

void function_body(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag);
void identv_dispose(variable* pvar);
void identv_one(variable* pvar);
void func_identv(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag);
int exist_func(function* pfunc);
void func_identf(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag);
void case_comma(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag);
void func_return(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag);
void func_while(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag);
void func_while_or_for_body_one(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag);
void func_while_or_for_body_two(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag);
void func_for(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag);
void func_if(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag);
void func_else_if(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag);
void func_if_else_body_one(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag);
void func_if_else_body_two(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag);
void destroy_var(variable* pvar_in, int grade);
