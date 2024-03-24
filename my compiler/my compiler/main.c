#include "head.h"

int row = 0;
int main_flag=0;
int SUCC;//����ɹ��ı�־

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
	{NULL,Kw_addr,"&",NULL},		// & ȡ��ַ(�ݲ�֧���������)
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

	{NULL,Kw_cchar,"�ַ�����",NULL},
	{NULL,Kw_cint,"���γ���",NULL},
	{NULL,Kw_cfloat,"�����ͳ���",NULL},
	{NULL,Kw_cstr,"�ַ�������",NULL},

	{NULL,Kw_char,"char",NULL},
	{NULL,Kw_int,"int",NULL},
	{NULL,Kw_float,"float",NULL},
	{NULL,Kw_void,"void",NULL},			//��֧��ָ�룬��voidֻ���ں�������/��������
	{NULL,Kw_struct,"struct",NULL},

	{NULL,Kw_if,"if",NULL},
	{NULL,Kw_else,"else",NULL},
	{NULL,Kw_for,"for",NULL},
	{NULL,Kw_while,"while",NULL},
	{NULL,Kw_continue,"continue",NULL},
	{NULL,Kw_break,"break",NULL},
	{NULL,Kw_return,"return",NULL},
	{NULL,Kw_include,"include",NULL},

	{NULL,Kw_notes},		//ע��
	{NULL,Kw_space," ",NULL},
	{NULL,Kw_tabs,"    ",NULL},

	{NULL,Kw_identv},		//������
	{NULL,Kw_identf}		//������
};





int main()
{
	int kw_length = sizeof(keywords) / sizeof(Key_Word);
	Key_Word* kword_hashtable[maxsize] = { 0 };
	Inithashtable(keywords, kw_length, kword_hashtable);
	words array;
	variable var;				//ȫ�ֱ���,�ṹ�����������洢
	variable var_in;			//��ź����ڲ�����
	function func;				//��������ĺ���
	word_storage(&array);
	variable_storage(&var);	
	variable_storage(&var_in);
	function_storage(&func);
	JmpJud = setjmp(jmpbuf);
	switch (JmpJud){			
		case func_undefined:				printf("����ʧ�ܣ�%d��ʹ����δ֪�ĺ�����",row); break;
		case func_repeat_definition:		printf("����ʧ�ܣ�%d���ظ�����ĺ�����", row); break;
		case var_undefined:					printf("����ʧ�ܣ�%d��ʹ����δ����ı�����", row); break;
		case var_uninitialzed:				printf("����ʧ�ܣ�%d��ʹ����δ��ʼ���ı�����", row); break;
		case var_repeat_definition:			printf("����ʧ�ܣ�%d���ظ�����ĵı�����", row); break;
		case func_define_error:				printf("����ʧ�ܣ�%d�к��������ڲ��������Ϲ淶��", row); break;
						

		case lack_semicolon:				printf("����ʧ�ܣ�%d��ȱ��';'��", row); break;
		case lack_parameter:				printf("����ʧ�ܣ�%d��ȱ�ٲ�����", row); break;
		case lack_openpa:					printf("����ʧ�ܣ�%d��ȱ��'('��", row); break;
		case lack_closepa:					printf("����ʧ�ܣ�%d��ȱ��')'!", row); break;
		case lack_openbr:					printf("����ʧ�ܣ�%d��ȱ��'['��", row); break;
		case lack_closebr:					printf("����ʧ�ܣ�%d��ȱ��']'��", row); break;
		case lack_begin:					printf("����ʧ�ܣ�%d��ȱ��'{'��", row); break;
		case lack_end:						printf("����ʧ�ܣ�%d��ȱ��'}'��", row); break;
		case lack_if:						printf("����ʧ�ܣ�%d��else��else ifʹ�ô���", row); break;
		case lack_expression:				printf("����ʧ�ܣ�%d��ȱ�ٱ��ʽ��", row); break;
		case lack_quotation_mark:			printf("����ʧ�ܣ�%d��ȱ��'''��", row); break;
		case lack_dquotation_mark:			printf("����ʧ�ܣ�%d��ȱ��'\"'��", row); break;
		case lack_space:					printf("����ʧ�ܣ�%d��ȱ�ٿո���룡", row); break; 
		case lack_identv:					printf("����ʧ�ܣ�%d��ȱ�ٱ�������", row); break;
		case lack_identf:					printf("����ʧ�ܣ�%d��ȱ�ٺ�������", row); break;
		case lack_value:					printf("����ʧ�ܣ�%d�п��ܶ�ʧ��ȷ��ֵ��", row); break;


		case type_error:					printf("����ʧ�ܣ�%d�����Ͳ�һ��(ȱ������)��", row); break;
		case array_error:					printf("����ʧ�ܣ�%d���������(������)/Խ�磡", row); break;
		case struct_error:					printf("����ʧ�ܣ�%d�нṹ�����(������)/δ����Ľṹ�����ͣ�", row); break;
		case expression_error:				printf("����ʧ�ܣ�%d�д���ı��ʽ��", row); break;
		case func_parameter_error:			printf("����ʧ�ܣ�%d�к����Ĳ�����һ�£�", row); break;
		case continue_use_error:			printf("����ʧ�ܣ�%d��continueʹ�ó�������", row); break;
		case break_use_error:				printf("����ʧ�ܣ�%d��breakʹ�ó�������", row); break;
		case return_error:					printf("����ʧ�ܣ�%d��return���ʹ���", row); break;
		case headfile_error:				printf("����ʧ�ܣ�%d��ͷ�ļ����ô���", row); break;
		case main_error:					printf("����ʧ�ܣ�%d������������ֵ���Ͳ���int��Ǻ���ʵ��", row); break;
		case para_type_error:				printf("����ʧ�ܣ�%d�в������ʹ���", row); break;
								
		case init_value_more:				printf("����ʧ�ܣ�%d�г�ʼֵ�趨����࣡", row); break;
		case unknown_struct_type:			printf("����ʧ�ܣ�%d��δ֪�Ľṹ�����ͣ�", row); break;
		case repeat_struct_statement:		printf("����ʧ�ܣ�%d���ظ��Ľṹ��������", row); break;
		case struct_lack_mem:				printf("����ʧ�ܣ�%d�нṹ���ڲ��޳�Ա������", row); break;
		case need_Kw_begin_Kw_end:			printf("����ʧ�ܣ�%d����Ҫ�������ŵı��ʽ��", row); break;
		case statememnt_should_front:		printf("����ʧ�ܣ�%d�к�������Ӧ����main����֮ǰ��", row); break;
		case para_too_more:					printf("����ʧ�ܣ�%d�к������ݲ������࣡", row); break;
		case para_too_less:					printf("����ʧ�ܣ�%d�к������ݲ������٣�", row); break;

						



		case program_start:					printf("��ʼ����......\n");
			word_split(&array, kword_hashtable);	//�˺�������������������У�����ʾ���ǲ�Ϊ�յ������еĵڼ���
			grammar_clear(array, &var,&var_in,&func);				//�˺�������������������У�����ʾ���ǲ�Ϊ�յ������еĵڼ���
			SUCC = 1;
		default:
			printf("\n==========δ���ֱ������==========\n");
			break;
	}
	if (SUCC) {
		printf("\n");
		printf("����Ϊ��\n\n");
		printf_words(&array);
	}
		
	return 0;
}