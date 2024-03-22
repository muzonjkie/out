#include "head.h"




void Inithashtable(Key_Word keywords[], int kw_length, Key_Word* kword_hashtable[])			//��ʼ����ϣ��
{
	int i;
	Key_Word* temp;
	for (i = 0; i < kw_length - 1; ++i) {			//���һ��Ԫ�ز����ַ�������������
		if(NULL == kword_hashtable[elf_hash(keywords[i].spell)])
			kword_hashtable[elf_hash(keywords[i].spell)] = keywords + i;
		else {
			temp = kword_hashtable[elf_hash(keywords[i].spell)];
			kword_hashtable[elf_hash(keywords[i].spell)] = keywords + i;
			kword_hashtable[elf_hash(keywords[i].spell)]->next = temp;
		}
	}
}



int elf_hash(char* key)					//���ع�ϣ���±�
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
	if (x->KwCode >= Kw_identv) {		//�����������ߺ�����Ϊ��ɫ
		SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);
	}
	else if (x->KwCode >= Kw_notes) {			//ע��Ϊ��ɫ
		SetConsoleTextAttribute(h, FOREGROUND_GREEN);
	}
	else if (x->KwCode >= Kw_cchar) {	//�ؼ��֡��ַ�����Ϊ��ɫ		
		SetConsoleTextAttribute(h, FOREGROUND_BLUE);
	}
	else if (x->KwCode >= Kw_cint) {			//��������Ϊ��ɫ
		SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_RED);
	}
	else											//�����Ϊ��ɫ
		SetConsoleTextAttribute(h, FOREGROUND_RED);
	printf("%s", x->spell);
}


//������define���



