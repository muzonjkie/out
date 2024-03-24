#include "head.h"

extern Key_Word* pcur;

void variable_storage(variable* pvar)				//�洢���ֵı�����ṹ������
{
	pvar->word = (char(*)[var_size])calloc(line, var_size * sizeof(char));
	pvar->type = (char(*)[type_size])calloc(line, type_size * sizeof(char));
	pvar->array_flag = (int*)calloc(line, sizeof(int));		//Ĭ��Ϊ������
	pvar->array_count = (int*)calloc(line, sizeof(int));
	pvar->init_flag = (int*)calloc(line, sizeof(int));		//Ĭ��Ϊδ��ʼ��
	pvar->mem = (member**)calloc(line, sizeof(member*));
	pvar->part = (array_next**)calloc(line, sizeof(array_next*));
	pvar->grade = (int*)calloc(line, sizeof(int));
	pvar->count = line;
}

void variable_expand(variable* pvar)				//�ռ䲻������
{
	if (pvar->row + 1 == pvar->count) {			//�������Ѵ���
		int len = pvar->count;
		pvar->count *= 2;
		pvar->word = (char(*)[var_size])realloc(pvar->word, var_size * sizeof(char) * pvar->count);
		pvar->type = (char(*)[type_size])realloc(pvar->type, type_size * sizeof(char) * pvar->count);
		pvar->array_flag = (int*)realloc(pvar->array_flag, sizeof(int) * pvar->count);
		pvar->array_count = (int*)realloc(pvar->array_flag, sizeof(int) * pvar->count);
		pvar->init_flag = (int*)realloc(pvar->init_flag, sizeof(int) * pvar->count);
		pvar->mem = (member**)realloc(pvar->mem, sizeof(member*) * pvar->count);
		pvar->part = (array_next**)realloc(pvar->part, sizeof(array_next*) * pvar->count);
		pvar->grade = (int*)realloc(pvar->grade, sizeof(int) * pvar->count);
		memset(pvar->word + len, 0, var_size * sizeof(char) * len);		//�¿ռ��ʼ��
		memset(pvar->type + len, 0, type_size * sizeof(char) * len);	//�¿ռ��ʼ��
		memset(pvar->array_flag + len, false, sizeof(int) * len);		//Ĭ��Ϊ������
		memset(pvar->array_count + len, 0, sizeof(int) * len);			//�¿ռ��ʼ��
		memset(pvar->init_flag + len, false, sizeof(int) * len);		//Ĭ��Ϊδ��ʼ��
		memset(pvar->mem + len, 0, sizeof(member*) * len);				//�¿ռ��ʼ��
		memset(pvar->part + len, 0, sizeof(array_next*) * len);
		memset(pvar->grade + len, false, sizeof(int) * len);			//��ʼ��Ϊ��
	}
}

void function_storage(function* pfunc)				//��������ĺ���
{
	pfunc->is_define = (int*)calloc(line, sizeof(int));
	pfunc->word = (char(*)[var_size])calloc(line, var_size * sizeof(char));
	pfunc->type = (char(*)[type_size])calloc(line, type_size * sizeof(char));
	pfunc->para = (parameter**)calloc(line, sizeof(parameter*));
	pfunc->count = line;
}


void function_expand(function* pfunc)				//�ռ䲻������
{
	if (pfunc->row + 1 == pfunc->count) {			//�������Ѵ���
		int len = pfunc->count;
		pfunc->count *= 2;
		pfunc->is_define = (int*)realloc(pfunc->is_define, sizeof(int) * pfunc->count);
		pfunc->word = (char(*)[var_size])realloc(pfunc->word, var_size * sizeof(char) * pfunc->count);
		pfunc->type = (char(*)[type_size])realloc(pfunc->type, type_size * sizeof(char) * pfunc->count);
		pfunc->para = (parameter**)realloc(pfunc->para, sizeof(parameter*) * pfunc->count);
		memset(pfunc->is_define + len, 0, sizeof(int) * len);		//�¿ռ��ʼ��
		memset(pfunc->word + len, 0, var_size * sizeof(char) * len);		//�¿ռ��ʼ��
		memset(pfunc->type + len, 0, type_size * sizeof(char) * len);	//�¿ռ��ʼ��
		memset(pfunc->para + len, 0, sizeof(parameter**) * len);
	}
}


void grammar_clear(words array, variable* pvar, variable* pvar_in, function* pfunc) {
	pcur = array.list[1];
	row = 1;
	pvar->row = 1;			//��������
	pvar_in->row = 1;
	pfunc->row = 1;
	External_dec(pvar, pvar_in, pfunc);
}


