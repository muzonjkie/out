#include "head.h"

int row = 0;
int main_flag=0;
int SUCC;//编译成功的标志

static Key_Word keywords[] = {
	{NULL,Kw_plus,"+",NULL},
	{NULL,Kw_minus,"-",NULL},
	{NULL,Kw_star,"*",NULL},
	{NULL,Kw_divide,"/",NULL},
	{NULL,Kw_mod,"%",NULL},
	{NULL,Kw_eq,"==",NULL},
	{NULL,Kw_neq,"!=",NULL},
	{NULL,Kw_lt,"<",NULL},
	{NULL,Kw_leq,"<=",NULL},
	{NULL,Kw_gt,">",NULL},
	{NULL,Kw_geq,">=",NULL},
	{NULL,Kw_assign,"=",NULL},
	{NULL,Kw_not,"!",NULL },
	{NULL,Kw_and,"&&",NULL },
	{NULL,Kw_or,"||",NULL },
	{NULL,Kw_addr,"&",NULL},		// & 取地址(暂不支持与运算符)
	{NULL,Kw_pointsto,"->",NULL},
	{NULL,Kw_dot,".",NULL},

	{NULL,Kw_openpa,"(",NULL},
	{NULL,Kw_closepa,")",NULL},
	{NULL,Kw_openbr,"[",NULL},
	{NULL,Kw_closebr,"]",NULL},
	{NULL,Kw_begin,"{",NULL},
	{NULL,Kw_end,"}",NULL},
	{NULL,Kw_semicolon,";",NULL},
	{NULL,Kw_comma,",",NULL},
	{NULL,Kw_hash,"#",NULL},
	{NULL,Kw_eof,"End Of File",NULL},		

	{NULL,Kw_cchar,"字符常量",NULL},
	{NULL,Kw_cint,"整形常量",NULL},
	{NULL,Kw_cfloat,"浮点型常量",NULL},
	{NULL,Kw_cstr,"字符串常量",NULL},

	{NULL,Kw_char,"char",NULL},
	{NULL,Kw_int,"int",NULL},
	{NULL,Kw_float,"float",NULL},
	{NULL,Kw_void,"void",NULL},			//不支持指针，则void只能在函数定义/声明出现
	{NULL,Kw_struct,"struct",NULL},

	{NULL,Kw_if,"if",NULL},
	{NULL,Kw_else,"else",NULL},
	{NULL,Kw_for,"for",NULL},
	{NULL,Kw_while,"while",NULL},
	{NULL,Kw_continue,"continue",NULL},
	{NULL,Kw_break,"break",NULL},
	{NULL,Kw_return,"return",NULL},
	{NULL,Kw_include,"include",NULL},

	{NULL,Kw_notes},		//注释
	{NULL,Kw_space," ",NULL},
	{NULL,Kw_tabs,"    ",NULL},

	{NULL,Kw_identv},		//变量名
	{NULL,Kw_identf}		//函数名
};





