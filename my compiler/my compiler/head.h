
/*
* ��ٱ����� VC 6.6.666 (Virtual Compiler 6.6.666)
*
* @author zhongjie mo
* @21/3/2024
*
* ������������������������������
* �������C����
* ���л���ΪMicrosoft Visual Studio Community 2022 (64 λ) - Current  �汾 17.9.1
*
* ��������������Ҫ���ܼ�ȱ�ݡ�������������
* ��֧��ָ�뼰ָ����ز���
* ֧��struct��struct����,������'{'��'}'�Ŀ���ʡ��,���ֽṹ���ʼ��������vs2022�г���
* ֧��int��float��char���ͼ�����,֧���ַ���,֧��void����������ֵ���֣�
* ֧�ֱ�����ʼ���ж�
* ֧��ȫ�ֱ������ֲ����������ֲ����� 
* ֧�ּ򵥵�ͷ�ļ��ж�
* ��֧��++/--
* ֧�ּ��δ����ı����뺯����
*֧�ּ�⺯��ʵ�Ρ��β�һ���� 
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <setjmp.h> 
#include <stdbool.h>

#define maxsize 300
#define line    50			//�������������������
#define capacity 200		
#define stack_size 30
#define var_size 30
#define mem_size 10
#define type_size 20
#define	Is_type()  (Kw_char<=pcur->KwCode&&Kw_float>=pcur->KwCode)
#define Is_fit_type(a) ((!strcmp((*p)->type,a)))		//����ṹ���ڲ���Ա��
#define Is_this(a)  (a == pcur->KwCode)

typedef enum  Key_Word_Code {
	/* ��������ָ��� */
	Kw_plus,		// + �Ӻ�
	Kw_minus,		// - ����
	Kw_star,		// * �ǡ��˺�
	Kw_divide,		// / ����
	Kw_mod,			// % ���������
	Kw_eq,			// == ���ں�
	Kw_neq,			// != �����ں�
	Kw_lt,			// < С�ں�
	Kw_leq,			// <= С�ڵ��ں�
	Kw_gt,			// > ���ں�
	Kw_geq,			// >= ���ڵ��ں�
	Kw_assign,		// = ��ֵ�����
	Kw_not,			// !  �߼��������
	Kw_and,			// && �߼��������
	Kw_or,			// || �߼��������

	Kw_addr,		// & ȡ��ַ���������
	Kw_pointsto,	// -> ָ��ṹ���Ա�����
	Kw_dot,			// . �ṹ���Ա�����
	Kw_openpa,		// ( ��Բ����
	Kw_closepa,		// ) ��Բ����
	Kw_openbr,		// [ ��������
	Kw_closebr,		// ] ��������
	Kw_begin,		// { �������
	Kw_end,			// } �Ҵ�����
	Kw_semicolon,	// ; �ֺ� 
	Kw_comma,		// , ����
	Kw_hash,		// # ��
	Kw_eof,			// �ļ�������



	/* ���� */
	Kw_cchar,		// �ַ�����
	Kw_cint,		// ���ͳ���
	Kw_cfloat,		// �����ͳ���	
	Kw_cstr,		// �ַ�������

	/* �ؼ��� */
	Kw_char,		// char�ؼ���
	Kw_int,			// int�ؼ���
	Kw_float,		// float�ؼ���
	Kw_void,		// void�ؼ��� 
	Kw_struct,		// struct�ؼ���
	Kw_if,			// if�ؼ���
	Kw_else,		// else�ؼ���
	Kw_for,			// for�ؼ���
	Kw_while,		// while�ؼ���
	Kw_continue,	// continue�ؼ���
	Kw_break,		// break�ؼ���
	Kw_return,		// return�ؼ���
	Kw_include,		//include�ؼ���

	Kw_notes,		//ע�ͱ��
	Kw_space,		//�ո�
	Kw_tabs,		//�Ʊ��

	/* ��ʶ�� */
	Kw_identv,		//������
	Kw_identf		//������
}Key_Word_Code;



typedef struct Key_Word {			//�洢���ʽṹ
	struct Key_Word* prior;			//ָ��ǰһ������
	int KwCode;						//���ʱ���
	char spell[capacity];			//�����ַ���
	struct Key_Word* next;			//ָ���ϣ��ͻ���������ʣ���ָ��ͬһ�е���һ������
	int row_tail_flag;
}Key_Word;

typedef struct words {
	int count;						//����
	int row;						//��ʹ�ü���
	Key_Word** list;		//һ���ڴ�ŵĵ�������
}words;

typedef struct member {					//�ṹ���ڲ���Ա
	char word[var_size];				//ÿ�д��һ������
	char type[type_size];							//����������(int��float��char)
	int array_flag;						//�Ƿ�Ϊ����
	int array_count;					//�������飬������
	int init_flag;						//�Ƿ��ѳ�ʼ��
	int* part_init;						//���������Ա�Ƿ��ѳ�ʼ��
	struct member* next;				//�ṹ���Աָ��
}member;