void struct_array_part_storage(variable* pvar) {				//����Ϊ����ʱ���������Ա
	if (pvar->array_count[pvar->row] > 1) {				//����Ϊ����ʱ����Ӧ����Ϊ����
		int i;
		pvar->part[pvar->row] = (array_next*)calloc(1, sizeof(array_next));
		pvar->part[pvar->row]->mem = (member**)calloc(pvar->array_count[pvar->row] - 1, sizeof(member*));
		pvar->part[pvar->row]->init_flag = (int*)calloc(pvar->array_count[pvar->row] - 1, sizeof(int));
		for (i = 0; i < pvar->array_count[pvar->row] - 1; ++i) {		//��Ϊ�ṹ��,��һ���ĳ�Ա(���ǽṹ����ΪNULL)
			pvar->part[pvar->row]->mem[i] = (member*)calloc(1, sizeof(member));//Ϊ�ṹ�������Ա����һ���Ľṹ���ڲ���Ա�ռ�
			*(pvar->part[pvar->row]->mem[i]) = *(pvar->mem[pvar->row]);		//����ͬ��Ϊһ��������;
			member* temp = pvar->mem[pvar->row]->next;
			member* p = pvar->part[pvar->row]->mem[i], * pnew = NULL;
			while (temp) {
				pnew = (member*)calloc(1, sizeof(member));
				*(pnew) = *temp;				//��Աһ��						
				p->next = pnew;					//�ṹ���ڲ���Աָ���¸��ṹ���ڲ���Ա
				p = p->next;
				temp = temp->next;
			}
		}		//���⽫���нṹ�������Ա�е��ڲ���Ա��ͬ�����
	}
}

void same_struct_mem_copy(variable* pvar, int k) {		//�ҽṹ����������������������
	pvar->mem[pvar->row] = (member*)calloc(1, sizeof(member));//Ϊ�ṹ���ڲ���Ա����һ���Ľṹ���ڲ���Ա�ռ�
	*(pvar->mem[pvar->row]) = *(pvar->mem[k]);		//����ͬ��Ϊһ��������;
	member* temp = pvar->mem[k]->next;
	member* p = pvar->mem[pvar->row], * pnew = NULL;
	while (temp) {
		pnew = (member*)calloc(1, sizeof(member));
		*(pnew) = *temp;				//��Աһ��						
		p->next = pnew;					//�ṹ���ڲ���Աָ���¸��ṹ���ڲ���Ա
		p = p->next;
		temp = temp->next;
	}		//���⽫���нṹ����ڲ���Աͬ�����
}

void struct_mem_array_part_storage(member* temp) {
	if (temp->array_count > 1) {
		temp->part_init = (int*)calloc(temp->array_count - 1, sizeof(int));
	}					//��Ĭ��Ϊδ��ʼ��
}



bool have_space_judge()				//�����ʼ�Ӧ�пո񣬲����ߵ��ո�
{
	int have = 0;
	while (pcur && (Kw_tabs == pcur->KwCode || Kw_space == pcur->KwCode)) {
		if (1 == pcur->row_tail_flag)
			row++;
		pcur = pcur->next;
		have = 1;
	}
	return have;
}

void next_node()
{
	if (pcur->row_tail_flag)
		++row;
	pcur = pcur->next;			//���ߵ���ǰ����
}

bool statement_valid_ok_judge(variable* pnow) {
	int i = 0,flag=0;
	for (i = 1; i < pnow->row; ++i) {							//��ǰ�����ѣ��ҵ���һ���ǽṹ����������
		int ret = strcmp(pnow->type[pnow->row], pnow->type[i]);		//�����ýṹ�����������Ƿ��Ѵ���			
		if (0 == ret) { 						//���ҵ��иýṹ����������	
			flag = i;
			break;
		}
	}
	return flag;			//�����ڸýṹ����������,������λ�ã�����ֵ��;���򷵻���
}

bool identv_valid_ok_judge(variable* pnow) {//�ҵ���ṹ����������������������λ��
	int i, ret = 0,flag=0;
	for (i = 1; i < pnow->row; ++i) {							//��ǰ�����ѣ��ҵ���һ���ǽṹ����������
		ret = strcmp(pnow->type[pnow->row], pnow->type[i]);		//�����ýṹ�������Ƿ�������			
		if (0 == ret) { 						//���ҵ��иýṹ����������
			flag = i;
			break;
		}
	}
	return flag;
}

