#include "head.h"

extern Key_Word* pcur;

void variable_storage(variable* pvar)				//存储出现的变量或结构体声明
{
	pvar->word = (char(*)[var_size])calloc(line, var_size * sizeof(char));
	pvar->type = (char(*)[type_size])calloc(line, type_size * sizeof(char));
	pvar->array_flag = (int*)calloc(line, sizeof(int));		//默认为非数组
	pvar->array_count = (int*)calloc(line, sizeof(int));
	pvar->init_flag = (int*)calloc(line, sizeof(int));		//默认为未初始化
	pvar->mem = (member**)calloc(line, sizeof(member*));
	pvar->part = (array_next**)calloc(line, sizeof(array_next*));
	pvar->grade = (int*)calloc(line, sizeof(int));
	pvar->count = line;
}

void variable_expand(variable* pvar)				//空间不够扩容
{
	if (pvar->row + 1 == pvar->count) {			//若行数已存满
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
		memset(pvar->word + len, 0, var_size * sizeof(char) * len);		//新空间初始化
		memset(pvar->type + len, 0, type_size * sizeof(char) * len);	//新空间初始化
		memset(pvar->array_flag + len, false, sizeof(int) * len);		//默认为非数组
		memset(pvar->array_count + len, 0, sizeof(int) * len);			//新空间初始化
		memset(pvar->init_flag + len, false, sizeof(int) * len);		//默认为未初始化
		memset(pvar->mem + len, 0, sizeof(member*) * len);				//新空间初始化
		memset(pvar->part + len, 0, sizeof(array_next*) * len);
		memset(pvar->grade + len, false, sizeof(int) * len);			//初始化为零
	}
}

void function_storage(function* pfunc)				//存放声明的函数
{
	pfunc->is_define = (int*)calloc(line, sizeof(int));
	pfunc->word = (char(*)[var_size])calloc(line, var_size * sizeof(char));
	pfunc->type = (char(*)[type_size])calloc(line, type_size * sizeof(char));
	pfunc->para = (parameter**)calloc(line, sizeof(parameter*));
	pfunc->count = line;
}


void function_expand(function* pfunc)				//空间不够扩容
{
	if (pfunc->row + 1 == pfunc->count) {			//若行数已存满
		int len = pfunc->count;
		pfunc->count *= 2;
		pfunc->is_define = (int*)realloc(pfunc->is_define, sizeof(int) * pfunc->count);
		pfunc->word = (char(*)[var_size])realloc(pfunc->word, var_size * sizeof(char) * pfunc->count);
		pfunc->type = (char(*)[type_size])realloc(pfunc->type, type_size * sizeof(char) * pfunc->count);
		pfunc->para = (parameter**)realloc(pfunc->para, sizeof(parameter*) * pfunc->count);
		memset(pfunc->is_define + len, 0, sizeof(int) * len);		//新空间初始化
		memset(pfunc->word + len, 0, var_size * sizeof(char) * len);		//新空间初始化
		memset(pfunc->type + len, 0, type_size * sizeof(char) * len);	//新空间初始化
		memset(pfunc->para + len, 0, sizeof(parameter**) * len);
	}
}


void grammar_clear(words array, variable* pvar, variable* pvar_in, function* pfunc) {
	pcur = array.list[1];
	row = 1;
	pvar->row = 1;			//不用零行
	pvar_in->row = 1;
	pfunc->row = 1;
	External_dec(pvar, pvar_in, pfunc);
}


void struct_array_part_storage(variable* pvar) {				//变量为数组时其余数组成员
	if (pvar->array_count[pvar->row] > 1) {				//变量为数组时总数应至少为两个
		int i;
		pvar->part[pvar->row] = (array_next*)calloc(1, sizeof(array_next));
		pvar->part[pvar->row]->mem = (member**)calloc(pvar->array_count[pvar->row] - 1, sizeof(member*));
		pvar->part[pvar->row]->init_flag = (int*)calloc(pvar->array_count[pvar->row] - 1, sizeof(int));
		for (i = 0; i < pvar->array_count[pvar->row] - 1; ++i) {		//若为结构体,则一样的成员(不是结构体则为NULL)
			pvar->part[pvar->row]->mem[i] = (member*)calloc(1, sizeof(member));//为结构体数组成员申请一样的结构体内部成员空间
			*(pvar->part[pvar->row]->mem[i]) = *(pvar->mem[pvar->row]);		//将其同步为一样的设置;
			member* temp = pvar->mem[pvar->row]->next;
			member* p = pvar->part[pvar->row]->mem[i], * pnew = NULL;
			while (temp) {
				pnew = (member*)calloc(1, sizeof(member));
				*(pnew) = *temp;				//成员一致						
				p->next = pnew;					//结构体内部成员指向下个结构体内部成员
				p = p->next;
				temp = temp->next;
			}
		}		//到这将所有结构体数组成员中的内部成员已同步完毕
	}
}

