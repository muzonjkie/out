#include "head.h"




//----------------------�⼸���ں���������������;
int stack_Kw_begin = 0;		//�洢{
int stack_Kw_openpa = 0;	//�洢(
int stack_Kw_if = 0;		//�洢 if �������else��else if
int Kw_begin_grade = 0;		//�ڵڼ���{}��


Key_Word* pcur = NULL;//ָ��ʼ��Ҫ�����Ĵ�

////�ⲿ����
void External_dec(variable* pvar, variable* pvar_in, function* pfunc) {   //�˳��ⲿ����ʱ pcurΪ��ǰ������:������} 
	have_space_judge();
	if (NULL == pcur) {//�ߵ����ͽ�����
		return;
	}
	else if (Kw_notes == pcur->KwCode) {//�Ƿ���ע��
	}
	else if (Kw_semicolon == pcur->KwCode) {//�Ƿ��Ƿֺ�
	}
	else if (Kw_hash == pcur->KwCode) {//�Ƿ���#��
		quote_dispose();
	}
	else if (Kw_struct == pcur->KwCode) {//�Ƿ���struct��
		struct_dispose(pvar, pvar_in, pfunc, 0);
	}
	else if (Is_type() || Kw_void == pcur->KwCode) {//�Ƿ�������
		type_dispose(pvar, pvar_in, pfunc);
	}
	else if (Kw_identv == pcur->KwCode) {			//�Ƿ��Ǳ�����
		identv_dispose(pvar);
	}
	else {

	}
	next_node();
	External_dec(pvar, pvar_in, pfunc);
}


void quote_dispose()							//����ͷ�ļ�����
{
	if (main_flag)								//��main�����Ѿ�����֮����include��䣬����
		longjmp(jmpbuf, headfile_error);
	next_node();
	have_space_judge();
	if (Kw_include != pcur->KwCode)
		longjmp(jmpbuf, headfile_error);
	next_node();
	have_space_judge();
	if (Kw_lt == pcur->KwCode || Kw_cstr == pcur->KwCode) {	//Ҫô��<��ͷ��Ҫô��"(���ִʴ����Ϊ�ַ�������)
		if (Kw_lt == pcur->KwCode) {
			next_node();
			//	����ȱһ���ж��Ƿ��Ǳ�׼ͷ�ļ��ĺ���,���������ݴ���
			if (Kw_identv != pcur->KwCode)		//����ʱת���˱�������
				longjmp(jmpbuf, headfile_error);
			next_node();
			if (Kw_dot != pcur->KwCode)			// .����
				longjmp(jmpbuf, headfile_error);
			next_node();
			if (0 != strcmp("h", pcur->spell))				// h��
				longjmp(jmpbuf, headfile_error);
			next_node();
			have_space_judge();					//�����пո�
			if (Kw_gt != pcur->KwCode)			// >��
				longjmp(jmpbuf, headfile_error);
		}
		Key_Word* temp = pcur;
		while (1 != pcur->row_tail_flag) {			//���������β���ߵ���β
			if (Kw_tabs == pcur->KwCode || Kw_space == pcur->KwCode)
				;
			else
				longjmp(jmpbuf, headfile_error);
			next_node();
		}
		if (temp == pcur)		//������β
			;
		else if (Kw_tabs == pcur->KwCode || Kw_space == pcur->KwCode)	//��β
			;
		else															//�����б�Ķ���
			longjmp(jmpbuf, headfile_error);
	}
	else {								//���ô���
		longjmp(jmpbuf, headfile_error);
	}
}


