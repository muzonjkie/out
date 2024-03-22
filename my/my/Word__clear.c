#include "head.h"




void Inithashtable(Key_Word keywords[], int kw_length, Key_Word* kword_hashtable[])			//初始化哈希表
{
	int i;
	Key_Word* temp;
	for (i = 0; i < kw_length - 1; ++i) {			//最后一个元素不带字符串，不做处理
		if(NULL == kword_hashtable[elf_hash(keywords[i].spell)])
			kword_hashtable[elf_hash(keywords[i].spell)] = keywords + i;
		else {
			temp = kword_hashtable[elf_hash(keywords[i].spell)];
			kword_hashtable[elf_hash(keywords[i].spell)] = keywords + i;
			kword_hashtable[elf_hash(keywords[i].spell)]->next = temp;
		}
	}
}



int elf_hash(char* key)					//返回哈希表下标
{
	int h = 0, g;
	while (*key)
	{
		h = (h << 4) + *key++;
		g = h & 0xf0000000;
		if (g)
			h ^= g >> 24;
		h &= ~g;
	}
	return h % maxsize;
}



void printf_words(words* array) {
	int k=0;
	while (k<= array->row) {
		++k;
		//	printf("%s\n", string);				
		Key_Word* p = array->list[k];
		while (p) {
			printf_color(p);
			p = p->next;
		}
		printf("\n");
	}
}

void printf_color(Key_Word* x)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (x->KwCode >= Kw_identv) {		//变量名，或者函数名为灰色
		SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);
	}
	else if (x->KwCode >= Kw_notes) {			//注释为绿色
		SetConsoleTextAttribute(h, FOREGROUND_GREEN);
	}
	else if (x->KwCode >= Kw_cchar) {	//关键字、字符常量为蓝色		
		SetConsoleTextAttribute(h, FOREGROUND_BLUE);
	}
	else if (x->KwCode >= Kw_cint) {			//其它常量为紫色
		SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_RED);
	}
	else											//运算符为红色
		SetConsoleTextAttribute(h, FOREGROUND_RED);
	printf("%s", x->spell);
}


//不考虑define语句