void same_struct_mem_copy(variable* pvar, int k) {		//找结构体类型声明，复制其声明
	pvar->mem[pvar->row] = (member*)calloc(1, sizeof(member));//为结构体内部成员申请一样的结构体内部成员空间
	*(pvar->mem[pvar->row]) = *(pvar->mem[k]);		//将其同步为一样的设置;
	member* temp = pvar->mem[k]->next;
	member* p = pvar->mem[pvar->row], * pnew = NULL;
	while (temp) {
		pnew = (member*)calloc(1, sizeof(member));
		*(pnew) = *temp;				//成员一致						
		p->next = pnew;					//结构体内部成员指向下个结构体内部成员
		p = p->next;
		temp = temp->next;
	}		//到这将所有结构体的内部成员同步完毕
}

void struct_mem_array_part_storage(member* temp) {
	if (temp->array_count > 1) {
		temp->part_init = (int*)calloc(temp->array_count - 1, sizeof(int));
	}					//已默认为未初始化
}



bool have_space_judge()				//两个词间应有空格，并且走掉空格
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
	pcur = pcur->next;			//先走掉当前符号
}

bool statement_valid_ok_judge(variable* pnow) {
	int i = 0,flag=0;
	for (i = 1; i < pnow->row; ++i) {							//从前往后搜，找到的一定是结构体类型声明
		int ret = strcmp(pnow->type[pnow->row], pnow->type[i]);		//搜索该结构体类型声明是否已存在			
		if (0 == ret) { 						//则找到有该结构体类型声明	
			flag = i;
			break;
		}
	}
	return flag;			//若存在该结构体类型声明,返回其位置（非零值）;否则返回零
}

bool identv_valid_ok_judge(variable* pnow) {//找到其结构体类型声明处，带回声明位置
	int i, ret = 0,flag=0;
	for (i = 1; i < pnow->row; ++i) {							//从前往后搜，找到的一定是结构体类型声明
		ret = strcmp(pnow->type[pnow->row], pnow->type[i]);		//搜索该结构体类型是否已声明			
		if (0 == ret) { 						//则找到有该结构体类型声明
			flag = i;
			break;
		}
	}
	return flag;
}

int repeat_judge(variable* pnow) {			//此变量是否重名(存在);允许重名，但要求在不同层次
	int i, flag = 0;
	for (i = 1; i < pnow->row; ++i) {
		int ret = strcmp(pnow->word[pnow->row], pnow->word[i]);					//该变量名是否有重名,重名不要
		if (0 == ret && pnow->grade[pnow->row] == pnow->grade[i]) { 		//在同一层次,又同名,则为重命名
			flag = i;
			break;
		}
	}
	return flag;		//若重命名返回重命名位置（非零数）;若未重命名,返回零
}

int have_identv(variable* pnow) {//是否存在该变量
	int i, flag = 0;
	for (i = 1; i < pnow->row; ++i) {
		int ret = strcmp(pcur->spell, pnow->word[i]);					
		if (0 == ret) { 		
			flag = i;
			break;
		}
	}
	return flag;		//若存在返回重命名位置（非零数）;若不存在,返回零
}


bool cmp_para(function* pfunc, variable* pnow) {	//函数内定义的变量，若是第一层的，不能与函数参数有重名
	parameter* temp = pfunc->para[pfunc->row];
	int flag = 0;
	while (temp) {
		int ret = strcmp(temp->word, pnow->word[pnow->row]);
		if (0 == ret) {		//找到重名
			flag = 1;
			break;
		}
	}
	return flag;
}


bool parameter_name_examine(function* pfunc, int pos)//若该函数定义有参数
{
	parameter* temp = pfunc->para[pos];
	while (temp) {
		if (!temp->word)//若参数无名称,只能在函数声明里出现
			return false;
		temp = temp->next;
	}
	return true;
}


int top_first(variable* pvar) {		//重名变量中选择层次最高的(针对局部变量)
	int i, flag = 0;
	for (i = 1; i < pvar->row; ++i) {
		int ret = strcmp(pcur->spell, pvar->word[i]);
		if (0 == ret) { 		//同名
			if (pvar->grade[flag] < pvar->grade[i])//找到更高层次;若只有一个变量，也会成立
				flag = i;
			break;
		}
	}
	return flag;		//若存在此变量返回位置（非零数且层次最高的）;若不存在,返回零
}