typedef struct {						//	�ṹ�����������Ա
	int* init_flag;
	member** mem;						//����ṹ����ڲ���Ա
}array_next;

typedef struct {				//��������ı�����������Ƿ��Ѿ���ʼ��
	int count;							//����
	int row;							//��ʹ�ü���
	char(*word)[var_size];				//ÿ�д��һ������(��Ϊ�գ������ڻ��ǽṹ����������Ϊ�գ���Ϊ����)
	char(*type)[type_size];				//����������(char��int��float��struct ^)
	int* array_flag;					//�Ƿ�Ϊ����
	int* array_count;					//�������飬������
	int* init_flag;						//�Ƿ��ѳ�ʼ��(�Է�struct������������struct���飩��˵)
	member** mem;						//�ṹ���Աָ������
	array_next** part;					//����/�ṹ�����������Ա
	int* grade;							//���Ǿֲ�������ʵ�ں������ڵĵڼ���{}�����
}variable;


typedef struct parameter {					//�����ڲ�����
	char word[var_size];				//������
	char type[type_size];				//����������(int��float��char)
	int array_flag;						//�Ƿ�Ϊ����
	int array_count;					//�������飬������
	member* mem;						//�ṹ���Աָ��
	struct parameter* next;				//��һ������
}parameter;

typedef struct {						//��������ĺ���
	int count;							//����
	int row;							//��ʹ�ü���
	int* is_define;						//�������廹�Ǻ�������
	char(*word)[var_size];				//ÿ�д��һ��������
	char(*type)[type_size];				//��������ֵ����(��ʱֻ֧��char��int��float��void)
	parameter** para;						//����
}function;


jmp_buf jmpbuf;
int JmpJud;//�Ƿ����ɹ��ı�־
extern int row;
extern int main_flag;		//main�����Ƿ��ѳ���,�����ж�include�Ƿ���main����֮ǰ

enum Error_type {				//��1��ʼ
	program_start,

	func_undefined,				//ʹ��δ֪����
	func_repeat_definition,		//�ظ����庯��
	var_undefined,				//ʹ��δ�������
	var_uninitialzed,			//ʹ��δ��ʼ������
	var_repeat_definition,		//�ظ��������

	lack_parameter,				//ȱ�ٲ���
	lack_openpa,				//ȱ����Բ����
	lack_closepa,				//ȱ����Բ����
	lack_openbr,				//ȱ����������
	lack_closebr,				//ȱ����������
	lack_begin,					//ȱ��������
	lack_end,					//ȱ���һ�����
	lack_semicolon,				//ȱ�ٷֺ�
	lack_if,					//else��else ifʹ�ô���
	lack_expression,			//ȱ�����ʽ
	lack_quotation_mark,		//ȱ������
	lack_dquotation_mark,		//ȱ��˫����
	lack_space,					//ȱ�ٿո�
	lack_identv,				//ȱ�ٱ�����
	lack_identf,				//ȱ�ٺ�����
	lack_value,					//��ʧ��ȷ����

	type_error,					//�������Ͳ�һ��		
	array_error,				//�������(������)
	struct_error,				//�ṹ�����
	expression_error,			//����ı��ʽ
	func_parameter_error,		//�����Ĳ�����һ��
	func_define_error,			//�����ڲ��������Ϲ淶
	continue_use_error,			//continueʹ�ó�������
	break_use_error,			//breakʹ�ó�������
	return_error,				//return���ʹ���				��������δ�������ͣ�Ĭ�Ϸ���ֵΪint��
	headfile_error,				//ͷ�ļ����ô���
	main_error,					//����������ֵ���Ͳ���int
	para_type_error,			//�������ʹ���

	init_value_more,				//��ʼֵ�趨�����
	unknown_struct_type,			//δ֪�Ľṹ������
	struct_lack_mem,				//�ṹ���ڲ�ȱ�ٳ�Ա����
	repeat_struct_statement,		//�ظ��Ľṹ������
	need_Kw_begin_Kw_end,			//��Ҫ�������ŵı��ʽ
	statememnt_should_front,		//��������Ӧ����main����֮ǰ
	para_too_more,					//�������ݲ�������
	para_too_less					//�������ݲ�������
};



//----------------------------�ʷ���������------------------------------------
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
void variable_storage(variable* var);//�洢���ֵı�����ṹ������
void variable_expand(variable* var);//�ռ䲻������

//-----------------------------�﷨��������------------------------------------
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
void function_storage(function* pfunc);//��������ĺ���
void function_expand(function* pfunc);//�ռ䲻������
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