int main()
{
	int kw_length = sizeof(keywords) / sizeof(Key_Word);
	Key_Word* kword_hashtable[maxsize] = { 0 };
	Inithashtable(keywords, kw_length, kword_hashtable);
	words array;
	variable var;				//全局变量,结构体类型声明存储
	variable var_in;			//存放函数内部变量
	function func;				//存放声明的函数
	word_storage(&array);
	variable_storage(&var);	
	variable_storage(&var_in);
	function_storage(&func);
	JmpJud = setjmp(jmpbuf);
	switch (JmpJud){			
		case func_undefined:				printf("编译失败，%d行使用了未知的函数！",row); break;
		case func_repeat_definition:		printf("编译失败，%d行重复定义的函数！", row); break;
		case var_undefined:					printf("编译失败，%d行使用了未定义的变量！", row); break;
		case var_uninitialzed:				printf("编译失败，%d行使用了未初始化的变量！", row); break;
		case var_repeat_definition:			printf("编译失败，%d行重复定义的的变量！", row); break;
		case func_define_error:				printf("编译失败，%d行函数定义内部参数不合规范！", row); break;
						

		case lack_semicolon:				printf("编译失败，%d行缺少';'！", row); break;
		case lack_parameter:				printf("编译失败，%d行缺少参数！", row); break;
		case lack_openpa:					printf("编译失败，%d行缺少'('！", row); break;
		case lack_closepa:					printf("编译失败，%d行缺少')'!", row); break;
		case lack_openbr:					printf("编译失败，%d行缺少'['！", row); break;
		case lack_closebr:					printf("编译失败，%d行缺少']'！", row); break;
		case lack_begin:					printf("编译失败，%d行缺少'{'！", row); break;
		case lack_end:						printf("编译失败，%d行缺少'}'！", row); break;
		case lack_if:						printf("编译失败，%d行else或else if使用错误！", row); break;
		case lack_expression:				printf("编译失败，%d行缺少表达式！", row); break;
		case lack_quotation_mark:			printf("编译失败，%d行缺少'''！", row); break;
		case lack_dquotation_mark:			printf("编译失败，%d行缺少'\"'！", row); break;
		case lack_space:					printf("编译失败，%d行缺少空格隔离！", row); break; 
		case lack_identv:					printf("编译失败，%d行缺少变量名！", row); break;
		case lack_identf:					printf("编译失败，%d行缺少函数名！", row); break;
		case lack_value:					printf("编译失败，%d行可能丢失精确数值！", row); break;


		case type_error:					printf("编译失败，%d行类型不一致(缺少类型)！", row); break;
		case array_error:					printf("编译失败，%d行数组错误(不完整)/越界！", row); break;
		case struct_error:					printf("编译失败，%d行结构体错误(不完整)/未定义的结构体类型！", row); break;
		case expression_error:				printf("编译失败，%d行错误的表达式！", row); break;
		case func_parameter_error:			printf("编译失败，%d行函数的参数不一致！", row); break;
		case continue_use_error:			printf("编译失败，%d行continue使用场景错误！", row); break;
		case break_use_error:				printf("编译失败，%d行break使用场景错误！", row); break;
		case return_error:					printf("编译失败，%d行return类型错误！", row); break;
		case headfile_error:				printf("编译失败，%d行头文件引用错误！", row); break;
		case main_error:					printf("编译失败，%d行主函数返回值类型不是int或非函数实现", row); break;
		case para_type_error:				printf("编译失败，%d行参数类型错误", row); break;
								
		case init_value_more:				printf("编译失败，%d行初始值设定项过多！", row); break;
		case unknown_struct_type:			printf("编译失败，%d行未知的结构体类型！", row); break;
		case repeat_struct_statement:		printf("编译失败，%d行重复的结构体声明！", row); break;
		case struct_lack_mem:				printf("编译失败，%d行结构体内部无成员变量！", row); break;
		case need_Kw_begin_Kw_end:			printf("编译失败，%d行需要带大括号的表达式！", row); break;
		case statememnt_should_front:		printf("编译失败，%d行函数声明应放在main函数之前！", row); break;
		case para_too_more:					printf("编译失败，%d行函数传递参数过多！", row); break;
		case para_too_less:					printf("编译失败，%d行函数传递参数过少！", row); break;

						



		case program_start:					printf("开始编译......\n");
			word_split(&array, kword_hashtable);	//此函数里的行数不包括空行，即显示的是不为空的行数中的第几行
			grammar_clear(array, &var,&var_in,&func);				//此函数里的行数不包括空行，即显示的是不为空的行数中的第几行
			SUCC = 1;
		default:
			printf("\n==========未发现编译错误==========\n");
			break;
	}
	if (SUCC) {
		printf("\n");
		printf("代码为：\n\n");
		printf_words(&array);
	}
		
	return 0;
}