int repeat_judge(variable* pnow) {			//�˱����Ƿ�����(����);������������Ҫ���ڲ�ͬ���
	int i, flag = 0;
	for (i = 1; i < pnow->row; ++i) {
		int ret = strcmp(pnow->word[pnow->row], pnow->word[i]);					//�ñ������Ƿ�������,������Ҫ
		if (0 == ret && pnow->grade[pnow->row] == pnow->grade[i]) { 		//��ͬһ���,��ͬ��,��Ϊ������
			flag = i;
			break;
		}
	}
	return flag;		//������������������λ�ã���������;��δ������,������
}

int have_identv(variable* pnow) {//�Ƿ���ڸñ���
	int i, flag = 0;
	for (i = 1; i < pnow->row; ++i) {
		int ret = strcmp(pcur->spell, pnow->word[i]);					
		if (0 == ret) { 		
			flag = i;
			break;
		}
	}
	return flag;		//�����ڷ���������λ�ã���������;��������,������
}


bool cmp_para(function* pfunc, variable* pnow) {	//�����ڶ���ı��������ǵ�һ��ģ������뺯������������
	parameter* temp = pfunc->para[pfunc->row];
	int flag = 0;
	while (temp) {
		int ret = strcmp(temp->word, pnow->word[pnow->row]);
		if (0 == ret) {		//�ҵ�����
			flag = 1;
			break;
		}
	}
	return flag;
}


bool parameter_name_examine(function* pfunc, int pos)//���ú��������в���
{
	parameter* temp = pfunc->para[pos];
	while (temp) {
		if (!temp->word)//������������,ֻ���ں������������
			return false;
		temp = temp->next;
	}
	return true;
}


int top_first(variable* pvar) {		//����������ѡ������ߵ�(��Ծֲ�����)
	int i, flag = 0;
	for (i = 1; i < pvar->row; ++i) {
		int ret = strcmp(pcur->spell, pvar->word[i]);
		if (0 == ret) { 		//ͬ��
			if (pvar->grade[flag] < pvar->grade[i])//�ҵ����߲��;��ֻ��һ��������Ҳ�����
				flag = i;
			break;
		}
	}
	return flag;		//�����ڴ˱�������λ�ã��������Ҳ����ߵģ�;��������,������
}

int have_func_statement(function* pfunc, int pos) {	//�Ƿ��иú���������
	int i;
	int flag = 0;//�Ƿ��иú�������
	int good = 0;//�����Ƿ�һ��
	for (i = 1; i < pfunc->row; ++i) {
		int ret = strcmp(pfunc->word[pos], pfunc->word[i]);
		if (0 == ret && 0 == pfunc->is_define[i]) {//�Ǻ�������
			flag = i;	//�ҵ�����������λ��
			break;
		}
	}
	if (flag) {	//���ҵ��˺�������
		parameter* p = pfunc->para[pos];//��ǰ��������
		parameter* q = pfunc->para[flag];//�ҵ��Ĵ˺�������
		int ret1 = 1, ret2 = 1;		//��ʼ��Ϊ������
		while (p) {
			ret1 = strcmp(p->type, q->type);
			ret2 = p->array_flag - q->array_flag;
			if (0 != ret1 || 0 != ret2) {//�����Ͳ�һ�»��߲���ͬ����(������)
				good = 0;
				break;
			}
			else
				good = flag;//������
			p = p->next;
			q = q->next;
		}
	}
	return good;		//���غ�������λ�ã���������;��������,������
}


int have_func_define(function* pfunc, int pos) {//�Ƿ��Ѿ����˸ú����Ķ���
	int i;
	int flag = 0;//�Ƿ��иú�������
	for (i = 1; i < pfunc->row; ++i) {
		int ret = strcmp(pfunc->word[pos], pfunc->word[i]);
		if (0 == ret && 1 == pfunc->is_define[i]) {//�Ǻ�������
			flag = i;	//�ҵ����������λ��
			break;
		}
	}
	return flag;		//���غ�������λ�ã���������;��������,������
}

parameter* have_func_var(function* pfunc) {//�����ڸú����������Ƿ���ڸò�������
	parameter* temp = pfunc->para[pfunc->row];
	while (temp) {
		if (!strcmp(temp->word, pcur->spell)) {	//�ҵ��ò�������
			break;
		}
		temp = temp->next;
	}
	return temp;
}

int exist_func(function* pfunc) {//�Ƿ���ڸõ��ú����Ķ���
	int i;
	int flag = 0;//�Ƿ��иú�������
	for (i = 1; i <=pfunc->row; ++i) {
		int ret = strcmp(pcur->spell, pfunc->word[i]);
		if (0 == ret && 1 == pfunc->is_define[i]) {//�Ǻ�������
			flag = i;	//�ҵ����������λ��
			break;
		}
	}
	return flag;		//���غ�������λ�ã���������;��������,������
}