void word_split(words* array, Key_Word* kword_hashtable[])			//每次传一行进来分析
{
	char string[1000] = { 0 };		//临时存一行字符串
	FILE* fp = fopen("text.txt", "r");
	if (NULL == fp) {
		perror("fopen:");
	}
	else {
		array->row = 0;	
		Key_Word* temp = NULL,*q=NULL;
		while (fgets(string, sizeof(string), fp)) {
			q = temp;
			if (string[0] == '\n')									//空行不处理
				continue;
			++array->row;					//array.list[0]弃置不用，与行号一一对应
			row = array->row;				//记录错误时的行号
			int i, j;
			int length = strlen(string);
			if (string[length - 1] == '\n') {
				length = length - 1;			//忽略行末的换行符
			}
			for (i = 0; i < length; ++i) {
				j = 0;												//每剥离出一个词重置j为零
				temp = (Key_Word*)calloc(1, sizeof(Key_Word));//存一个词
				if (isalpha(string[i]) || '_' == string[i]) {//变量名，函数名，也可能是关键字，必须以英文字母和下划线开头			
					while ((isalnum(string[i]) || '_' == string[i]) && i < length) {//变量名中可以为英文字母、数字和下划线
						temp->spell[j] = string[i];
						++j;
						++i;
					}
					if (i == length)									//不足以出现;
						longjmp(jmpbuf, lack_semicolon);			//缺少分号；
					--i;		//下次循环拿回空格
				}
				else if ('"' == string[i]) {//字符串常量，从"一直读到下一个"
					temp->spell[j] = string[i];		//存入
					++j;
					++i;
					while (string[i] && i < length) {//字符串常量没有遇到下一个双引号
						if ('"' == string[i])		//不考虑字符串中含有双引号
							break;
						temp->spell[j] = string[i];
						++j;
						++i;
					}
					if (i == length) {				//不足以出现"字符
						longjmp(jmpbuf, lack_quotation_mark);
					}
					temp->spell[j] = string[i];//右双引号也需要放进去	
					temp->KwCode = Kw_cstr;
					goto keep;
				}
				else if ('\'' == string[i]) {
					int pos = i;
					int n = 3;
					int w;
					for (w = 1; w <= n && i < length; ++w) {
						temp->spell[j] = string[i];
						++j;
						++i;
					}
					if (i == length) {				//不足以出现'字符
						longjmp(jmpbuf, lack_quotation_mark);
					}
					if (i == length - 1) {		//最后一个字符才是'
						longjmp(jmpbuf, lack_semicolon);
					}
					--i;							//回退到右'(如果是)
					if (string[i] != string[pos]) {		//错误的输入
						longjmp(jmpbuf, lack_quotation_mark);
					}
					temp->KwCode = Kw_cchar;
					goto keep;
				}
				else if ('/' == string[i] && '/' == string[i + 1]) {		//以下是前缀相同的处理
					while (string[i] && i < length) {//之后的都是注释
						temp->spell[j] = string[i];
						++j;
						++i;
					}
					temp->KwCode = Kw_notes;
					goto keep;
				}
				else if ('-' == string[i] && '>' == string[i + 1]) {
					int n = 2;
					int w;
					for (w = 1; w <= n; ++w) {
						temp->spell[j] = string[i];
						++j;
						++i;
					}
					--i;					//防止丢失字符
					if (i == length - 1 && ';' != string[i]) {		//最后一个字符
						longjmp(jmpbuf, lack_semicolon);
					}
				}
				else if ('=' == string[i] && '=' == string[i + 1]) {
					int n = 2;
					int w;
					for (w = 1; w <= n; ++w) {
						temp->spell[j] = string[i];
						++j;
						++i;
					}
					--i;					//防止丢失字符
					if (i == length - 1 && ';' != string[i]) {		//最后一个字符
						longjmp(jmpbuf, lack_semicolon);
					}
				}
				else if ('>' == string[i] && '=' == string[i + 1]) {
					int n = 2;
					int w;
					for (w = 1; w <= n; ++w) {
						temp->spell[j] = string[i];
						++j;
						++i;
					}
					--i;					//防止丢失字符
					if (i == length - 1 && ';' != string[i]) {		//最后一个字符
						longjmp(jmpbuf, lack_semicolon);
					}
				}
				else if ('<' == string[i] && '=' == string[i + 1]) {
					int n = 2;
					int w;
					for (w = 1; w <= n; ++w) {
						temp->spell[j] = string[i];
						++j;
						++i;
					}
					--i;					//防止丢失字符
					if (i == length - 1 && ';' != string[i]) {		//最后一个字符
						longjmp(jmpbuf, lack_semicolon);
					}
				}
				else if ('!' == string[i] && '=' == string[i + 1]) {
					int n = 2;
					int w;
					for (w = 1; w <= n; ++w) {
						temp->spell[j] = string[i];
						++j;
						++i;
					}
					--i;					//防止丢失字符
					if (i == length - 1 && ';' != string[i]) {		//最后一个字符
						longjmp(jmpbuf, lack_semicolon);
					}
				}
				else if ('&' == string[i] && '&' == string[i + 1]) {
					int n = 2;
					int w;
					for (w = 1; w <= n; ++w) {
						temp->spell[j] = string[i];
						++j;
						++i;
					}
					--i;					//防止丢失字符
					if (i == length - 1 && ';' != string[i]) {		//最后一个字符
						longjmp(jmpbuf, lack_semicolon);
					}
				}
				else if (ispunct(string[i]) || ' ' == string[i]) {//其余可打印标点和空格
					temp->spell[j] = string[i];
				}
				else if (isdigit(string[i])) {
					int flag = 1;
					while ((isdigit(string[i]) || ('.' == string[i] && flag)) && i < length) {		//上面已有判断，第一个字符不会是'.'
						temp->spell[j] = string[i];
						if ('.' == string[i]) {			//则是浮点数
							flag = 0;
							temp->KwCode = Kw_float;
						}
						++j;
						++i;
					}
					if (i == length)									//不老虑define
						longjmp(jmpbuf, lack_semicolon);			//缺少分号；
					if ((i == length - 1) && ';' != string[i])			//全行是数字的可能
						longjmp(jmpbuf, lack_semicolon);			//缺少分号；
					--i;					//回退，下次循环拿到该字符
					if (flag)				//未出现小数点
						temp->KwCode = Kw_cint;
					else
						temp->KwCode = Kw_cfloat;
					goto keep;
				}
				else if ('\t' == string[i]) {//tab键用四个空格代替
					int n = 4;
					int w;
					for (w = 1; w <= n; ++w) {
						temp->spell[j] = ' ';
						++j;
					}
				}
				Key_Word* p = kword_hashtable[elf_hash(temp->spell)];
				while (p && (0 != strcmp(temp->spell, p->spell))) {//对剥离出的字符，若有编码，找到对应编码以便染色
					p = p->next;
				}
				int w = i + 1;				//前面有回退操作，这里拿到下一次循坏开始时的字符;
				while ((' ' == string[w] || '\t' == string[i]) && w < (length - 1)) {	//最接近的非空格符，
					w++;
				}
				if (p)						//若找到对应编码
					temp->KwCode = p->KwCode;
				else if ('(' == string[w]) {	//没匹配上但往后最近一个非空字符为此，那么为函数
					temp->KwCode = Kw_identf;
				}
				else
					temp->KwCode = Kw_identv;		//则是变量

			keep:						//使染色正确
				if (NULL == array->list[array->row])
					array->list[array->row] = temp;
				else {						//同一行的词链到一行
					Key_Word* pos = array->list[array->row];
					Key_Word* pre = pos;
					while (pos) {			//pos为NULL，pre指向前驱
						pre = pos;
						pos = pos->next;
					}
					pre->next = temp;
					temp->prior = pre;
				}
			}
			if (array->row > 1) {
				array->list[array->row]->prior = q;
				q->next = array->list[array->row];
			}
			temp->row_tail_flag = 1;
			word_expand(array);					//空间是否还足够
		}
	}
}

void word_storage(words* array)				//动态指针数组
{

	array->list = (Key_Word**)calloc(line, sizeof(Key_Word*));
	array->count = line;
}


void word_expand(words* array)				//空间不够扩容
{
	if (array->row + 1 == array->count) {			//若行数已存满
		int len = array->count;
		array->count *= 2;
		array->list = (Key_Word**)realloc(array->list, sizeof(Key_Word*) * array->count);
		memset(array->list + len, 0, sizeof(Key_Word*) * len);		//新空间初始化
	}
}


void print_hashtable(Key_Word* kword_hashtable[])					//看哈希冲突
{
	int i;
	for (i = 0; i < maxsize; ++i) {
		if (kword_hashtable[i]) {
			Key_Word* temp = kword_hashtable[i];
			while (temp){
				printf("%s\t", temp->spell);
				temp = temp->next;
			}
			printf("\n");
		}
	}
}