void word_split(words* array, Key_Word* kword_hashtable[])			//ÿ�δ�һ�н�������
{
	char string[1000] = { 0 };		//��ʱ��һ���ַ���
	FILE* fp = fopen("text.txt", "r");
	if (NULL == fp) {
		perror("fopen:");
	}
	else {
		array->row = 0;	
		Key_Word* temp = NULL,*q=NULL;
		while (fgets(string, sizeof(string), fp)) {
			q = temp;
			if (string[0] == '\n')									//���в�����
				continue;
			++array->row;					//array.list[0]���ò��ã����к�һһ��Ӧ
			row = array->row;				//��¼����ʱ���к�
			int i, j;
			int length = strlen(string);
			if (string[length - 1] == '\n') {
				length = length - 1;			//������ĩ�Ļ��з�
			}
			for (i = 0; i < length; ++i) {
				j = 0;												//ÿ�����һ��������jΪ��
				temp = (Key_Word*)calloc(1, sizeof(Key_Word));//��һ����
				if (isalpha(string[i]) || '_' == string[i]) {//����������������Ҳ�����ǹؼ��֣�������Ӣ����ĸ���»��߿�ͷ			
					while ((isalnum(string[i]) || '_' == string[i]) && i < length) {//�������п���ΪӢ����ĸ�����ֺ��»���
						temp->spell[j] = string[i];
						++j;
						++i;
					}
					if (i == length)									//�����Գ���;
						longjmp(jmpbuf, lack_semicolon);			//ȱ�ٷֺţ�
					--i;		//�´�ѭ���ûؿո�
				}
				else if ('"' == string[i]) {//�ַ�����������"һֱ������һ��"
					temp->spell[j] = string[i];		//����
					++j;
					++i;
					while (string[i] && i < length) {//�ַ�������û��������һ��˫����
						if ('"' == string[i])		//�������ַ����к���˫����
							break;
						temp->spell[j] = string[i];
						++j;
						++i;
					}
					if (i == length) {				//�����Գ���"�ַ�
						longjmp(jmpbuf, lack_quotation_mark);
					}
					temp->spell[j] = string[i];//��˫����Ҳ��Ҫ�Ž�ȥ	
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
					if (i == length) {				//�����Գ���'�ַ�
						longjmp(jmpbuf, lack_quotation_mark);
					}
					if (i == length - 1) {		//���һ���ַ�����'
						longjmp(jmpbuf, lack_semicolon);
					}
					--i;							//���˵���'(�����)
					if (string[i] != string[pos]) {		//���������
						longjmp(jmpbuf, lack_quotation_mark);
					}
					temp->KwCode = Kw_cchar;
					goto keep;
				}
				else if ('/' == string[i] && '/' == string[i + 1]) {		//������ǰ׺��ͬ�Ĵ���
					while (string[i] && i < length) {//֮��Ķ���ע��
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
					--i;					//��ֹ��ʧ�ַ�
					if (i == length - 1 && ';' != string[i]) {		//���һ���ַ�
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
					--i;					//��ֹ��ʧ�ַ�
					if (i == length - 1 && ';' != string[i]) {		//���һ���ַ�
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
					--i;					//��ֹ��ʧ�ַ�
					if (i == length - 1 && ';' != string[i]) {		//���һ���ַ�
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
					--i;					//��ֹ��ʧ�ַ�
					if (i == length - 1 && ';' != string[i]) {		//���һ���ַ�
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
					--i;					//��ֹ��ʧ�ַ�
					if (i == length - 1 && ';' != string[i]) {		//���һ���ַ�
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
					--i;					//��ֹ��ʧ�ַ�
					if (i == length - 1 && ';' != string[i]) {		//���һ���ַ�
						longjmp(jmpbuf, lack_semicolon);
					}
				}
				else if (ispunct(string[i]) || ' ' == string[i]) {//����ɴ�ӡ���Ϳո�
					temp->spell[j] = string[i];
				}
				else if (isdigit(string[i])) {
					int flag = 1;
					while ((isdigit(string[i]) || ('.' == string[i] && flag)) && i < length) {		//���������жϣ���һ���ַ�������'.'
						temp->spell[j] = string[i];
						if ('.' == string[i]) {			//���Ǹ�����
							flag = 0;
							temp->KwCode = Kw_float;
						}
						++j;
						++i;
					}
					if (i == length)									//������define
						longjmp(jmpbuf, lack_semicolon);			//ȱ�ٷֺţ�
					if ((i == length - 1) && ';' != string[i])			//ȫ�������ֵĿ���
						longjmp(jmpbuf, lack_semicolon);			//ȱ�ٷֺţ�
					--i;					//���ˣ��´�ѭ���õ����ַ�
					if (flag)				//δ����С����
						temp->KwCode = Kw_cint;
					else
						temp->KwCode = Kw_cfloat;
					goto keep;
				}
				else if ('\t' == string[i]) {//tab�����ĸ��ո����
					int n = 4;
					int w;
					for (w = 1; w <= n; ++w) {
						temp->spell[j] = ' ';
						++j;
					}
				}
				Key_Word* p = kword_hashtable[elf_hash(temp->spell)];
				while (p && (0 != strcmp(temp->spell, p->spell))) {//�԰�������ַ������б��룬�ҵ���Ӧ�����Ա�Ⱦɫ
					p = p->next;
				}
				int w = i + 1;				//ǰ���л��˲����������õ���һ��ѭ����ʼʱ���ַ�;
				while ((' ' == string[w] || '\t' == string[i]) && w < (length - 1)) {	//��ӽ��ķǿո����
					w++;
				}
				if (p)						//���ҵ���Ӧ����
					temp->KwCode = p->KwCode;
				else if ('(' == string[w]) {	//ûƥ���ϵ��������һ���ǿ��ַ�Ϊ�ˣ���ôΪ����
					temp->KwCode = Kw_identf;
				}
				else
					temp->KwCode = Kw_identv;		//���Ǳ���

			keep:						//ʹȾɫ��ȷ
				if (NULL == array->list[array->row])
					array->list[array->row] = temp;
				else {						//ͬһ�еĴ�����һ��
					Key_Word* pos = array->list[array->row];
					Key_Word* pre = pos;
					while (pos) {			//posΪNULL��preָ��ǰ��
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
			word_expand(array);					//�ռ��Ƿ��㹻
		}
	}
}

void word_storage(words* array)				//��ָ̬������
{

	array->list = (Key_Word**)calloc(line, sizeof(Key_Word*));
	array->count = line;
}


void word_expand(words* array)				//�ռ䲻������
{
	if (array->row + 1 == array->count) {			//�������Ѵ���
		int len = array->count;
		array->count *= 2;
		array->list = (Key_Word**)realloc(array->list, sizeof(Key_Word*) * array->count);
		memset(array->list + len, 0, sizeof(Key_Word*) * len);		//�¿ռ��ʼ��
	}
}


void print_hashtable(Key_Word* kword_hashtable[])					//����ϣ��ͻ
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