member* struct_mem_repeat_judge(variable* pnow, int posi) {			//�ṹ���ڲ���Ա�Ƿ�������
	int flag = 0;
	member* temp = pnow->mem[posi];
	while (temp) {
		int ret = strcmp(pcur->spell, temp->word);
		if (0 == ret) {
			flag = 1;
			break;
		}
		temp = temp->next;
	}
	return temp;		//�����������ط�����;��δ������,������
}

//member* struct_have_mem(function *pfunc,int posi) {//����������Ϊ�ṹ�壬��ѯ���Ƿ���ڴ˳�Ա
//	int flag = 0;
//	member* temp = pfunc->para[posi];
//	while (temp) {
//		int ret = strcmp(pcur->spell, temp->word);
//		if (0 == ret) {
//			flag = 1;
//			break;
//		}
//		temp = temp->next;
//	}
//	return temp;		//�����������ط�����;��δ������,������
//}

member* parameter_mem_repeat_judge(parameter* pfunc_var) {//�ò���Ϊ�ṹ�壬�鿴�Ƿ��ж�Ӧ���ڲ���Ա
	int flag = 0;
	member* temp = pfunc_var->mem;
	while (temp) {
		int ret = strcmp(pcur->spell, temp->word);
		if (0 == ret) {
			flag = 1;
			break;
		}
		temp = temp->next;
	}
	return temp;		//�����������ط�����;��δ������,������
}


void struct_rest_mem(member* rest) {//�ṹ������ĳ��Ա���ڲ���Ա������Щ������ʼ���˵�δ���Ϊ�ѳ�ʼ��
	while (rest) {		//����ڲ���Ա��ʼ��
		rest->init_flag = 1;
		if (rest->array_flag) {
			int j = 0;
			for (j; j < rest->array_count - 1; ++j) {
				rest->part_init[j] = 1;
			}
		}
		rest = rest->next;
	}
}


void Is_init_too_more(int flag) {		//�жϽṹ���ڲ���Ա��������ڳ�ʼ����������������'{',�ڱպ�ʱ�ж�
	if (1 == flag) {								//�˴������ڱ�������һ��������
		Key_Word* temp = pcur;			//�浵
		int num = 0;
		while (Kw_begin != pcur->KwCode) {
			if (Is_this(Kw_cchar) || Is_this(Kw_cfloat) || Is_this(Kw_cint)) {
				++num;
			}
			pcur = pcur->prior;
		}
		if (num > 1)
			longjmp(jmpbuf, init_value_more);
		pcur = temp;					//�ص�
	}
}

void Is_init_more(int flag) {
	if (1 == flag) {								//�˴������ڱ�������һ��������
		Key_Word* temp = pcur;			//�浵
		int num = 1;
		pcur = pcur->prior;
		while (Is_this(Kw_space) || Is_this(Kw_tabs)) {
			pcur = pcur->prior;
		}
		if (Is_this(Kw_comma))	//����ĵ�ǰһ��','��������
			pcur = pcur->prior;
		while (Kw_begin != pcur->KwCode) {
			if (Is_this(Kw_comma)) {		//	���������˸���ֵ
				++num;
			}
			pcur = pcur->prior;
		}
		if (num > 1)		//	����һ����ֵ
			longjmp(jmpbuf, init_value_more);
		pcur = temp;					//�ص�
	}
}




void struct_mem_array_part(member* p) {		//�ṹ���ڲ������п������µĲ���δ���Ϊ�ѳ�ʼ��
	if (p->array_flag) {
		int j = 0;
		for (j; j < p->array_count - 1; ++j)
			p->part_init[j] = 1;
	}
}



int string_value(char* str) {			//���ַ�ת��Ϊ����ֵ
	int length = strlen(str);
	int i = 0, value = 0;
	for (i; i < length; ++i) {			//ת�����鳤��
		value = str[i] - '0' + value * 10;
	}
	return value;
}

void identv_array_part_init(variable* pvar) {
	int j = 0;
	for (j; j < pvar->array_count[pvar->row] - 1; ++j) {
		pvar->part[pvar->row]->init_flag[j] = 1;
	}
}

void identv_array_part_storage(variable* pvar) {	//�˱���Ϊ����,�����������ԱΪ�ѳ�ʼ��
	if (pvar->array_count[pvar->row] - 1 > 0) {
		pvar->part[pvar->row] = (array_next*)calloc(1, sizeof(array_next));
		pvar->part[pvar->row]->init_flag = (int*)calloc(pvar->array_count[pvar->row] - 1, sizeof(int));
	}
}