int have_func_statement(function* pfunc, int pos) {	//是否有该函数的声明
	int i;
	int flag = 0;//是否有该函数声明
	int good = 0;//参数是否一致
	for (i = 1; i < pfunc->row; ++i) {
		int ret = strcmp(pfunc->word[pos], pfunc->word[i]);
		if (0 == ret && 0 == pfunc->is_define[i]) {//是函数声明
			flag = i;	//找到函数声明的位置
			break;
		}
	}
	if (flag) {	//若找到此函数声明
		parameter* p = pfunc->para[pos];//当前函数定义
		parameter* q = pfunc->para[flag];//找到的此函数声明
		int ret1 = 1, ret2 = 1;		//初始化为非零数
		while (p) {
			ret1 = strcmp(p->type, q->type);
			ret2 = p->array_flag - q->array_flag;
			if (0 != ret1 || 0 != ret2) {//若类型不一致或者不是同数组(非数组)
				good = 0;
				break;
			}
			else
				good = flag;//非零数
			p = p->next;
			q = q->next;
		}
	}
	return good;		//返回函数声明位置（非零数）;若不存在,返回零
}


int have_func_define(function* pfunc, int pos) {//是否已经有了该函数的定义
	int i;
	int flag = 0;//是否有该函数定义
	for (i = 1; i < pfunc->row; ++i) {
		int ret = strcmp(pfunc->word[pos], pfunc->word[i]);
		if (0 == ret && 1 == pfunc->is_define[i]) {//是函数定义
			flag = i;	//找到函数定义的位置
			break;
		}
	}
	return flag;		//返回函数定义位置（非零数）;若不存在,返回零
}

parameter* have_func_var(function* pfunc) {//查找在该函数定义中是否存在该参数变量
	parameter* temp = pfunc->para[pfunc->row];
	while (temp) {
		if (!strcmp(temp->word, pcur->spell)) {	//找到该参数变量
			break;
		}
		temp = temp->next;
	}
	return temp;
}

int exist_func(function* pfunc) {//是否存在该调用函数的定义
	int i;
	int flag = 0;//是否有该函数定义
	for (i = 1; i <=pfunc->row; ++i) {
		int ret = strcmp(pcur->spell, pfunc->word[i]);
		if (0 == ret && 1 == pfunc->is_define[i]) {//是函数定义
			flag = i;	//找到函数定义的位置
			break;
		}
	}
	return flag;		//返回函数定义位置（非零数）;若不存在,返回零
}

member* struct_mem_repeat_judge(variable* pnow, int posi) {			//结构体内部成员是否有重名
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
	return temp;		//若重命名返回非零数;若未重命名,返回零
}

//member* struct_have_mem(function *pfunc,int posi) {//函数参数若为结构体，查询其是否存在此成员
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
//	return temp;		//若重命名返回非零数;若未重命名,返回零
//}

member* parameter_mem_repeat_judge(parameter* pfunc_var) {//该参数为结构体，查看是否有对应的内部成员
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
	return temp;		//若重命名返回非零数;若未重命名,返回零
}


void struct_rest_mem(member* rest) {//结构体数组某成员其内部成员可能有些变量初始化了但未标记为已初始化
	while (rest) {		//标记内部成员初始化
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


void Is_init_too_more(int flag) {		//判断结构体内部成员数组变量在初始化过程中若增加了'{',在闭合时判断
	if (1 == flag) {								//此大括号内变量超过一个即报错
		Key_Word* temp = pcur;			//存档
		int num = 0;
		while (Kw_begin != pcur->KwCode) {
			if (Is_this(Kw_cchar) || Is_this(Kw_cfloat) || Is_this(Kw_cint)) {
				++num;
			}
			pcur = pcur->prior;
		}
		if (num > 1)
			longjmp(jmpbuf, init_value_more);
		pcur = temp;					//回档
	}
}

void Is_init_more(int flag) {
	if (1 == flag) {								//此大括号内变量超过一个即报错
		Key_Word* temp = pcur;			//存档
		int num = 1;
		pcur = pcur->prior;
		while (Is_this(Kw_space) || Is_this(Kw_tabs)) {
			pcur = pcur->prior;
		}
		if (Is_this(Kw_comma))	//最靠近的的前一个','不计入内
			pcur = pcur->prior;
		while (Kw_begin != pcur->KwCode) {
			if (Is_this(Kw_comma)) {		//	遇到即多了个赋值
				++num;
			}
			pcur = pcur->prior;
		}
		if (num > 1)		//	超过一个赋值
			longjmp(jmpbuf, init_value_more);
		pcur = temp;					//回档
	}
}




void struct_mem_array_part(member* p) {		//结构体内部数组中可能余下的部分未标记为已初始化
	if (p->array_flag) {
		int j = 0;
		for (j; j < p->array_count - 1; ++j)
			p->part_init[j] = 1;
	}
}



int string_value(char* str) {			//将字符转换为整数值
	int length = strlen(str);
	int i = 0, value = 0;
	for (i; i < length; ++i) {			//转换数组长度
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

void identv_array_part_storage(variable* pvar) {	//此变量为数组,置其余数组成员为已初始化
	if (pvar->array_count[pvar->row] - 1 > 0) {
		pvar->part[pvar->row] = (array_next*)calloc(1, sizeof(array_next));
		pvar->part[pvar->row]->init_flag = (int*)calloc(pvar->array_count[pvar->row] - 1, sizeof(int));
	}
}