void struct_dispose(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {
	variable* pnow = NULL;
	if (in_func_flag)//�������ڵ���
		pnow = pvar_in;
	else//�ⲿ����
		pnow = pvar;
	Key_Word* pa = pcur;				//��¼��ǰstruct;
	next_node();
	if (!have_space_judge())				//δ���ֿո�
		longjmp(jmpbuf, lack_space);
	if (Kw_identv != pcur->KwCode)
		longjmp(jmpbuf, lack_identv);
	int length = strlen(pa->spell);
	strcpy(pnow->type[pnow->row], pa->spell);
	strcpy(pnow->type[pnow->row] + length, pcur->spell);		//��struct��������������������µı�������
	int mark = pnow->row;			//��ֹ������ʹpnow->row���Ӷ�ʧ����
	next_node();
	int have = have_space_judge();				//�Ƿ��пո��ڿ��ܵĽṹ�����ͺͽṹ�������
	if (Kw_begin == pcur->KwCode) {				//�ṹ����������
		next_node();
		struct_statement(pvar, pvar_in, pfunc, (member*)NULL, in_func_flag);			//	����ô˽ṹ������
		if (statement_valid_ok_judge(pnow))//�������Ƿ�֮ǰ�Ѿ�������
			longjmp(jmpbuf, repeat_struct_statement);
		pnow->grade[pnow->row] = Kw_begin_grade;
		pnow->row++;
		variable_expand(pnow);				//������Ҫ����
		next_node();
		have_space_judge();
		if (Kw_identv == pcur->KwCode) {
			goto keep;						//��󻹿��ܻ��нṹ���������
		}
		else if (Kw_semicolon == pcur->KwCode) {	//�ýṹ�崦�����

		}
		else
			longjmp(jmpbuf, struct_error);
	}
	else if (Kw_identv == pcur->KwCode) {		//�ṹ���������			
		if (!have)								//δ���ֿո�
			longjmp(jmpbuf, lack_space);
	keep: {
		strcpy(pnow->type[pnow->row], pnow->type[mark]);			//��ֹ��������pnow->row�б仯
		strcpy(pnow->word[pnow->row], pcur->spell);					//���������
		pnow->grade[pnow->row] = Kw_begin_grade;
		int posi = 0;													//��¼�ҵ�ͬһ���͵�λ�ñ��
		if (!((in_func_flag && (posi = identv_valid_ok_judge(pvar_in))) || (posi = identv_valid_ok_judge(pvar))))/*���ں����������ھ�
																		�������洢����Ѱ���Ƿ��иýṹ�������������Ҳ����ٵ�ȫ����ȥ��*/
			longjmp(jmpbuf, unknown_struct_type);//�������ڸýṹ������
		if (repeat_judge(pnow))	//�Ƿ���������
			longjmp(jmpbuf, var_repeat_definition);
		if (in_func_flag && 1 == Kw_begin_grade) {//�ԱȺ�������
			if (cmp_para(pfunc, pnow))//�����뺯�������Ƿ�������
				longjmp(jmpbuf, var_repeat_definition);
		}
		same_struct_mem_copy(pnow, posi);								//ͬ��Ϊһ������
		next_node();
		struct_init(pvar, pvar_in, pfunc, 0, 0, in_func_flag);					//��ʼ����һ/����ṹ����������飩
		}
	}
	else {										//�������
		longjmp(jmpbuf, struct_error);
	}

}


void struct_statement(variable* pvar, variable* pvar_in, function* pfunc, member* temp, int in_func_flag) {		//����ṹ���ڲ���Ա
	have_space_judge();
	variable* pnow = NULL;
	if (in_func_flag)//�������ڵ���
		pnow = pvar_in;
	else//�ⲿ����
		pnow = pvar;
	if (Is_type()) {								//(char��int��float)
		Key_Word* memo = pcur;
		next_node();
		if (!have_space_judge())			//δ���ֿո�
			longjmp(jmpbuf, lack_space);
		struct_statement_one(pvar, pvar_in, pfunc, temp, memo, in_func_flag);
		next_node();
		struct_statement(pvar, pvar_in, pfunc, temp, in_func_flag);	//�����Ƿ�������Ľṹ���ڲ���Ա
	}
	else if (Kw_semicolon == pcur->KwCode) {			//���Ƿֺſ��ܻ��г�Ա
		next_node();
		struct_statement(pvar, pvar_in, pfunc, temp, in_func_flag);				//�ݹ����
	}
	else if (Kw_end == pcur->KwCode) {					//�����ݹ����
		if (!pnow->mem[pnow->row])					//�ṹ���ڲ��޳�Ա
			longjmp(jmpbuf, struct_lack_mem);
	}
	else		//�����ͷǷֺŷ��Ҵ����ţ�����
		longjmp(jmpbuf, lack_end);
}


void struct_statement_one(variable* pvar, variable* pvar_in, function* pfunc, member* temp, Key_Word* memo, int in_func_flag) {			//������';' ���ߴ���
	have_space_judge();
	variable* pnow = NULL;
	if (in_func_flag)//�������ڵ���
		pnow = pvar_in;
	else//�ⲿ����
		pnow = pvar;
	if (Kw_identv == pcur->KwCode) {
		member* pnew = (member*)calloc(1, sizeof(member));
		strcpy(pnew->type, memo->spell);//��������
		if (struct_mem_repeat_judge(pnow, pnow->row))				//�ṹ���ڲ���Ա��������
			longjmp(jmpbuf, var_repeat_definition);
		strcpy(pnew->word, pcur->spell);	//���ϳ�Ա��������		
		if (NULL == pnow->mem[pnow->row]) {			//��������ǵ�һ����Ա
			pnow->mem[pnow->row] = pnew;
		}
		else {									//�Ǿ���֮��ĳ�Ա
			member* next = pnow->mem[pnow->row];
			while (next) {					//��tempָ�����е����һ����Ա
				temp = next;
				next = next->next;
			}
			temp->next = pnew;			//����
		}
		next_node();
		temp = pnew;					//�������һ����Ա
		struct_statement_two(pvar, pvar_in, pfunc, 0, temp, memo, in_func_flag);				//�Ƿ��г�Ա
	}
	else if (Kw_semicolon == pcur->KwCode) {				//��ֹ�ޱ�����struct_statement_two()�������˺�������
		Key_Word* p = pcur;
		p = p->prior;
		while (Kw_space == p->KwCode || Kw_tabs == p->KwCode) {
			p = p->prior;
		}
		if (Kw_closebr == pcur->KwCode || Kw_identv == pcur->KwCode) {
			//ǰ������Ǳ���,���ñ���Ϊ����,���һ����Ϊ']'
		}
		else
			longjmp(jmpbuf, lack_identv);
	}
	else
		longjmp(jmpbuf, lack_identv);
}


void struct_statement_two(variable* pvar, variable* pvar_in, function* pfunc, int from, member* temp, Key_Word* memo, int in_func_flag) {
	have_space_judge();
	variable* pnow = NULL;
	if (in_func_flag)//�������ڵ���
		pnow = pvar_in;
	else//�ⲿ����
		pnow = pvar;
	if (Kw_comma == pcur->KwCode) {					//������ܻ��б���;pnow->init_flag[pnow->row]��ʼΪ�㼴δ��ʼ��		
		next_node();
		struct_statement_one(pvar, pvar_in, pfunc, temp, memo, in_func_flag);
	}
	else if (Kw_semicolon == pcur->KwCode) {		//�˽ṹ������������

	}
	else if (Kw_openbr == pcur->KwCode) {			//�����������ţ�������
		if (1 == from)							//'[]'����'[]'�����󣨲�֧�ֶ�ά���飩
			longjmp(jmpbuf, array_error);
		next_node();
		have_space_judge();
		if (Kw_cint != pcur->KwCode)		//���������Ϊ������
			longjmp(jmpbuf, array_error);
		temp->array_flag = 1;
		temp->array_count = string_value(pcur->spell);		//���ַ�ת��Ϊ����ֵ
		if (temp->array_count <= 0)			//���鳤�Ȳ���Ϊ�����
			longjmp(jmpbuf, array_error);
		next_node();
		have_space_judge();
		if (Kw_closebr != pcur->KwCode)		//��������
			longjmp(jmpbuf, lack_closebr);
		struct_mem_array_part_storage(temp);	//���������Ա
		next_node();
		struct_statement_two(pvar, pvar_in, pfunc, 1, temp, memo, in_func_flag);					//']'����һ���ǿ��ַ�	,ҪôΪ',',ҪôΪ';'	
	}
	else if (Kw_semicolon == pcur->KwCode) {			//������Ӵˣ��ɽ���

	}
	else
		longjmp(jmpbuf, expression_error);
}


void struct_init(variable* pvar, variable* pvar_in, function* pfunc, int from, int assign, int in_func_flag) {//����ṹ���ڲ���Ա��ʼ����from�Ǳ�Ǵ˺������ǽ�����
	have_space_judge();
	variable* pnow = NULL;
	if (in_func_flag)//�������ڵ���
		pnow = pvar_in;
	else//�ⲿ����
		pnow = pvar;
	if (Kw_comma == pcur->KwCode) {					//������ܻ��б���;pnow->init_flag[pnow->row]��ʼΪ�㼴δ��ʼ��		
		pnow->row++;
		variable_expand(pnow);				//������Ҫ����
		next_node();
		have_space_judge();
		if (Kw_identv == pcur->KwCode) {
			strcpy(pnow->word[pnow->row], pcur->spell);				//���������
			strcpy(pnow->type[pnow->row], pnow->type[pnow->row - 1]);		//ǰ������������һ��
			same_struct_mem_copy(pnow, pnow->row - 1);			//��Ա��һ�µ�
			pnow->grade[pnow->row] = Kw_begin_grade;
			if (repeat_judge(pnow))						//�Ƿ�Ϊ�ض������
				longjmp(jmpbuf, var_repeat_definition);
			next_node();
			struct_init(pvar, pvar_in, pfunc, 0, 0, in_func_flag);
		}
		else											//','�󲻸�������������
			longjmp(jmpbuf, lack_semicolon);
	}
	else if (Kw_semicolon == pcur->KwCode) {		//�˽ṹ������������
		pnow->row++;
		variable_expand(pnow);
	}
	else if (Kw_openbr == pcur->KwCode) {			//�����������ţ�������
		if (1 == from)							//'[]'����'[]'�����󣨲�֧�ֶ�ά���飩
			longjmp(jmpbuf, array_error);
		next_node();
		have_space_judge();
		if (Kw_cint != pcur->KwCode)		//���������Ϊ������
			longjmp(jmpbuf, array_error);
		pnow->array_flag[pnow->row] = 1;
		pnow->array_count[pnow->row] = string_value(pcur->spell);		//���ַ�ת��Ϊ����ֵ
		next_node();
		have_space_judge();
		if (Kw_closebr != pcur->KwCode)		//��������
			longjmp(jmpbuf, lack_closebr);
		struct_array_part_storage(pnow);			//���������Ա
		next_node();
		struct_init(pvar, pvar_in, pfunc, 1, 0, in_func_flag);					//']'����һ���ǿ��ַ�		
	}
	else if (Kw_assign == pcur->KwCode) {			//'='��ʼ������
		if (1 == assign)
			longjmp(jmpbuf, expression_error);
		next_node();
		have_space_judge();
		if (pnow->array_flag[pnow->row]) {			//�ṹ������
			more_struct_mem_init(pvar, pvar_in, pfunc, in_func_flag);
			have_space_judge();
			struct_init(pvar, pvar_in, pfunc, 1, 1, in_func_flag);				//���ܻ��нṹ�������Ҫ����
		}
		else {										//�����ṹ�����
			struct_mem_init(pvar, pvar_in, pfunc, in_func_flag);				//��ʼ����һ���ṹ�����	
			have_space_judge();
			struct_init(pvar, pvar_in, pfunc, 1, 1, in_func_flag);				//���ܻ��нṹ�������Ҫ����
		}
	}
	else
		longjmp(jmpbuf, expression_error);
}


void struct_mem_init(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {		//����˺���ʱpcurָ��'='���һ���ǿ��ַ�
	have_space_judge();
	variable* pnow = NULL;
	if (in_func_flag)//�������ڵ���
		pnow = pvar_in;
	else//�ⲿ����
		pnow = pvar;
	if (Kw_begin == pcur->KwCode) {
		++stack_Kw_begin;						//����һ��{
		member* p = pnow->mem[pnow->row];
		next_node();
		while (0 < stack_Kw_begin) {
			struct_mem_init_one(pvar, pvar_in, pfunc, &p, in_func_flag);
			pnow->init_flag[pnow->row] = 1;		//�˽ṹ������ѳ�ʼ��
			if (p)
				p = p->next;
			if (NULL == p)
				break;
		}
		if (stack_Kw_begin)						//����Ϊ�㣬˵������'}'(���к����ж�����С���㣬�ᱨ��)
			longjmp(jmpbuf, lack_end);
		if (p) {								//������Ľṹ���Աδ��ֵ��������Ϊ�ѳ�ʼ��
			p = p->next;
			while (p) {
				p->init_flag = 1;
				if (p->array_flag) {			//�Գ�Ա�е������Ա����Ϊ�ѳ�ʼ��
					int i = 0;
					for (i; i < p->array_count - 1; ++i)
						p->part_init[i] = 1;
				}
				p = p->next;
			}
		}
	}
	else
		longjmp(jmpbuf, expression_error);
}


void struct_mem_init_one(variable* pvar, variable* pvar_in, function* pfunc, member** p, int in_func_flag) {
	have_space_judge();
	variable* pnow = NULL;
	if (in_func_flag)//�������ڵ���
		pnow = pvar_in;
	else//�ⲿ����
		pnow = pvar;
	if (Kw_begin == pcur->KwCode) {			//'{'��
		++stack_Kw_begin;
		if (stack_Kw_begin > 2)
			longjmp(jmpbuf, expression_error);
		next_node();
		struct_mem_init_one(pvar, pvar_in, pfunc, p, in_func_flag);
	}
	else if (Is_this(Kw_cchar) || Is_this(Kw_cint) || Is_this(Kw_cfloat) || Is_this(Kw_not) || Is_this(Kw_minus) || Is_this(Kw_openpa)) {
		(*p)->init_flag = 1;												//��Ա����������ֵ����һ��
		expression(pvar, pvar_in, pfunc, in_func_flag);
		struct_mem_init_two(pvar, pvar_in, pfunc, p, 1, 0, in_func_flag);			//����ֻ��Ϊ','��'}'		
	}
	else if (Kw_cstr == pcur->KwCode) {
		if (Is_fit_type("char") && (*p)->array_flag && (0 == (*p)->init_flag)) {//�ַ���,�ַ�����ֻ�ܳ�ʼ��һ��
			int length = strlen(pcur->spell) - 2;							//�۳�����'"'�ĳ���
			if (length > (*p)->array_count) {				//������Խ��
				longjmp(jmpbuf, array_error);
			}
			else {					//�ɹ���ʼ��
				(*p)->init_flag = 1;
				next_node();
				struct_mem_init_two(pvar, pvar_in, pfunc, p, (*p)->array_count, 0, in_func_flag);			//����ֻ��Ϊ','��'}'�Ҵ˳�Ա�ѳ�ʼ�����
			}
		}
		else if (Is_fit_type("char") || !(*p)->array_flag) {
			longjmp(jmpbuf, type_error);
		}
		else {						//�Ѿ���ʼ������
			longjmp(jmpbuf, expression_error);
		}

	}
	else							//���Ͳ�һ�£�����
		longjmp(jmpbuf, expression_error);
}


void struct_mem_init_two(variable* pvar, variable* pvar_in, function* pfunc, member** p, int count, int flag, int in_func_flag) {//count��¼�ṹ���Ա���������ѳ�ʼ��������Ա������Խ��
	have_space_judge();									//	flag����ڽ����ڲ���Ա��������ʱ�Ƿ���ֹ�'{'
	variable* pnow = NULL;
	if (in_func_flag)//�������ڵ���
		pnow = pvar_in;
	else//�ⲿ����
		pnow = pvar;
	if (Kw_comma == pcur->KwCode) {
		if (0 == (*p)->init_flag) {					//������"{3,}"��ʹ�л�����һ��Ա
			next_node();
			struct_mem_init_one(pvar, pvar_in, pfunc, p, in_func_flag);
		}
		else if ((*p)->array_flag && count < (*p)->array_count) {			//��Ϊ������δԽ�磬���������Ƿ���ų�ʼ�������Ա
			next_node();
			struct_mem_init_three(pvar, pvar_in, pfunc, p, count, 0, flag, in_func_flag);
		}
		else {			//�������鵫�ѳ�ʼ���������鵫�����Ա���ѳ�ʼ�������ػ���һ����Ա����
			next_node();
			Key_Word* q = pcur;
			while (q && (Kw_tabs == q->KwCode || Kw_space == q->KwCode)) {
				q = q->next;
			}
			if (Kw_end == q->KwCode) {			//������"{3,}",�л�����һ��Ա
				Is_init_too_more(flag);
				struct_mem_array_part(*p);
				--stack_Kw_begin;
				pcur = q;
				next_node();
				(*p) = (*p)->next;
				if (*p && stack_Kw_begin)
					struct_mem_init_two(pvar, pvar_in, pfunc, p, 0, flag, in_func_flag);//�˱�������ʼ��,����һ������ֻ��Ϊ','��'}',��Ϊ',',ͨ��������һ
			}
			if ((*p)->array_flag && count == (*p)->array_count && stack_Kw_begin > 1 && Kw_identv == q->KwCode)	//��ʼֵ�趨�����
				longjmp(jmpbuf, init_value_more);
		}
	}
	else if (Kw_end == pcur->KwCode) {
		Is_init_too_more(flag);
		struct_mem_array_part(*p);
		--stack_Kw_begin;
		if (0 == stack_Kw_begin) {			//ƥ��ɹ��������ṹ���ʼ�����
			next_node();
		}
		else if (stack_Kw_begin < 0)
			longjmp(jmpbuf, lack_begin);
		else {
			next_node();
			struct_mem_init_two(pvar, pvar_in, pfunc, p, (*p)->array_count, flag, in_func_flag);//����ֻ��Ϊ','��'}';��(*p)->array_count����Ϊ�˱����������ַ�������
		}												//���ǵ�����,��Ӱ�죻����δ��ʼ��������飬������'}',�������ʼ����
	}
	else
		longjmp(jmpbuf, expression_error);
}


void struct_mem_init_three(variable* pvar, variable* pvar_in, function* pfunc, member** p, int count, int from, int flag, int in_func_flag) {//�������Ա����	  //from�����Ǵ��Ľ���˺�����
	have_space_judge();
	variable* pnow = NULL;
	if (in_func_flag)//�������ڵ���
		pnow = pvar_in;
	else//�ⲿ����
		pnow = pvar;
	if (Is_this(Kw_cchar) || Is_this(Kw_cint) || Is_this(Kw_cfloat) || Is_this(Kw_not) || Is_this(Kw_minus) || Is_this(Kw_openpa)) {
		expression(pvar, pvar_in, pfunc, in_func_flag);
		(*p)->init_flag = 1;														//��Ա����������ֵ����һ��
		++count;
		struct_mem_init_two(pvar, pvar_in, pfunc, p, count, flag, in_func_flag);		//����ֻ��Ϊ','��'}'
	}
	else if (Kw_end == pcur->KwCode) {
		if (1 == from)						//����struct_mem_init_three()�����ģ���������ƥ���ڲ�Ϊ��
			longjmp(jmpbuf, expression_error);
		Is_init_too_more(flag);
		struct_mem_array_part(*p);
		--stack_Kw_begin;
		if (0 == stack_Kw_begin) {
			next_node();
		}
		else if (stack_Kw_begin < 0)
			longjmp(jmpbuf, lack_begin);
		else {
			next_node();
			struct_mem_init_two(pvar, pvar_in, pfunc, p, count, flag, in_func_flag);		//����ֻ��Ϊ','��'}'
		}
	}
	else if (Kw_begin == pcur->KwCode) {
		++stack_Kw_begin;
		if (stack_Kw_begin > 2)
			longjmp(jmpbuf, expression_error);
		next_node();
		struct_mem_init_three(pvar, pvar_in, pfunc, p, count, 1, 1, in_func_flag);
	}
	else
		longjmp(jmpbuf, expression_error);
}


void more_struct_mem_init(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {	//�ṹ�����鴦��	//����˺���ʱpcurָ��'='���һ���ǿ��ַ�
	have_space_judge();
	variable* pnow = NULL;
	if (in_func_flag)//�������ڵ���
		pnow = pvar_in;
	else//�ⲿ����
		pnow = pvar;
	if (Kw_begin == pcur->KwCode) {
		++stack_Kw_begin;						//����һ��{
		member* p = pnow->mem[pnow->row];
		int i = 0;
		next_node();
		while (0 < stack_Kw_begin) {
			more_struct_mem_init_one(pvar, pvar_in, pfunc, &p, &i, 0, in_func_flag);
			pnow->init_flag[pnow->row] = 1;		//�˽ṹ������ѳ�ʼ��
			if (i < pnow->array_count[pnow->row] - 1) {		//�����л���һ���ṹ��
				p = pnow->part[pnow->row]->mem[i];
				pnow->part[pnow->row]->init_flag[i] = 1;
				++i;
			}
			else
				break;
		}
		if (stack_Kw_begin)						//����Ϊ�㣬˵������'}'(���к����ж�����С���㣬�ᱨ��)
			longjmp(jmpbuf, lack_end);
		if (p) {								//��p�������������ޱ���,˵��ȫ���ṹ�������Ա�е��ڲ���Ա���ѱ�ǳ�ʼ��
			for (i; i < pnow->array_count[pnow->row] - 1; ++i) {
				pnow->part[pnow->row]->init_flag[i] = 1;			//��ǽṹ���ʼ��
				p = pnow->part[pnow->row]->mem[i];		//�׸��ڲ���Ա
				struct_rest_mem(p);
			}
		}
	}
	else
		longjmp(jmpbuf, expression_error);
}


void more_struct_mem_init_one(variable* pvar, variable* pvar_in, function* pfunc, member** p, int* pi, int exchange, int in_func_flag) {//pi��i�ĵ�ַ,ΪӦ�Դ˽ṹ����������������
	have_space_judge();							//exchange��ʾ�˴α�����ͨ���л�һ���ṹ�壨0�������л���һ���ڲ�����������1��
	variable* pnow = NULL;
	if (in_func_flag)//�������ڵ���
		pnow = pvar_in;
	else//�ⲿ����
		pnow = pvar;
	if (Kw_begin == pcur->KwCode) {			//'{'��
		++stack_Kw_begin;
		if (stack_Kw_begin > 3)
			longjmp(jmpbuf, expression_error);
		next_node();
		more_struct_mem_init_one(pvar, pvar_in, pfunc, p, pi, exchange, in_func_flag);
	}
	else if (Is_this(Kw_cchar) || Is_this(Kw_cint) || Is_this(Kw_cfloat) || Is_this(Kw_not) || Is_this(Kw_minus) || Is_this(Kw_openpa)) {
		expression(pvar, pvar_in, pfunc, in_func_flag);
		(*p)->init_flag = 1;												//��Ա����������ֵ����һ��			
		more_struct_mem_init_two(pvar, pvar_in, pfunc, p, 1, pi, 0, exchange, in_func_flag);			//����ֻ��Ϊ','��'}'		
	}
	else if (Kw_cstr == pcur->KwCode) {
		if (Is_fit_type("char") && (*p)->array_flag && (0 == (*p)->init_flag)) {//�ַ���,�ַ�����ֻ�ܳ�ʼ��һ��
			int length = strlen(pcur->spell) - 2;							//�۳�����'"'�ĳ���
			if (length > (*p)->array_count) {				//������Խ��
				longjmp(jmpbuf, array_error);
			}
			else {					//�ɹ���ʼ��
				(*p)->init_flag = 1;
				next_node();
				more_struct_mem_init_two(pvar, pvar_in, pfunc, p, (*p)->array_count, pi, 0, exchange, in_func_flag);			//����ֻ��Ϊ','��'}'�Ҵ˳�Ա�ѳ�ʼ�����
			}
		}
		else if (Is_fit_type("char") || !(*p)->array_flag) {
			longjmp(jmpbuf, type_error);
		}
		else {						//�Ѿ���ʼ������
			longjmp(jmpbuf, expression_error);
		}
	}
	else							//���Ͳ�һ�£�����
		longjmp(jmpbuf, expression_error);
}


void more_struct_mem_init_two(variable* pvar, variable* pvar_in, function* pfunc, member** p, int count, int* pi, int flag, int exchange, int in_func_flag) {//count��¼�ṹ���Ա���������ѳ�ʼ��������Ա������Խ��
	have_space_judge();	//exchange��ʾ�˴α�����ͨ���л�һ���ṹ�壨0�������л���һ���ڲ�����������1);flag��¼����three�����Ǵ�two����three
	variable* pnow = NULL;
	if (in_func_flag)//�������ڵ���
		pnow = pvar_in;
	else//�ⲿ����
		pnow = pvar;
	if (Kw_comma == pcur->KwCode) {
		if (0 == (*p)->init_flag) {					//������"{3,}"��ʹ�л�����һ��Ա
			next_node();
			more_struct_mem_init_one(pvar, pvar_in, pfunc, p, pi, exchange, in_func_flag);
		}
		else if ((*p)->array_flag && count < (*p)->array_count) {			//��Ϊ������δԽ�磬���������Ƿ���ų�ʼ�������Ա
			next_node();
			more_struct_mem_init_three(pvar, pvar_in, pfunc, p, count, pi, 0, flag, exchange, in_func_flag);
		}
		else {			//�������鵫�ѳ�ʼ���������鵫�����Ա���ѳ�ʼ�������ػ���һ����Ա����
			next_node();
			Key_Word* q = pcur;
			while (q && (Kw_tabs == q->KwCode || Kw_space == q->KwCode)) {
				q = q->next;
			}
			if (Kw_end == q->KwCode) {			//������"{3,}",�л�����һ��Ա
				Is_init_too_more(flag);
				struct_mem_array_part(*p);
				--stack_Kw_begin;
				pcur = q;
				next_node();
				(*p) = (*p)->next;
				if (*p && stack_Kw_begin)
					more_struct_mem_init_two(pvar, pvar_in, pfunc, p, 0, pi, flag, 1, in_func_flag);//�˱�������ʼ��,����һ������ֻ��Ϊ','��'}',��Ϊ',',ͨ��������һ
			}
			if ((*p)->array_flag && count == (*p)->array_count && stack_Kw_begin > 2 && Kw_identv == q->KwCode)	//��ʼֵ�趨�����
				longjmp(jmpbuf, init_value_more);
			(*p) = (*p)->next;				//�ѳ�ʼ�����ñ������л���һ��
			if (*p && stack_Kw_begin)
				more_struct_mem_init_one(pvar, pvar_in, pfunc, p, pi, 1, in_func_flag);//�˱�������ʼ��,����һ������ֻ��Ϊ','��'}',��Ϊ',',ͨ��������һ
		}
	}
	else if (Kw_end == pcur->KwCode) {
		Is_init_too_more(flag);
		struct_mem_array_part(*p);
		--stack_Kw_begin;
		if (0 == stack_Kw_begin) {			//ƥ��ɹ�
			next_node();
		}
		else if (stack_Kw_begin < 0)
			longjmp(jmpbuf, lack_begin);
		else if (1 == stack_Kw_begin && 0 == exchange) {		//���л���һ�ṹ��
			struct_rest_mem(*p);
			if ((*pi) < pnow->array_count[pnow->row] - 1) {
				(*p) = pnow->part[pnow->row]->mem[*(pi)];
				++*(pi);
			}
			next_node();
			if (*p)
				more_struct_mem_init_two(pvar, pvar_in, pfunc, p, (*p)->array_count, pi, flag, 0, in_func_flag);//����ֻ��Ϊ','��'}';��(*p)->array_count����Ϊ�˱����������ַ�������
		}													//���ǵ�����,��Ӱ�죻����δ��ʼ��������飬������'}',�������ʼ����
		else {
			next_node();
			(*p) = (*p)->next;				//�л���һ�ڲ���Ա
			if (NULL == (*p)) {
				++*(pi);
				if ((*pi) < pnow->array_count[pnow->row] - 1) {//�л���һ�ṹ��
					(*p) = pnow->part[pnow->row]->mem[*(pi)];
					exchange = 0;
				}
				else {		//�ѵ����һ���ṹ���е����һ���ڲ���Ա;���ڴ�ʱpΪNULL,�����ٽ�ȥ�ж����һ��'}'
					have_space_judge();
					if (Kw_end == pcur->KwCode) {
						--stack_Kw_begin;
						next_node();
					}
				}
			}
			if (*p)
				more_struct_mem_init_two(pvar, pvar_in, pfunc, p, (*p)->array_count, pi, flag, exchange, in_func_flag);//����ֻ��Ϊ','��'}';��(*p)->array_count����Ϊ�˱����������ַ�������
		}													//���ǵ�����,��Ӱ�죻����δ��ʼ��������飬������'}',�������ʼ����
	}
	else
		longjmp(jmpbuf, expression_error);
}


void more_struct_mem_init_three(variable* pvar, variable* pvar_in, function* pfunc, member** p, int count, int* pi, int from, int flag, int exchange, int in_func_flag) {
	have_space_judge();
	variable* pnow = NULL;
	if (in_func_flag)//�������ڵ���
		pnow = pvar_in;
	else//�ⲿ����
		pnow = pvar;
	if (Is_this(Kw_cchar) || Is_this(Kw_cint) || Is_this(Kw_cfloat) || Is_this(Kw_not) || Is_this(Kw_minus) || Is_this(Kw_openpa)) {
		expression(pvar, pvar_in, pfunc, in_func_flag);
		(*p)->init_flag = 1;														//��Ա����������ֵ����һ��
		++count;
		more_struct_mem_init_two(pvar, pvar_in, pfunc, p, count, pi, flag, exchange, in_func_flag);		//����ֻ��Ϊ','��'}'
	}
	else if (Kw_end == pcur->KwCode) {
		Is_init_too_more(flag);
		struct_mem_array_part(*p);
		--stack_Kw_begin;
		if (0 == stack_Kw_begin) {			//ƥ��ɹ�
			next_node();
		}
		else if (stack_Kw_begin < 0)
			longjmp(jmpbuf, lack_begin);
		else if (1 == stack_Kw_begin && 0 == exchange) {			//���л���һ�ṹ��
			struct_rest_mem(*p);
			if ((*pi) < pnow->array_count[pnow->row] - 1) {
				(*p) = pnow->part[pnow->row]->mem[*(pi)];
				++*(pi);
			}
			next_node();
			if (*p)
				more_struct_mem_init_two(pvar, pvar_in, pfunc, p, (*p)->array_count, pi, flag, 0, in_func_flag);//�����ʼ������
		}
		else {
			next_node();
			(*p) = (*p)->next;
			if (NULL == (*p)) {
				++*(pi);
				if ((*pi) < pnow->array_count[pnow->row] - 1) {
					(*p) = pnow->part[pnow->row]->mem[*(pi)];
					exchange = 0;
				}
				else {//�ѵ����һ���ṹ���е����һ���ڲ���Ա;���ڴ�ʱpΪNULL,�����ٽ�ȥ�ж����һ��'}'
					have_space_judge();
					if (Kw_end == pcur->KwCode) {
						--stack_Kw_begin;
						next_node();
					}
				}
			}
			if (*p)
				more_struct_mem_init_two(pvar, pvar_in, pfunc, p, (*p)->array_count, pi, flag, exchange, in_func_flag);		//����ֻ��Ϊ','��'}'
		}
	}
	else if (Kw_begin == pcur->KwCode) {
		++stack_Kw_begin;
		if (stack_Kw_begin > 3)
			longjmp(jmpbuf, expression_error);
		next_node();
		more_struct_mem_init_three(pvar, pvar_in, pfunc, p, count, pi, 1, 1, exchange, in_func_flag);
	}
	else
		longjmp(jmpbuf, expression_error);
}


void type_dispose(variable* pvar, variable* pvar_in, function* pfunc) {
	Key_Word* memo = pcur;
	if (Kw_void == pcur->KwCode) {
		next_node();
		if (!have_space_judge())			//δ���ֿո�
			longjmp(jmpbuf, lack_space);
		if (Kw_identf != pcur->KwCode)		//�����Ǻ�����
			longjmp(jmpbuf, lack_identf);
		function_handle(pvar, pvar_in, pfunc, memo, 1);
	}
	else {
		next_node();
		if (!have_space_judge())			//δ���ֿո�
			longjmp(jmpbuf, lack_space);
		if (Kw_identv == pcur->KwCode) {			//��������
			identv_statement_one(pvar, pvar_in, pfunc, memo, 0);//������������ʼ���жϺ���
			++pvar->row;
			variable_expand(pvar);
		}
		else if (Kw_identf == pcur->KwCode) {			//��������/����ʵ��
			function_handle(pvar, pvar_in, pfunc, memo, 1);
		}
		else
			longjmp(jmpbuf, expression_error);
	}

}


void function_handle(variable* pvar, variable* pvar_in, function* pfunc, Key_Word* memo, int in_func_flag) {
	have_space_judge();
	strcpy(pfunc->type[pfunc->row], memo->spell);//��������ֵ����
	strcpy(pfunc->word[pfunc->row], pcur->spell);//������
	if (!strcmp(pfunc->word[pfunc->row], "main") && strcmp(pfunc->type[pfunc->row], "int"))
		longjmp(jmpbuf, main_error);//�����ڴ������main����������ֵ����int
	main_flag = 1;
	next_node();
	have_space_judge();
	next_node();//�ߵ�'('
	parameter_handle(pvar, pfunc, NULL);	//�ܴ������˵��'('��')'һ����ƥ���
	if (Is_this(Kw_begin)) {	//����ʵ��
		if (!parameter_name_examine(pfunc, pfunc->row))//���˺����Ƿ���Ϻ���ʵ�ֵĹ���
			longjmp(jmpbuf, func_define_error);
		if (strcmp(pfunc->word[pfunc->row], "main")) {//�����������������Ҫ��ô��
			if (main_flag) {		//��main����֮��ĺ������壬Ӧ���к�������
				if (!have_func_statement(pfunc, pfunc->row))	//û�иú�������
					longjmp(jmpbuf, func_undefined);
			}
		}
		pfunc->is_define[pfunc->row] = 1;
		if (have_func_define(pfunc, pfunc->row))//�ú��������Ƿ��Ѵ���
			longjmp(jmpbuf, func_repeat_definition);
		next_node();
		++Kw_begin_grade;
		function_body(pvar, pvar_in, pfunc, in_func_flag);		//����������
		//external���ߵ�'}'
	}
	else if (Is_this(Kw_semicolon)) {	//��������(Ҫ��main����֮ǰ�����򱨴�)
		if (!strcmp(pfunc->word[pfunc->row], "main"))
			longjmp(jmpbuf, main_error);//�����ڴ������main���������Ǻ���ʵ��
		if (main_flag && !have_func_statement(pfunc, pfunc->row))//��main����֮��ĺ�������,��û��main����֮ǰ���������ҵ�һ���ĺ�������������
			longjmp(jmpbuf, statememnt_should_front);//��������Ӧ����main����֮ǰ
		next_node();
	}
	else	//��������
		longjmp(jmpbuf, expression_error);
	++pfunc->row;
	function_expand(pfunc);
}

void function_body(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {//�������ڲ�����
	have_space_judge();
	Key_Word* memo = pcur;
	while (Kw_begin_grade) {
		switch (pcur->KwCode) {
		case Kw_char:		//һ���Ĵ���ʽ
		case Kw_int:
		case Kw_float:
			next_node();
			func_type(pvar, pvar_in, pfunc, memo, in_func_flag);
			next_node();//�ߵ�';'��
			have_space_judge();
			break;


		case Kw_identv:		//�����Ǹ�ֵ���ʽ,Ҳ�����ǲ���ֵ���ʽ
			func_identv(pvar, pvar_in, pfunc, in_func_flag);
			if (!Is_this(Kw_semicolon))
				longjmp(jmpbuf, lack_semicolon);
			next_node();//�ߵ�';'��
			have_space_judge();
			break;

		case Kw_not:		//����ֵ�ı��ʽ����
		case Kw_minus:
		case Kw_openpa:
		case Kw_cchar:
		case Kw_cint:
		case Kw_cfloat:
			func_other(pvar, pvar_in, pfunc, in_func_flag);
			if (!Is_this(Kw_semicolon))
				longjmp(jmpbuf, lack_semicolon);
			next_node();//�ߵ�';'��
			have_space_judge();
			break;

		case Kw_struct: //�����ṹ�����ͻ�ṹ�����,����ھֲ���������
			struct_dispose(pvar, pvar_in, pfunc, in_func_flag);
			next_node();
			break;

		case Kw_identf://�������ô���
			func_identf(pvar, pvar_in, pfunc, in_func_flag);
			if (Is_this(Kw_comma)) {
				next_node();//�ߵ�';'����','��
				have_space_judge();
				case_comma(pvar, pvar_in, pfunc, in_func_flag);//','����ܸ��ź������ã�����ֵ���ʽ����ֵ���ʽ
			}
			else if (Is_this(Kw_semicolon)) {
				next_node();//�ߵ�';'����','��
				have_space_judge();
			}
			else
				longjmp(jmpbuf, expression_error);
			break;

		case Kw_if:
			next_node();
			func_if(pvar, pvar_in, pfunc, in_func_flag);
			next_node();//�ߵ�'}'����';'
			have_space_judge();
			break;

		case Kw_for:
			next_node();
			func_for(pvar, pvar_in, pfunc, in_func_flag);
			next_node();//�ߵ�'}'����';'
			have_space_judge();

			break;
		case Kw_while:
			next_node();
			func_while(pvar, pvar_in, pfunc, in_func_flag);
			next_node();//�ߵ�'}'����';'
			have_space_judge();
			break;

		case Kw_begin:
			++Kw_begin_grade;
			next_node();
			have_space_judge();
			break;

		case Kw_end:
			destroy_var(pvar_in, Kw_begin_grade);//���ٴ��ڵ��ڴ˲�εľֲ�����
			--Kw_begin_grade;
			break;

		case Kw_semicolon:	//��������
			next_node();
			have_space_judge();
			break;

		case Kw_return:
			next_node();
			func_return(pvar, pvar_in, pfunc, in_func_flag);
			next_node();//�ߵ�';'��
			have_space_judge();
			break;

		case Kw_notes:		//ע�ͣ���������
			next_node();
			have_space_judge();
			break;

		default:
			longjmp(jmpbuf, expression_error);
		}
	}
}

void func_type(variable* pvar, variable* pvar_in, function* pfunc, Key_Word* memo, int in_func_flag) {
	have_space_judge();			//δ���ֿո�
	if (Kw_identv != pcur->KwCode)		//��֧�ֺ��������������庯��
		longjmp(jmpbuf, expression_error);
	identv_statement_one(pvar, pvar_in, pfunc, memo, in_func_flag);//������������ʼ���жϺ���
	++pvar_in->row;
	variable_expand(pvar_in);
}


void func_other(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {//����ֵ�ı��ʽ
	expression(pvar, pvar_in, pfunc, in_func_flag);
	if (Is_this(Kw_comma)) {//���ܻ������Ʊ��ʽ
		next_node();
		have_space_judge();
		if (Is_this(Kw_identv))//���Ǳ��������ܴ��ڸ�ֵ���ʽ
			func_identv(pvar, pvar_in, pfunc, in_func_flag);
		func_other(pvar, pvar_in, pfunc, in_func_flag);
	}
}


void func_identv(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {//���ܴ��ڸ�ֵ�ı��ʽ
	have_space_judge();
	if (Is_this(Kw_identv)) {
		Key_Word* temp = pcur;//��¼��ǰpcurλ��,�����ж����Ǹ�ֵ���ʽ�Ļ�,��pcur�ص�,�ٽ��в���ֵ���ʽ�Ľ���
		int ret = 0;	//��¼�鵽�ñ����ڱ����洢����ߵ�λ��
		member* inner = NULL;//��¼�ṹ���ڲ������ĵ�ַ
		parameter* func_var = NULL;//��¼������ַ
		if (ret = top_first(pvar_in)) {//�ں������ڽ���expression()�Ҵ��ڴ˾ֲ�����
			if (pvar_in->array_flag[ret]) {	//��������
				next_node();
				have_space_judge();
				if (Kw_openbr != pcur->KwCode)
					longjmp(jmpbuf, lack_openbr);
				next_node();
				have_space_judge();
				expression(pvar, pvar_in, pfunc, in_func_flag);		//'['��']'֮��
				if (Kw_closebr != pcur->KwCode)
					longjmp(jmpbuf, lack_openbr);
			}
			if (pvar_in->mem[ret]) {				//���ǽṹ��
				next_node();
				have_space_judge();
				if (Kw_dot != pcur->KwCode)
					longjmp(jmpbuf, expression_error);
				next_node();
				have_space_judge();
				if (!(inner = struct_mem_repeat_judge(pvar_in, ret)))	//�Ƿ��и��ڲ���Ա
					longjmp(jmpbuf, expression_error);
				if (inner->array_flag) {			//���ó�Ա������
					next_node();
					have_space_judge();
					if (Kw_openbr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
					next_node();
					have_space_judge();
					expression(pvar, pvar_in, pfunc, in_func_flag);
					if (Kw_closebr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
				}
			}
			next_node();
		}
		else if (func_var = have_func_var(pfunc)) {//�ں������ڽ���expression()�Ҵ��ڴ˺�����������
			if (func_var->array_flag) {	//��������
				next_node();
				have_space_judge();
				if (Kw_openbr != pcur->KwCode)
					longjmp(jmpbuf, lack_openbr);
				next_node();
				have_space_judge();
				expression(pvar, pvar_in, pfunc, in_func_flag);		//'['��']'֮��
				if (Kw_closebr != pcur->KwCode)
					longjmp(jmpbuf, lack_openbr);
			}
			if (func_var->mem) {				//���ǽṹ��
				next_node();
				have_space_judge();
				if (Kw_dot != pcur->KwCode)
					longjmp(jmpbuf, expression_error);
				next_node();
				have_space_judge();
				if (!(inner = parameter_mem_repeat_judge(func_var)))	//�Ƿ��и��ڲ���Ա
					longjmp(jmpbuf, expression_error);
				if (inner->array_flag) {			//���ó�Ա������
					next_node();
					have_space_judge();
					if (Kw_openbr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
					next_node();
					have_space_judge();
					expression(pvar, pvar_in, pfunc, in_func_flag);
					if (Kw_closebr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
				}
			}
			next_node();
		}

		else if (ret = have_identv(pvar)) {//����ڴ�ȫ�ֱ���
			if (pvar->array_flag[ret]) {	//�������飨�ṹ�����飩
				next_node();
				have_space_judge();
				if (Kw_openbr != pcur->KwCode)
					longjmp(jmpbuf, lack_openbr);
				next_node();
				have_space_judge();
				expression(pvar, pvar_in, pfunc, in_func_flag);		//'['��']'֮��
				if (Kw_closebr != pcur->KwCode)
					longjmp(jmpbuf, lack_openbr);
			}
			if (pvar->mem[ret]) {				//���ǽṹ������
				next_node();
				have_space_judge();
				if (Kw_dot != pcur->KwCode)
					longjmp(jmpbuf, expression_error);
				next_node();
				have_space_judge();
				if (!(inner = struct_mem_repeat_judge(pvar, ret)))	//�Ƿ��и��ڲ���Ա
					longjmp(jmpbuf, expression_error);
				if (inner->array_flag) {			//���ó�Ա������
					next_node();
					have_space_judge();
					if (Kw_openbr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
					next_node();
					have_space_judge();
					expression(pvar, pvar_in, pfunc, in_func_flag);
					if (Kw_closebr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
				}
			}
			next_node();
		}
		else//�Ǳ��������Ǵ����д洢�����ĵط���û�ҵ��˱�����˵���˱��������ڣ�����ʹ��
			longjmp(jmpbuf, var_undefined);
		have_space_judge();
		if (Is_this(Kw_assign)) {//�����Ǹ�ֵ���ʽ
			next_node();
			have_space_judge();
			func_other(pvar, pvar_in, pfunc, in_func_flag);
		}
		else {//�Ǿ��ǲ���ֵ���ʽ
			pcur = temp;//�ص�
			func_other(pvar, pvar_in, pfunc, in_func_flag);
		}
	}
	else
		longjmp(jmpbuf, expression_error);
}


void func_identf(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {//�������ô���
	have_space_judge();
	int posi = 0;
	if (!(posi = exist_func(pfunc)))//�ҵ��ú��������λ��
		longjmp(jmpbuf, func_undefined);
	parameter* para = pfunc->para[posi];//��һ��������λ��
	next_node();
	have_space_judge();//�ߵ�'('
	++stack_Kw_openpa;
	next_node();
	have_space_judge();//�ߵ���һ������(Ҳ�����޲���)
	while (para) {
		if ((strcmp("char", para->type) || strcmp("int", para->type) || strcmp("float", para->type)) && (0 == para->array_flag))//��ֵ���߱���ֵ��ȥ
			expression(pvar, pvar_in, pfunc, in_func_flag);
		else if ((strcmp("char", para->type) || strcmp("int", para->type) || strcmp("float", para->type)) && para->array_flag) {
			if (!Is_this(Kw_identv))
				longjmp(jmpbuf, para_type_error);
			int ret = 0;	//��¼�鵽�ñ����ڱ����洢����ߵ�λ��
			member* inner = NULL;//��¼�ṹ���ڲ������ĵ�ַ
			parameter* func_var = NULL;//��¼������ַ
			if (ret = top_first(pvar_in)) {//�ں������ڽ���expression()�Ҵ��ڴ˾ֲ�����
				if (pvar_in->mem[ret] && pvar_in->array_flag[ret]) {//���ҵ��Ĵ˱���Ϊ�ṹ������,��ѯ�Ƿ����ӳ�Ա���ϱ�����
					next_node();
					have_space_judge();
					if (Kw_openbr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
					next_node();
					have_space_judge();
					expression(pvar, pvar_in, pfunc, in_func_flag);		//'['��']'֮��
					if (Kw_closebr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
					next_node();
					have_space_judge();
					if (Kw_dot != pcur->KwCode)
						longjmp(jmpbuf, expression_error);
					next_node();
					have_space_judge();
					if (!(inner = struct_mem_repeat_judge(pvar_in, ret)))	//�Ƿ��и��ڲ���Ա
						longjmp(jmpbuf, para_type_error);
					if (!(inner->array_flag && !strcmp(inner->type, para->type))) //�ó�Ա������������һ��
						longjmp(jmpbuf, para_type_error);
				}
				else if (pvar_in->mem[ret] && !pvar_in->array_flag[ret]) {	//���ǽṹ�������
					next_node();
					have_space_judge();
					if (Kw_dot != pcur->KwCode)
						longjmp(jmpbuf, expression_error);
					next_node();
					have_space_judge();
					if (!(inner = struct_mem_repeat_judge(pvar_in, ret)))	//�Ƿ��и��ڲ���Ա
						longjmp(jmpbuf, para_type_error);
					if (!(inner->array_flag && !strcmp(inner->type, para->type))) //�ó�Ա������������һ��
						longjmp(jmpbuf, para_type_error);
				}
				else if (pvar_in->array_flag[ret] && !strcmp(pvar_in->type[ret], para->type)) {//�ǽṹ������������һ��

				}
				else
					longjmp(jmpbuf, para_type_error);
			}
			else if (func_var = have_func_var(pfunc)) {//�ں������ڽ���expression()�Ҵ��ڴ˺�����������
				if (func_var->mem && func_var->array_flag) {//���ҵ��Ĵ˱���Ϊ�ṹ������,��ѯ�Ƿ����ӳ�Ա���ϱ�����
					next_node();
					have_space_judge();
					if (Kw_openbr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
					next_node();
					have_space_judge();
					expression(pvar, pvar_in, pfunc, in_func_flag);		//'['��']'֮��
					if (Kw_closebr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
					next_node();
					have_space_judge();
					if (Kw_dot != pcur->KwCode)
						longjmp(jmpbuf, expression_error);
					next_node();
					have_space_judge();
					if (!(inner = parameter_mem_repeat_judge(func_var)))	//�Ƿ��и��ڲ���Ա
						longjmp(jmpbuf, para_type_error);
					if (!(inner->array_flag && !strcmp(inner->type, para->type))) //�ó�Ա������������һ��
						longjmp(jmpbuf, para_type_error);
				}
				else if (func_var->mem && !func_var->array_flag) {	//���ǽṹ�������
					next_node();
					have_space_judge();
					if (Kw_dot != pcur->KwCode)
						longjmp(jmpbuf, expression_error);
					next_node();
					have_space_judge();
					if (!(inner = parameter_mem_repeat_judge(func_var)))	//�Ƿ��и��ڲ���Ա
						longjmp(jmpbuf, para_type_error);
					if (!(inner->array_flag && !strcmp(inner->type, para->type))) //�ó�Ա������������һ��
						longjmp(jmpbuf, para_type_error);
				}
				else if (func_var->array_flag && !(strcmp(func_var->type, para->type))) {//�ǽṹ������������һ��

				}
				else
					longjmp(jmpbuf, para_type_error);
			}
			else if (ret = have_identv(pvar)) {//����ڴ�ȫ�ֱ���
				if (pvar->mem[ret] && pvar->array_flag[ret]) {//���ҵ��Ĵ˱���Ϊ�ṹ������,��ѯ�Ƿ����ӳ�Ա���ϱ�����
					next_node();
					have_space_judge();
					if (Kw_openbr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
					next_node();
					have_space_judge();
					expression(pvar, pvar_in, pfunc, in_func_flag);		//'['��']'֮��
					if (Kw_closebr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
					next_node();
					have_space_judge();
					if (Kw_dot != pcur->KwCode)
						longjmp(jmpbuf, expression_error);
					next_node();
					have_space_judge();
					if (!(inner = struct_mem_repeat_judge(pvar, ret)))	//�Ƿ��и��ڲ���Ա
						longjmp(jmpbuf, para_type_error);
					if (!(inner->array_flag && !strcmp(inner->type, para->type))) //�ó�Ա������������һ��
						longjmp(jmpbuf, para_type_error);
				}
				else if (pvar->mem[ret] && !pvar->array_flag[ret]) {	//���ǽṹ�������
					next_node();
					have_space_judge();
					if (Kw_dot != pcur->KwCode)
						longjmp(jmpbuf, expression_error);
					next_node();
					have_space_judge();
					if (!(inner = struct_mem_repeat_judge(pvar, ret)))	//�Ƿ��и��ڲ���Ա
						longjmp(jmpbuf, para_type_error);
					if (!(inner->array_flag && !strcmp(inner->type, para->type))) //�ó�Ա������������һ��
						longjmp(jmpbuf, para_type_error);
				}
				else if (pvar->array_flag[ret] && !strcmp(pvar->type[ret], para->type)) {//�ǽṹ������������һ��

				}
				else
					longjmp(jmpbuf, para_type_error);
			}
			else//�Ǳ��������Ǵ����д洢�����ĵط���û�ҵ��˱�����˵���˱��������ڣ�����ʹ��
				longjmp(jmpbuf, var_undefined);
			next_node();
			have_space_judge();
		}
		else {//�����ǽṹ��
			if (!Is_this(Kw_identv))
				longjmp(jmpbuf, para_type_error);
			int ret = 0;	//��¼�鵽�ñ����ڱ����洢����ߵ�λ��
			member* inner = NULL;//��¼�ṹ���ڲ������ĵ�ַ
			parameter* func_var = NULL;//��¼������ַ
			if ((func_var = have_func_var(pfunc))) {
				if (!(!strcmp(func_var->type, para->type) && func_var->array_flag == para->array_flag))//����Ҫһ��
					longjmp(jmpbuf, para_type_error);
			}
			else if (ret = have_identv(pvar_in)) {
				if (!(!strcmp(pvar_in->type[ret], para->type) && pvar_in->array_flag[ret] == para->array_flag))//����Ҫһ��
					longjmp(jmpbuf, para_type_error);
			}
			else if (ret = have_identv(pvar)) {
				if (!(!strcmp(pvar->type[ret], para->type) && pvar->array_flag[ret] == para->array_flag))//����Ҫһ��
					longjmp(jmpbuf, para_type_error);
			}
			else//�Ǳ��������Ǵ����д洢�����ĵط���û�ҵ��˱�����˵���˱��������ڣ�����ʹ��
				longjmp(jmpbuf, var_undefined);
			next_node();
			have_space_judge();
		}
		para = para->next;//��һ������
		if (Is_this(Kw_comma)) {
			next_node();
			have_space_judge();
		}
		else if (Is_this(Kw_closepa)) {
			--stack_Kw_openpa;
			next_node();
			have_space_judge();
			break;
		}
		else
			longjmp(jmpbuf, expression_error);
	}
	if (stack_Kw_openpa)
		longjmp(jmpbuf, lack_closepa);
	if (para)
		longjmp(jmpbuf, expression_error);
}


void func_return(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {//��������Ҫ����
	have_space_judge();
	if (!strcmp(pfunc->type[pfunc->row], "void")) {//����������ֵ����Ϊvoid
		if (!Is_this(Kw_semicolon))
			longjmp(jmpbuf, expression_error);
	}
	else {//����int��char��float
		expression(pvar, pvar_in, pfunc, in_func_flag);
		if (!Is_this(Kw_semicolon))
			longjmp(jmpbuf, expression_error);
	}
}


void func_while(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {
	have_space_judge();
	if (!Is_this(Kw_openpa))
		longjmp(jmpbuf, lack_openpa);
	next_node();
	have_space_judge();
	expression(pvar, pvar_in, pfunc, in_func_flag);
	if (!Is_this(Kw_closepa))
		longjmp(jmpbuf, lack_closepa);
	next_node();
	have_space_judge();
	if (Is_this(Kw_begin)) {
		++Kw_begin_grade;
		next_node();
		have_space_judge();
		func_while_or_for_body_two(pvar, pvar_in, pfunc, in_func_flag);
	}
	else
		func_while_or_for_body_one(pvar, pvar_in, pfunc, in_func_flag);
}


void case_comma(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {
	have_space_judge();
	switch (pcur->KwCode) {
	case Kw_identv:		//�����Ǹ�ֵ���ʽ,Ҳ�����ǲ���ֵ���ʽ
		func_identv(pvar, pvar_in, pfunc, in_func_flag);
		if (!Is_this(Kw_semicolon))
			longjmp(jmpbuf, lack_semicolon);
		next_node();//�ߵ�';'��
		have_space_judge();
		break;

	case Kw_not:		//����ֵ�ı��ʽ����
	case Kw_minus:
	case Kw_openpa:
	case Kw_cchar:
	case Kw_cint:
	case Kw_cfloat:
		func_other(pvar, pvar_in, pfunc, in_func_flag);
		if (!Is_this(Kw_semicolon))
			longjmp(jmpbuf, lack_semicolon);
		next_node();//�ߵ�';'��
		have_space_judge();
		break;

	case Kw_identf://�������ô���
		func_identf(pvar, pvar_in, pfunc, in_func_flag);
		if (Is_this(Kw_comma)) {
			next_node();//�ߵ�';'����','��
			have_space_judge();
			case_comma(pvar, pvar_in, pfunc, in_func_flag);
		}
		else if (Is_this(Kw_semicolon)) {
			next_node();//�ߵ�';'����','��
			have_space_judge();
		}
		else
			longjmp(jmpbuf, expression_error);
		break;
	case Kw_notes:
		next_node();//�ߵ�';'����','��
		have_space_judge();
		case_comma(pvar, pvar_in, pfunc, in_func_flag);
		break;

	default:
		longjmp(jmpbuf, expression_error);
	}
}


void func_while_or_for_body_one(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {//��'{',����ֻ�ܽ�һ�����
	have_space_judge();
	switch (pcur->KwCode) {
	case Kw_identv:		//�����Ǹ�ֵ���ʽ,Ҳ�����ǲ���ֵ���ʽ
		func_identv(pvar, pvar_in, pfunc, in_func_flag);
		if (!Is_this(Kw_semicolon))
			longjmp(jmpbuf, lack_semicolon);
		next_node();//�ߵ�';'��
		have_space_judge();
		break;

	case Kw_not:		//����ֵ�ı��ʽ����
	case Kw_minus:
	case Kw_openpa:
	case Kw_cchar:
	case Kw_cint:
	case Kw_cfloat:
		func_other(pvar, pvar_in, pfunc, in_func_flag);
		if (!Is_this(Kw_semicolon))
			longjmp(jmpbuf, lack_semicolon);
		next_node();//�ߵ�';'��
		have_space_judge();
		break;

	case Kw_identf://�������ô���
		func_identf(pvar, pvar_in, pfunc, in_func_flag);//�ڲ��ߵ�','��';'
		if (Is_this(Kw_comma)) {
			next_node();//�ߵ�';'����','��
			have_space_judge();
			case_comma(pvar, pvar_in, pfunc, in_func_flag);
		}
		else if (Is_this(Kw_semicolon)) {
			next_node();//�ߵ�';'����','��
			have_space_judge();
		}
		else
			longjmp(jmpbuf, expression_error);
		break;

	case Kw_if:
		next_node();
		++stack_Kw_if;
		func_if(pvar, pvar_in, pfunc, in_func_flag);
		next_node();//�ߵ�'}'����';'
		have_space_judge();
		break;

	case Kw_for:
		next_node();
		func_for(pvar, pvar_in, pfunc, in_func_flag);
		next_node();//�ߵ�'}'
		have_space_judge();
		break;

	case Kw_while:
		next_node();
		func_while(pvar, pvar_in, pfunc, in_func_flag);
		next_node();//�ߵ�'}'
		have_space_judge();
		break;

	case Kw_semicolon:	//��������
		next_node();
		have_space_judge();
		break;

	case Kw_return:
		next_node();
		func_return(pvar, pvar_in, pfunc, in_func_flag);
		next_node();//�ߵ�';'��
		have_space_judge();
		break;

	case Kw_notes:		//ע�ͣ���������
		next_node();
		have_space_judge();
		func_while_or_for_body_one(pvar, pvar_in, pfunc, in_func_flag);//������һ�����
		break;

	case Kw_break://ѭ������
		next_node();
		have_space_judge();
		if (!Is_this(Kw_semicolon))
			longjmp(jmpbuf, expression_error);
		next_node();
		have_space_judge();
		break;

	case Kw_continue://ѭ������
		next_node();
		have_space_judge();
		if (!Is_this(Kw_semicolon))
			longjmp(jmpbuf, expression_error);
		next_node();
		have_space_judge();
		break;

	default:
		longjmp(jmpbuf, expression_error);
	}
}


void func_while_or_for_body_two(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {//��'{'������while�ڲ�����
	have_space_judge();
	int while_or_for_grade = Kw_begin_grade;		//�ڵڼ���while��
	Key_Word* memo = pcur;
	while (Kw_begin_grade > (while_or_for_grade - 1)) {//��������ȣ��Ƴ���whileѭ��
		switch (pcur->KwCode) {
		case Kw_char:		//һ���Ĵ���ʽ
		case Kw_int:
		case Kw_float:
			next_node();
			func_type(pvar, pvar_in, pfunc, memo, in_func_flag);
			next_node();//�ߵ�';'��
			have_space_judge();
			break;

		case Kw_identv:		//�����Ǹ�ֵ���ʽ,Ҳ�����ǲ���ֵ���ʽ
			func_identv(pvar, pvar_in, pfunc, in_func_flag);
			if (!Is_this(Kw_semicolon))
				longjmp(jmpbuf, lack_semicolon);
			next_node();//�ߵ�';'��
			have_space_judge();
			break;

		case Kw_not:		//����ֵ�ı��ʽ����
		case Kw_minus:
		case Kw_openpa:
		case Kw_cchar:
		case Kw_cint:
		case Kw_cfloat:
			func_other(pvar, pvar_in, pfunc, in_func_flag);
			if (!Is_this(Kw_semicolon))
				longjmp(jmpbuf, lack_semicolon);
			next_node();//�ߵ�';'��
			have_space_judge();
			break;

		case Kw_struct: //�����ṹ�����ͻ�ṹ�����,����ھֲ���������
			struct_dispose(pvar, pvar_in, pfunc, in_func_flag);
			next_node();
			break;

		case Kw_identf://�������ô���
			func_identf(pvar, pvar_in, pfunc, in_func_flag);
			if (Is_this(Kw_comma)) {
				next_node();//�ߵ�';'����','��
				have_space_judge();
				case_comma(pvar, pvar_in, pfunc, in_func_flag);
			}
			else if (Is_this(Kw_semicolon)) {
				next_node();//�ߵ�';'����','��
				have_space_judge();
			}
			else
				longjmp(jmpbuf, expression_error);
			break;

		case Kw_if:
			next_node();
			++stack_Kw_if;
			func_if(pvar, pvar_in, pfunc, in_func_flag);
			next_node();//�ߵ�'}'����';'
			have_space_judge();
			break;

		case Kw_for:
			next_node();
			func_for(pvar, pvar_in, pfunc, in_func_flag);
			next_node();//�ߵ�'}'
			have_space_judge();
			break;

		case Kw_while:
			next_node();
			func_while(pvar, pvar_in, pfunc, in_func_flag);
			next_node();//�ߵ�'}'
			have_space_judge();
			break;

		case Kw_begin:
			++Kw_begin_grade;
			next_node();
			have_space_judge();
			break;
		case Kw_end:
			destroy_var(pvar_in, Kw_begin_grade);//���ٴ��ڵ��ڴ˲�εľֲ�����
			--Kw_begin_grade;
			break;

		case Kw_semicolon:	//��������
			next_node();
			have_space_judge();
			break;

		case Kw_return:
			next_node();
			func_return(pvar, pvar_in, pfunc, in_func_flag);
			next_node();//�ߵ�';'��
			have_space_judge();
			break;

		case Kw_notes:		//ע�ͣ���������
			next_node();
			have_space_judge();
			break;

		case Kw_break://ѭ������
			next_node();
			have_space_judge();
			if (!Is_this(Kw_semicolon))
				longjmp(jmpbuf, expression_error);
			next_node();
			have_space_judge();
			break;

		case Kw_continue://ѭ������
			next_node();
			have_space_judge();
			if (!Is_this(Kw_semicolon))
				longjmp(jmpbuf, expression_error);
			next_node();
			have_space_judge();
			break;

		default:
			longjmp(jmpbuf, expression_error);
		}
	}
}


void func_for(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {
	have_space_judge();
	if (!Is_this(Kw_openpa))
		longjmp(jmpbuf, lack_openpa);
	next_node();
	have_space_judge();
	if (!Is_this(Kw_semicolon)) {//���б��ʽ
		if (Is_this(Kw_identv))
			func_identv(pvar, pvar_in, pfunc, in_func_flag);
		else
			expression(pvar, pvar_in, pfunc, in_func_flag);
	}
	if (!Is_this(Kw_semicolon))//������';'
		longjmp(jmpbuf, lack_semicolon);
	next_node();
	have_space_judge();
	if (!Is_this(Kw_semicolon)) {//���б��ʽ
		if (Is_this(Kw_identv))
			func_identv(pvar, pvar_in, pfunc, in_func_flag);
		else
			expression(pvar, pvar_in, pfunc, in_func_flag);
	}
	if (!Is_this(Kw_semicolon))//������';'
		longjmp(jmpbuf, lack_semicolon);
	next_node();
	have_space_judge();
	if (!Is_this(Kw_closepa)) {//���б��ʽ
		if (Is_this(Kw_identv))
			func_identv(pvar, pvar_in, pfunc, in_func_flag);
		else
			expression(pvar, pvar_in, pfunc, in_func_flag);
	}
	if (!Is_this(Kw_closepa))//������')'
		longjmp(jmpbuf, lack_closepa);
	next_node();
	have_space_judge();
	if (Is_this(Kw_begin)) {
		++Kw_begin_grade;
		next_node();
		have_space_judge();
		func_while_or_for_body_two(pvar, pvar_in, pfunc, in_func_flag);
	}
	else
		func_while_or_for_body_one(pvar, pvar_in, pfunc, in_func_flag);
}


void func_if(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {//if��䴦��
	have_space_judge();
	if (!Is_this(Kw_openpa))
		longjmp(jmpbuf, lack_openpa);
	next_node();
	have_space_judge();
	expression(pvar, pvar_in, pfunc, in_func_flag);
	if (!Is_this(Kw_closepa))
		longjmp(jmpbuf, lack_closepa);
	next_node();
	have_space_judge();
	if (Is_this(Kw_begin)) {//if�����'{',���봦��
		++Kw_begin_grade;
		next_node();
		have_space_judge();
		func_if_else_body_two(pvar, pvar_in, pfunc, in_func_flag);
	}
	else//�Ǿ�ֻ�ܽ�һ��
		func_if_else_body_one(pvar, pvar_in, pfunc, in_func_flag);
	next_node();//�ߵ�';'��'}'
	have_space_judge();
	while (Is_this(Kw_notes)) {//�ߵ�ע��
		next_node();
		have_space_judge();
	}
	if (Is_this(Kw_else)) //if��䴦��󣬺������else(Ҳ������else if)
		func_else_if(pvar, pvar_in, pfunc, in_func_flag);
}


void func_else_if(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {
	have_space_judge();
	if (Is_this(Kw_else)) {//if��䴦��󣬺������else
		next_node();
		have_space_judge();
		if (Is_this(Kw_if)) {//�ж��Ƿ�else if ���
			next_node();
			have_space_judge();
			if (!Is_this(Kw_openpa))
				longjmp(jmpbuf, lack_openpa);
			next_node();
			have_space_judge();
			expression(pvar, pvar_in, pfunc, in_func_flag);
			if (!Is_this(Kw_closepa))
				longjmp(jmpbuf, lack_closepa);
			next_node();
			have_space_judge();
			if (Is_this(Kw_begin)) {//else if�����������'{'�����봦��
				++Kw_begin_grade;
				next_node();
				have_space_judge();
				func_if_else_body_two(pvar, pvar_in, pfunc, in_func_flag);
			}
			else
				func_if_else_body_one(pvar, pvar_in, pfunc, in_func_flag);
			next_node();
			have_space_judge();
			while (Is_this(Kw_notes)) {//�ߵ�ע��
				next_node();
				have_space_judge();
			}
			if (Is_this(Kw_else)) {
				func_else_if(pvar, pvar_in, pfunc, in_func_flag);
			}

		}
		else if (Is_this(Kw_begin)) {//else ���'{',���봦��
			++Kw_begin_grade;
			next_node();
			have_space_judge();
			func_if_else_body_two(pvar, pvar_in, pfunc, in_func_flag);
		}
		else
			func_if_else_body_one(pvar, pvar_in, pfunc, in_func_flag);
	}
}



void func_if_else_body_one(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {
	have_space_judge();
	switch (pcur->KwCode) {

	case Kw_identv:		//�����Ǹ�ֵ���ʽ,Ҳ�����ǲ���ֵ���ʽ
		func_identv(pvar, pvar_in, pfunc, in_func_flag);
		if (!Is_this(Kw_semicolon))
			longjmp(jmpbuf, lack_semicolon);
		next_node();//�ߵ�';'��
		have_space_judge();
		break;

	case Kw_not:		//����ֵ�ı��ʽ����
	case Kw_minus:
	case Kw_openpa:
	case Kw_cchar:
	case Kw_cint:
	case Kw_cfloat:
		func_other(pvar, pvar_in, pfunc, in_func_flag);
		if (!Is_this(Kw_semicolon))
			longjmp(jmpbuf, lack_semicolon);
		next_node();//�ߵ�';'��
		have_space_judge();
		break;

	case Kw_identf://�������ô���
		func_identf(pvar, pvar_in, pfunc, in_func_flag);//�ڲ��ߵ�','��';'
		if (Is_this(Kw_comma)) {
			next_node();//�ߵ�';'����','��
			have_space_judge();
			case_comma(pvar, pvar_in, pfunc, in_func_flag);
		}
		else if (Is_this(Kw_semicolon)) {
			next_node();//�ߵ�';'����','��
			have_space_judge();
		}
		else
			longjmp(jmpbuf, expression_error);
		break;

	case Kw_if:
		next_node();
		++stack_Kw_if;
		func_if(pvar, pvar_in, pfunc, in_func_flag);
		next_node();//�ߵ�'}'����';'
		have_space_judge();
		break;

	case Kw_for:
		next_node();
		func_for(pvar, pvar_in, pfunc, in_func_flag);
		next_node();//�ߵ�'}'����';'
		have_space_judge();
		break;

	case Kw_while:
		next_node();
		func_while(pvar, pvar_in, pfunc, in_func_flag);
		next_node();//�ߵ�'}'����';'
		have_space_judge();
		break;

	case Kw_semicolon:	//��������
		next_node();
		have_space_judge();
		break;

	case Kw_return:
		next_node();
		func_return(pvar, pvar_in, pfunc, in_func_flag);
		next_node();//�ߵ�';'��
		have_space_judge();
		break;

	case Kw_notes:		//ע�ͣ���������
		next_node();
		have_space_judge();
		func_if_else_body_one(pvar, pvar_in, pfunc, in_func_flag);//��if�����δ����,�ٽ�ȥ
		break;

	default:
		longjmp(jmpbuf, expression_error);
	}
}


void func_if_else_body_two(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {
	have_space_judge();
	int while_if_grade = Kw_begin_grade;		//�ڵڼ���while��
	Key_Word* memo = pcur;
	while (Kw_begin_grade > (while_if_grade - 1)) {//��������ȣ��Ƴ���whileѭ��
		switch (pcur->KwCode) {

		case Kw_char:		//һ���Ĵ���ʽ
		case Kw_int:
		case Kw_float:
			next_node();
			func_type(pvar, pvar_in, pfunc, memo, in_func_flag);
			next_node();//�ߵ�';'��
			have_space_judge();
			break;


		case Kw_identv:		//�����Ǹ�ֵ���ʽ,Ҳ�����ǲ���ֵ���ʽ
			func_identv(pvar, pvar_in, pfunc, in_func_flag);
			if (!Is_this(Kw_semicolon))
				longjmp(jmpbuf, lack_semicolon);
			next_node();//�ߵ�';'��
			have_space_judge();
			break;

		case Kw_not:		//����ֵ�ı��ʽ����
		case Kw_minus:
		case Kw_openpa:
		case Kw_cchar:
		case Kw_cint:
		case Kw_cfloat:
			func_other(pvar, pvar_in, pfunc, in_func_flag);
			if (!Is_this(Kw_semicolon))
				longjmp(jmpbuf, lack_semicolon);
			next_node();//�ߵ�';'��
			have_space_judge();
			break;

		case Kw_struct: //�����ṹ�����ͻ�ṹ�����,����ھֲ���������
			struct_dispose(pvar, pvar_in, pfunc, in_func_flag);
			next_node();
			break;


		case Kw_identf://�������ô���
			func_identf(pvar, pvar_in, pfunc, in_func_flag);
			if (Is_this(Kw_comma)) {
				next_node();//�ߵ�';'����','��
				have_space_judge();
				case_comma(pvar, pvar_in, pfunc, in_func_flag);
			}
			else if (Is_this(Kw_semicolon)) {
				next_node();//�ߵ�';'����','��
				have_space_judge();
			}
			else
				longjmp(jmpbuf, expression_error);
			break;

		case Kw_if:
			next_node();
			func_if(pvar, pvar_in, pfunc, in_func_flag);
			next_node();//�ߵ�'}'����';'
			have_space_judge();
			break;

		case Kw_for:
			next_node();
			func_for(pvar, pvar_in, pfunc, in_func_flag);
			next_node();//�ߵ�'}'
			have_space_judge();
			break;

		case Kw_while:
			next_node();
			func_while(pvar, pvar_in, pfunc, in_func_flag);
			next_node();//�ߵ�'}'
			have_space_judge();
			break;

		case Kw_begin:
			++Kw_begin_grade;
			next_node();
			have_space_judge();
			break;

		case Kw_end:
			destroy_var(pvar_in, Kw_begin_grade);//���ٴ��ڵ��ڴ˲�εľֲ�����
			--Kw_begin_grade;
			break;

		case Kw_semicolon:	//��������
			next_node();
			have_space_judge();
			break;

		case Kw_return:
			next_node();
			func_return(pvar, pvar_in, pfunc, in_func_flag);
			next_node();//�ߵ�';'��
			have_space_judge();
			break;

		case Kw_notes:		//ע�ͣ���������
			next_node();
			have_space_judge();
			break;

		default:
			longjmp(jmpbuf, expression_error);
		}
	}
}


void destroy_var(variable* pvar_in, int grade) {//���ٲ�θߵľֲ�����
	int i = 1;
	for (i; i < pvar_in->row; ++i) {
		if (pvar_in->grade[i] >= grade) {
			member* temp1 = NULL, * temp2 = NULL;
			memset(pvar_in->word[i], 0, sizeof(pvar_in->word[i]));
			memset(pvar_in->type[i], 0, sizeof(pvar_in->type[i]));
			if (pvar_in->part[i]) {
				free(pvar_in->part[i]->init_flag);
				for (int j = 0; j < pvar_in->count - 1; ++j) {//���ǽṹ�����飬����
					temp1 = pvar_in->part[i]->mem[i], temp2 = NULL;
					while (temp1) {//���ǽṹ��,�������Ա
						temp2 = temp1;
						if (temp2->part_init)
							free(temp2->part_init);
						free(temp2);
						temp1 = temp1->next;
					}
				}
				pvar_in->part[i] = NULL;
			}
			pvar_in->array_flag[i] = 0;
			pvar_in->array_count[i] = 0;
			pvar_in->array_count[i] = 0;
			pvar_in->init_flag[i] = 0;
			pvar_in->grade[i] = 0;
			temp1 = pvar_in->mem[i], temp2 = NULL;
			while (temp1) {//���ǽṹ��,�������Ա
				temp2 = temp1;
				if (temp2->part_init)
					free(temp2->part_init);
				free(temp2);
				temp1 = temp1->next;
			}
			pvar_in->mem[i] = NULL;
			if (i != (pvar_in->row - 1)) {//���һ������
				strcpy(pvar_in->word[i], pvar_in->word[pvar_in->row - 1]);
				strcpy(pvar_in->type[i], pvar_in->type[pvar_in->row - 1]);
				pvar_in->array_flag[i] = pvar_in->array_flag[pvar_in->row - 1];
				pvar_in->array_count[i] = pvar_in->array_count[pvar_in->row - 1];
				pvar_in->init_flag[i] = pvar_in->init_flag[pvar_in->row - 1];
				pvar_in->grade[i] = pvar_in->grade[pvar_in->row - 1];
				pvar_in->mem[i] = pvar_in->mem[pvar_in->row - 1];
				pvar_in->part[i] = pvar_in->part[pvar_in->row - 1];//���Ͻ����һ���������Ƶ���ǰ�����ٵı���λ��

				memset(pvar_in->word[pvar_in->row - 1], 0, sizeof(pvar_in->word[pvar_in->row - 1]));
				memset(pvar_in->type[pvar_in->row - 1], 0, sizeof(pvar_in->type[pvar_in->row - 1]));
				pvar_in->array_flag[pvar_in->row - 1] = 0;
				pvar_in->array_count[pvar_in->row - 1] = 0;
				pvar_in->init_flag[pvar_in->row - 1] = 0;
				pvar_in->grade[pvar_in->row - 1] = 0;
				pvar_in->mem[pvar_in->row - 1] = NULL;
				pvar_in->part[pvar_in->row - 1] = NULL;//�����һ��������Ϊ��
				--pvar_in->row;
			}
		}
	}

}


void parameter_handle(variable* pvar, function* pfunc, parameter* temp) {
	have_space_judge();
	parameter* pnew = (parameter*)calloc(1, sizeof(parameter));
	if (Is_this(Kw_char) || Is_this(Kw_int) || Is_this(Kw_float) || Is_this(Kw_struct)) {
		if (Is_this(Kw_char) || Is_this(Kw_int) || Is_this(Kw_float)) {
			strcpy(pnew->type, pcur->spell);
			next_node();
			have_space_judge();
		}
		else {
			Key_Word* mark = pcur;		//��¼struct
			int length = strlen(mark->spell);
			next_node();
			have_space_judge();
			if (!Is_this(Kw_identv))
				longjmp(jmpbuf, unknown_struct_type);
			strcpy(pnew->type, mark->spell);
			strcpy(pnew->type + length, pcur->spell);//���¸ýṹ������
			int flag = 0, i = 1;							//�Ƿ���ڸýṹ�����͵ı�־
			for (i; i < pvar->row;) {
				int ret = strcmp(pnew->type, pvar->type[i]);
				if (0 == ret) {		//����ڸýṹ������
					flag = 1;
					break;
				}
			}
			if (!flag)		//�򲻴��ڸýṹ������
				longjmp(jmpbuf, unknown_struct_type);
			pnew->mem = (member*)calloc(1, sizeof(member));//Ϊ�ṹ���ڲ���Ա����һ���Ľṹ���ڲ���Ա�ռ�
			*(pnew->mem) = *(pvar->mem[i]);		//����ͬ��Ϊһ��������;
			member* q = pvar->mem[i]->next;		//��һ���ṹ���Ա
			member* p = pnew->mem, * pn = NULL;
			while (q) {	//ͬ��Ϊһ���Ľṹ��
				pn = (member*)calloc(1, sizeof(member));
				*(pn) = *q;				//��Աһ��						
				p->next = pn;			//�ṹ���ڲ���Աָ���¸��ṹ���ڲ���Ա
				p = p->next;
				q = q->next;
			}		//���⽫�ṹ����ڲ���Աͬ�����
			next_node();
			have_space_judge();
		}
		if (Is_this(Kw_identv)) {			//������Ǳ���������������;����Ǳ�������������������Ҳ�����Ƕ���;���ﻹ��֪��
			strcpy(pnew->word, pcur->spell);
			next_node();
			have_space_judge();
		}
		if (Is_this(Kw_openbr)) {
			next_node();
			have_space_judge();
			if (Is_this(Kw_cint)) {	//��ȷ���Ǻ������廹�Ǻ������������Դ˴���
				int length = string_value(pcur->spell);
				if (length <= 0)
					longjmp(jmpbuf, array_error);
				pnew->array_count = length;
			}
			else if (Is_this(Kw_closebr))
				pnew->array_flag = 1;
			else
				longjmp(jmpbuf, lack_closebr);
			next_node();
			have_space_judge();
		}
		if (NULL == pfunc->para[pfunc->row]) {//��������ǵ�һ����Ա
			pfunc->para[pfunc->row] = pnew;
		}
		else {	//�Ǿ���֮��ĳ�Ա
			parameter* next = pfunc->para[pfunc->row];
			while (next) {		//��tempָ�����е����һ����Ա
				temp = next;
				next = next->next;
			}
			temp->next = pnew;//����
		}
		temp = pnew;	//�������һ����Ա
		if (Is_this(Kw_comma)) {//���ܻ��в���
			next_node();
			parameter_handle(pvar, pfunc, temp);
		}
		else if (Is_this(Kw_closepa)) {//�����������
			next_node();
		}
		else
			longjmp(jmpbuf, expression_error);
	}
	else if (Is_this(Kw_closepa)) {		//�����������
		Key_Word* front = pcur->prior;
		while (Kw_space == front->KwCode || Kw_tabs == front->KwCode) {
			front = front->prior;
		}
		if (Kw_comma == front->KwCode)		//��')'ǰ��һ��','
			longjmp(jmpbuf, expression_error);
		next_node();
	}
	else
		longjmp(jmpbuf, type_error);
}


void identv_statement_one(variable* pvar, variable* pvar_in, function* pfunc, Key_Word* memo, int in_func_flag) {//������������ʼ������
	have_space_judge();
	variable* pnow = NULL;
	if (in_func_flag)//�������ڵ���
		pnow = pvar_in;
	else//�ⲿ����
		pnow = pvar;
	if (Kw_identv == pcur->KwCode) {
		pnow->grade[pnow->row] = Kw_begin_grade;
		strcpy(pnow->word[pnow->row], pcur->spell);	//���ϱ�������
		strcpy(pnow->type[pnow->row], memo->spell);	//������
		if (in_func_flag && 1 == Kw_begin_grade) {//�ԱȺ�������
			if (cmp_para(pfunc, pnow))//�����뺯�������Ƿ�������
				longjmp(jmpbuf, var_repeat_definition);
		}
		if (repeat_judge(pnow))				//������������
			longjmp(jmpbuf, var_repeat_definition);
		next_node();
		identv_statement_two(pvar, pvar_in, pfunc, 0, memo, 0, in_func_flag);				//�Ƿ��г�Ա
	}
	else if (Kw_semicolon == pcur->KwCode) {				//��ֹ�ޱ�����identv_statement_two()�������˺�������
		Key_Word* p = pcur;
		p = p->prior;
		while (Kw_space == p->KwCode || Kw_tabs == p->KwCode) {
			p = p->prior;
		}
		if (Kw_closebr == pcur->KwCode || Kw_identv == pcur->KwCode) {
			//ǰ������Ǳ���,���ñ���Ϊ����,���һ����Ϊ']'
		}
		else
			longjmp(jmpbuf, lack_identv);
	}
	else
		longjmp(jmpbuf, lack_identv);

}


void identv_statement_two(variable* pvar, variable* pvar_in, function* pfunc, int from, Key_Word* memo, int assign, int in_func_flag) {
	have_space_judge();
	variable* pnow = NULL;
	if (in_func_flag)//�������ڵ���
		pnow = pvar_in;
	else//�ⲿ����
		pnow = pvar;
	if (Kw_comma == pcur->KwCode) {					//������ܻ��б���;pnow->init_flag[pnow->row]��ʼΪ�㼴δ��ʼ��		
		next_node();
		++pnow->row;
		variable_expand(pnow);				//������Ҫ����
		identv_statement_one(pvar, pvar_in, pfunc, memo, in_func_flag);
	}
	else if (Kw_semicolon == pcur->KwCode) {		//�˱����������

	}
	else if (Kw_openbr == pcur->KwCode) {			//�����������ţ�������
		if (1 == from)							//'[]'����'[]'�����󣨲�֧�ֶ�ά���飩
			longjmp(jmpbuf, array_error);
		next_node();
		have_space_judge();
		if (Kw_cint != pcur->KwCode)		//���������Ϊ������
			longjmp(jmpbuf, array_error);
		pnow->array_flag[pnow->row] = 1;
		pnow->array_count[pnow->row] = string_value(pcur->spell);		//���ַ�ת��Ϊ����ֵ
		if (pnow->array_count[pnow->row] <= 0)			//���鳤�Ȳ���Ϊ�����
			longjmp(jmpbuf, array_error);
		next_node();
		have_space_judge();
		if (Kw_closebr != pcur->KwCode)		//��������
			longjmp(jmpbuf, lack_closebr);
		identv_array_part_storage(pnow);	//���������Ա
		next_node();
		identv_statement_two(pvar, pvar_in, pfunc, 1, memo, 0, in_func_flag);					//']'����һ���ǿ��ַ�	,ҪôΪ',',ҪôΪ';'	
	}
	else if (Kw_assign == pcur->KwCode) {			//'='��ʼ������
		if (1 == assign)
			longjmp(jmpbuf, expression_error);
		next_node();
		if (pnow->array_flag[pnow->row]) {
			more_identv_init(pvar, pvar_in, pfunc, in_func_flag);		//���������Ա����ѳ�ʼ��
			identv_array_part_init(pnow);
		}
		else {		//�����鴦��
			if (Kw_begin == pcur->KwCode) {
				next_node();
				have_space_judge();
				++stack_Kw_begin;
			}
			expression(pvar, pvar_in, pfunc, in_func_flag);				//��ʼ����һ������	
			if (stack_Kw_begin) {
				if (Kw_end != pcur->KwCode) {
					longjmp(jmpbuf, lack_end);
					--stack_Kw_begin;
					next_node();
					have_space_judge();
				}
			}
		}
		pnow->init_flag[pnow->row] = 1;
		identv_statement_two(pvar, pvar_in, pfunc, 1, memo, 1, in_func_flag);				//���ܻ��нṹ�������Ҫ����
	}
	else
		longjmp(jmpbuf, expression_error);
}


void more_identv_init(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {	//���������ʼ��
	have_space_judge();
	variable* pnow = NULL;
	if (in_func_flag)//�������ڵ���
		pnow = pvar_in;
	else//�ⲿ����
		pnow = pvar;
	if (!strcmp("char", pnow->type[pnow->row]) && Is_this(Kw_cstr)) {//��������Ϊchar�Ҵ�ʱpcurָ���ַ���
		next_node();
		have_space_judge();
	}
	else if (Is_this(Kw_begin)) {
		next_node();
		have_space_judge();
		++stack_Kw_begin;
		more_identv_init_one(pvar, pvar_in, pfunc, in_func_flag);
		if (stack_Kw_begin)
			longjmp(jmpbuf, lack_end);
	}
	else
		longjmp(jmpbuf, need_Kw_begin_Kw_end);
}


void more_identv_init_one(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {
	have_space_judge();
	variable* pnow = NULL;
	if (in_func_flag)//�������ڵ���
		pnow = pvar_in;
	else//�ⲿ����
		pnow = pvar;
	if (Is_this(Kw_begin)) {			//'{'��
		++stack_Kw_begin;
		if (stack_Kw_begin > 2)
			longjmp(jmpbuf, expression_error);
		next_node();
		more_identv_init_one(pvar, pvar_in, pfunc, in_func_flag);
	}
	else if (Is_this(Kw_cchar) || Is_this(Kw_cint) || Is_this(Kw_cfloat) || Is_this(Kw_not) || Is_this(Kw_minus) || Is_this(Kw_openpa)) {
		expression(pvar, pvar_in, pfunc, in_func_flag);
		more_identv_init_two(pvar, pvar_in, pfunc, 1, 0, in_func_flag);			//����ֻ��Ϊ','��'}'		
	}
	else if (Kw_cstr == pcur->KwCode) {
		if (!strcmp(pnow->type[pnow->row], "char")) {//�ַ���,�ַ�����ֻ�ܳ�ʼ��һ��
			if (stack_Kw_begin > 1)
				longjmp(jmpbuf, lack_value);
			next_node();
			int length = strlen(pcur->spell) - 2;							//�۳�����'"'�ĳ���
			if (length > pnow->array_count[pnow->row])				//������Խ��
				longjmp(jmpbuf, array_error);
			more_identv_init_two(pvar, pvar_in, pfunc, pnow->array_count[pnow->row], 0, in_func_flag);			//����ֻ��Ϊ','��'}'�Ҵ˳�Ա�ѳ�ʼ�����			
		}
		else
			longjmp(jmpbuf, type_error);
	}
	else							//���Ͳ�һ�£�����
		longjmp(jmpbuf, expression_error);
}


void more_identv_init_two(variable* pvar, variable* pvar_in, function* pfunc, int count, int flag, int in_func_flag) {
	have_space_judge();									//	flag����ڽ����ڲ���Ա��������ʱ�Ƿ���ֹ�'{'
	variable* pnow = NULL;
	if (in_func_flag)//�������ڵ���
		pnow = pvar_in;
	else//�ⲿ����
		pnow = pvar;
	if (Kw_comma == pcur->KwCode) {
		if (count < pnow->array_count[pnow->row]) {			//��Ϊ������δԽ�磬���������Ƿ���ų�ʼ�������Ա
			next_node();
			more_identv_init_three(pvar, pvar_in, pfunc, count, 0, flag, in_func_flag);
		}
		else {			//�����Ա���ѳ�ʼ��������
			next_node();
			Key_Word* q = pcur;
			while (q && (Kw_tabs == q->KwCode || Kw_space == q->KwCode)) {
				q = q->next;
			}
			if (Kw_end == q->KwCode) {			//������"{3,}"
				--stack_Kw_begin;
				pcur = q;
				Is_init_more(flag);
				next_node();
				if (stack_Kw_begin)		//����С����
					more_identv_init_two(pvar, pvar_in, pfunc, count, 0, in_func_flag);//����ֻ��Ϊ','��'}'
			}
		}
	}
	else if (Kw_end == pcur->KwCode) {
		--stack_Kw_begin;
		Is_init_more(flag);
		if (0 == stack_Kw_begin) {			//ƥ��ɹ������������ʼ�����
			next_node();
		}
		else if (stack_Kw_begin < 0)
			longjmp(jmpbuf, lack_begin);
		else {
			next_node();
			more_identv_init_two(pvar, pvar_in, pfunc, count, flag, in_func_flag);//����ֻ��Ϊ','��'}'
		}
	}
	else
		longjmp(jmpbuf, expression_error);
}


void more_identv_init_three(variable* pvar, variable* pvar_in, function* pfunc, int count, int from, int flag, int in_func_flag) {//�������Ա����	  //from�����Ǵ��Ľ���˺�����
	have_space_judge();
	if (Is_this(Kw_cchar) || Is_this(Kw_cint) || Is_this(Kw_cfloat) || Is_this(Kw_not) || Is_this(Kw_minus) || Is_this(Kw_openpa)) {
		expression(pvar, pvar_in, pfunc, in_func_flag);
		++count;
		more_identv_init_two(pvar, pvar_in, pfunc, count, 0, in_func_flag);			//����ֻ��Ϊ','��'}'		
	}
	else if (Kw_end == pcur->KwCode) {
		if (1 == from)						//����more_identv_init_three()�����ģ���������ƥ���ڲ�Ϊ��
			longjmp(jmpbuf, expression_error);
		Is_init_more(flag);
		--stack_Kw_begin;
		if (0 == stack_Kw_begin) {
			next_node();
		}
		else if (stack_Kw_begin < 0)
			longjmp(jmpbuf, lack_begin);
		else {
			next_node();
			more_identv_init_two(pvar, pvar_in, pfunc, count, flag, in_func_flag);		//����ֻ��Ϊ','��'}'
		}
	}
	else if (Kw_begin == pcur->KwCode) {
		++stack_Kw_begin;
		if (stack_Kw_begin > 2)
			longjmp(jmpbuf, expression_error);
		next_node();
		more_identv_init_three(pvar, pvar_in, pfunc, count, 1, 1, in_func_flag);
	}
	else
		longjmp(jmpbuf, expression_error);
}


void expression(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {//������ں������ڳ�ʼ�������ñ���,������������ó���
	have_space_judge();
	seventh(pvar, pvar_in, pfunc, in_func_flag);
}


void seventh(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {			//����'||'
	sixth(pvar, pvar_in, pfunc, in_func_flag);
	while (Kw_or == pcur->KwCode) {
		next_node();
		have_space_judge();
		sixth(pvar, pvar_in, pfunc, in_func_flag);
	}
}


void sixth(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {		//����'&&'
	fifth(pvar, pvar_in, pfunc, in_func_flag);
	while (Kw_and == pcur->KwCode) {
		next_node();
		have_space_judge();
		fifth(pvar, pvar_in, pfunc, in_func_flag);
	}
}


void fifth(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {		//����'=='��'!='
	fourth(pvar, pvar_in, pfunc, in_func_flag);
	while (Kw_eq == pcur->KwCode || Kw_neq == pcur->KwCode) {
		next_node();
		have_space_judge();
		fourth(pvar, pvar_in, pfunc, in_func_flag);
	}
}


void fourth(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {		//����'<'��'<='��'>'��'>='
	third(pvar, pvar_in, pfunc, in_func_flag);
	while (Kw_lt <= pcur->KwCode && Kw_geq >= pcur->KwCode) {
		next_node();
		have_space_judge();
		third(pvar, pvar_in, pfunc, in_func_flag);
	}
}


void third(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {				//����'+'��'-'
	second(pvar, pvar_in, pfunc, in_func_flag, 0);
	while (Kw_plus == pcur->KwCode || Kw_minus == pcur->KwCode) {
		next_node();
		have_space_judge();
		second(pvar, pvar_in, pfunc, in_func_flag, 0);
	}
}


void second(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag, int from) {		//����'*'��'/'��'%'
	if (in_func_flag) {
		in_func_first(pvar, pvar_in, pfunc, in_func_flag, 0);
		while (Kw_star == pcur->KwCode || Kw_divide == pcur->KwCode || Kw_mod == pcur->KwCode) {
			next_node();
			have_space_judge();
			in_func_first(pvar, pvar_in, pfunc, in_func_flag, 0);
		}
	}
	else {
		out_func_first(pvar, pvar_in, pfunc, in_func_flag, 0);
		while (Kw_star == pcur->KwCode || Kw_divide == pcur->KwCode || Kw_mod == pcur->KwCode) {
			next_node();
			have_space_judge();
			out_func_first(pvar, pvar_in, pfunc, in_func_flag, 0);
		}
	}
}


void in_func_first(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag, int from) {			//����'('��')'
	if (Kw_identv == pcur->KwCode || (Kw_cchar <= pcur->KwCode && Kw_cfloat >= pcur->KwCode)) {
		if (Kw_identv == pcur->KwCode) {
			int ret = 0;	//��¼�鵽�ñ����ڱ����洢����ߵ�λ��
			member* inner = NULL;//��¼�ṹ���ڲ������ĵ�ַ
			parameter* func_var = NULL;//��¼������ַ
			if (ret = top_first(pvar_in)) {//�ں������ڽ���expression()�Ҵ��ڴ˾ֲ�����
				if (pvar_in->array_flag[ret]) {	//��������
					next_node();
					have_space_judge();
					if (Kw_openbr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
					next_node();
					have_space_judge();
					expression(pvar, pvar_in, pfunc, in_func_flag);		//'['��']'֮��
					if (Kw_closebr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
				}
				if (pvar_in->mem[ret]) {				//���ǽṹ��
					next_node();
					have_space_judge();
					if (Kw_dot != pcur->KwCode)
						longjmp(jmpbuf, expression_error);
					next_node();
					have_space_judge();
					if (!(inner = struct_mem_repeat_judge(pvar_in, ret)))	//�Ƿ��и��ڲ���Ա
						longjmp(jmpbuf, expression_error);
					if (inner->array_flag) {			//���ó�Ա������
						next_node();
						have_space_judge();
						if (Kw_openbr != pcur->KwCode)
							longjmp(jmpbuf, lack_openbr);
						next_node();
						have_space_judge();
						expression(pvar, pvar_in, pfunc, in_func_flag);
						if (Kw_closebr != pcur->KwCode)
							longjmp(jmpbuf, lack_openbr);
					}
				}
				next_node();
			}
			else if (func_var = have_func_var(pfunc)) {//�ں������ڽ���expression()�Ҵ��ڴ˺�����������
				if (func_var->array_flag) {	//��������
					next_node();
					have_space_judge();
					if (Kw_openbr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
					next_node();
					have_space_judge();
					expression(pvar, pvar_in, pfunc, in_func_flag);		//'['��']'֮��
					if (Kw_closebr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
				}
				if (func_var->mem) {				//���ǽṹ��
					next_node();
					have_space_judge();
					if (Kw_dot != pcur->KwCode)
						longjmp(jmpbuf, expression_error);
					next_node();
					have_space_judge();
					if (!(inner = parameter_mem_repeat_judge(func_var)))	//�Ƿ��и��ڲ���Ա
						longjmp(jmpbuf, expression_error);
					if (inner->array_flag) {			//���ó�Ա������
						next_node();
						have_space_judge();
						if (Kw_openbr != pcur->KwCode)
							longjmp(jmpbuf, lack_openbr);
						next_node();
						have_space_judge();
						expression(pvar, pvar_in, pfunc, in_func_flag);
						if (Kw_closebr != pcur->KwCode)
							longjmp(jmpbuf, lack_openbr);
					}
				}
				next_node();
			}
			else if (ret = have_identv(pvar)) {//����ڴ�ȫ�ֱ���
				if (pvar->array_flag[ret]) {	//�������飨�ṹ�����飩
					next_node();
					have_space_judge();
					if (Kw_openbr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
					next_node();
					have_space_judge();
					expression(pvar, pvar_in, pfunc, in_func_flag);		//'['��']'֮��
					if (Kw_closebr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
				}
				if (pvar->mem[ret]) {				//���ǽṹ������
					next_node();
					have_space_judge();
					if (Kw_dot != pcur->KwCode)
						longjmp(jmpbuf, expression_error);
					next_node();
					have_space_judge();
					if (!(inner = struct_mem_repeat_judge(pvar, ret)))	//�Ƿ��и��ڲ���Ա
						longjmp(jmpbuf, expression_error);
					if (inner->array_flag) {			//���ó�Ա������
						next_node();
						have_space_judge();
						if (Kw_openbr != pcur->KwCode)
							longjmp(jmpbuf, lack_openbr);
						next_node();
						have_space_judge();
						expression(pvar, pvar_in, pfunc, in_func_flag);
						if (Kw_closebr != pcur->KwCode)
							longjmp(jmpbuf, lack_openbr);
					}
				}
				next_node();
			}
			else//�Ǳ��������Ǵ����д洢�����ĵط���û�ҵ��˱�����˵���˱��������ڣ�����ʹ��
				longjmp(jmpbuf, var_undefined);
		}
		else {	//��ô����Kw_cchar��Kw_cint�� Kw_cfloat 
			next_node();
			have_space_judge();
		}
	}
	else if (Kw_openpa == pcur->KwCode) {		//�����'('
		next_node();
		have_space_judge();
		seventh(pvar, pvar_in, pfunc, in_func_flag);
		next_node();
		have_space_judge();
		if (Kw_closepa != pcur->KwCode)
			longjmp(jmpbuf, lack_closepa);
		next_node();
		have_space_judge();
	}
	else if (Kw_minus == pcur->KwCode || Kw_not == pcur->KwCode) {	//����'-'��ȡ������'!'	//from�����Ǵ�������
		if (1 == from)
			longjmp(jmpbuf, expression_error);
		from = 1;
		next_node();
		have_space_judge();
		in_func_first(pvar, pvar_in, pfunc, in_func_flag, from);
	}
	else //��Ӧ���ֵ������ַ�
		longjmp(jmpbuf, expression_error);
}


void  out_func_first(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag, int from) {
	if (Kw_cchar <= pcur->KwCode && Kw_cfloat >= pcur->KwCode) {
		next_node();
		have_space_judge();
	}
	else if (Kw_openpa == pcur->KwCode) {		//�����'('
		next_node();
		have_space_judge();
		seventh(pvar, pvar_in, pfunc, in_func_flag);
		next_node();
		have_space_judge();
		if (Kw_closepa != pcur->KwCode)
			longjmp(jmpbuf, lack_closepa);
		next_node();
		have_space_judge();
	}
	else if (Kw_minus == pcur->KwCode || Kw_not == pcur->KwCode) {	//����'-'��ȡ������'!'	//from�����Ǵ�������
		if (1 == from)
			longjmp(jmpbuf, expression_error);
		from = 1;
		next_node();
		have_space_judge();
		out_func_first(pvar, pvar_in, pfunc, in_func_flag, from);
	}
	else //��Ӧ���ֵ������ַ�
		longjmp(jmpbuf, expression_error);
}


void identv_dispose(variable* pvar) {//�ⲿ��������
	have_space_judge();
	if (Is_this(Kw_identv)) {
		//��ѯ�Ƿ��иñ���
		if (!have_identv(pvar))
			longjmp(jmpbuf, var_undefined);
		next_node();
		identv_one(pvar);
	}
	else
		longjmp(jmpbuf, expression_error);
}


void identv_one(variable* pvar) {//�ⲿ������ֻ��Ϊ','��';'
	have_space_judge();
	if (Is_this(Kw_comma)) {
		next_node();
		identv_dispose(pvar);
	}
	else if (Is_this(Kw_semicolon))
		;
	else
		longjmp(jmpbuf, expression_error);
}