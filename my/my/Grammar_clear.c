#include "head.h"




//----------------------这几个在函数里面做就行了;
int stack_Kw_begin = 0;		//存储{
int stack_Kw_openpa = 0;	//存储(
int stack_Kw_if = 0;		//存储 if 用于配对else和else if
int Kw_begin_grade = 0;		//在第几层{}中


Key_Word* pcur = NULL;//指向始终要解析的词

////外部声明
void External_dec(variable* pvar, variable* pvar_in, function* pfunc) {   //退出外部声明时 pcur为当前声明的:或函数的} 
	have_space_judge();
	if (NULL == pcur) {//走到最后就结束了
		return;
	}
	else if (Kw_notes == pcur->KwCode) {//是否是注释
	}
	else if (Kw_semicolon == pcur->KwCode) {//是否是分号
	}
	else if (Kw_hash == pcur->KwCode) {//是否是#号
		quote_dispose();
	}
	else if (Kw_struct == pcur->KwCode) {//是否是struct号
		struct_dispose(pvar, pvar_in, pfunc, 0);
	}
	else if (Is_type() || Kw_void == pcur->KwCode) {//是否是类型
		type_dispose(pvar, pvar_in, pfunc);
	}
	else if (Kw_identv == pcur->KwCode) {			//是否是变量名
		identv_dispose(pvar);
	}
	else {

	}
	next_node();
	External_dec(pvar, pvar_in, pfunc);
}


void quote_dispose()							//引用头文件处理
{
	if (main_flag)								//若main函数已经出现之后还有include语句，错误
		longjmp(jmpbuf, headfile_error);
	next_node();
	have_space_judge();
	if (Kw_include != pcur->KwCode)
		longjmp(jmpbuf, headfile_error);
	next_node();
	have_space_judge();
	if (Kw_lt == pcur->KwCode || Kw_cstr == pcur->KwCode) {	//要么以<开头，要么是"(经分词处理后为字符串类型)
		if (Kw_lt == pcur->KwCode) {
			next_node();
			//	此行缺一个判定是否是标准头文件的函数,故用以下暂代替
			if (Kw_identv != pcur->KwCode)		//处理时转成了变量类型
				longjmp(jmpbuf, headfile_error);
			next_node();
			if (Kw_dot != pcur->KwCode)			// .符号
				longjmp(jmpbuf, headfile_error);
			next_node();
			if (0 != strcmp("h", pcur->spell))				// h符
				longjmp(jmpbuf, headfile_error);
			next_node();
			have_space_judge();					//可以有空格
			if (Kw_gt != pcur->KwCode)			// >符
				longjmp(jmpbuf, headfile_error);
		}
		Key_Word* temp = pcur;
		while (1 != pcur->row_tail_flag) {			//如果不是行尾，走到行尾
			if (Kw_tabs == pcur->KwCode || Kw_space == pcur->KwCode)
				;
			else
				longjmp(jmpbuf, headfile_error);
			next_node();
		}
		if (temp == pcur)		//本身即行尾
			;
		else if (Kw_tabs == pcur->KwCode || Kw_space == pcur->KwCode)	//行尾
			;
		else															//不能有别的东西
			longjmp(jmpbuf, headfile_error);
	}
	else {								//引用错误
		longjmp(jmpbuf, headfile_error);
	}
}


void struct_dispose(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {
	variable* pnow = NULL;
	if (in_func_flag)//函数体内调用
		pnow = pvar_in;
	else//外部调用
		pnow = pvar;
	Key_Word* pa = pcur;				//记录当前struct;
	next_node();
	if (!have_space_judge())				//未出现空格
		longjmp(jmpbuf, lack_space);
	if (Kw_identv != pcur->KwCode)
		longjmp(jmpbuf, lack_identv);
	int length = strlen(pa->spell);
	strcpy(pnow->type[pnow->row], pa->spell);
	strcpy(pnow->type[pnow->row] + length, pcur->spell);		//让struct与变量名连接起来构成新的变量类型
	int mark = pnow->row;			//防止声明中使pnow->row增加丢失记忆
	next_node();
	int have = have_space_judge();				//是否有空格，在可能的结构体类型和结构体变量间
	if (Kw_begin == pcur->KwCode) {				//结构体声明处理
		next_node();
		struct_statement(pvar, pvar_in, pfunc, (member*)NULL, in_func_flag);			//	处理好此结构体声明
		if (statement_valid_ok_judge(pnow))//该声明是否之前已经存在了
			longjmp(jmpbuf, repeat_struct_statement);
		pnow->grade[pnow->row] = Kw_begin_grade;
		pnow->row++;
		variable_expand(pnow);				//可能需要扩容
		next_node();
		have_space_judge();
		if (Kw_identv == pcur->KwCode) {
			goto keep;						//其后还可能会有结构体变量定义
		}
		else if (Kw_semicolon == pcur->KwCode) {	//该结构体处理完毕

		}
		else
			longjmp(jmpbuf, struct_error);
	}
	else if (Kw_identv == pcur->KwCode) {		//结构体变量声明			
		if (!have)								//未出现空格
			longjmp(jmpbuf, lack_space);
	keep: {
		strcpy(pnow->type[pnow->row], pnow->type[mark]);			//防止经过声明pnow->row有变化
		strcpy(pnow->word[pnow->row], pcur->spell);					//存入变量名
		pnow->grade[pnow->row] = Kw_begin_grade;
		int posi = 0;													//记录找到同一类型的位置编号
		if (!((in_func_flag && (posi = identv_valid_ok_judge(pvar_in))) || (posi = identv_valid_ok_judge(pvar))))/*若在函数中则先在局
																		部变量存储体中寻找是否有该结构体类型声明，找不到再到全局中去找*/
			longjmp(jmpbuf, unknown_struct_type);//若不存在该结构体类型
		if (repeat_judge(pnow))	//是否重命名了
			longjmp(jmpbuf, var_repeat_definition);
		if (in_func_flag && 1 == Kw_begin_grade) {//对比函数参数
			if (cmp_para(pfunc, pnow))//看看与函数参数是否有重名
				longjmp(jmpbuf, var_repeat_definition);
		}
		same_struct_mem_copy(pnow, posi);								//同步为一个类型
		next_node();
		struct_init(pvar, pvar_in, pfunc, 0, 0, in_func_flag);					//初始化完一/多个结构体变量（数组）
		}
	}
	else {										//否则错误
		longjmp(jmpbuf, struct_error);
	}

}


void struct_statement(variable* pvar, variable* pvar_in, function* pfunc, member* temp, int in_func_flag) {		//处理结构体内部成员
	have_space_judge();
	variable* pnow = NULL;
	if (in_func_flag)//函数体内调用
		pnow = pvar_in;
	else//外部调用
		pnow = pvar;
	if (Is_type()) {								//(char、int、float)
		Key_Word* memo = pcur;
		next_node();
		if (!have_space_judge())			//未出现空格
			longjmp(jmpbuf, lack_space);
		struct_statement_one(pvar, pvar_in, pfunc, temp, memo, in_func_flag);
		next_node();
		struct_statement(pvar, pvar_in, pfunc, temp, in_func_flag);	//看看是否还有其余的结构体内部成员
	}
	else if (Kw_semicolon == pcur->KwCode) {			//若是分号可能还有成员
		next_node();
		struct_statement(pvar, pvar_in, pfunc, temp, in_func_flag);				//递归进行
	}
	else if (Kw_end == pcur->KwCode) {					//函数递归结束
		if (!pnow->mem[pnow->row])					//结构体内部无成员
			longjmp(jmpbuf, struct_lack_mem);
	}
	else		//非类型非分号非右大括号，错误
		longjmp(jmpbuf, lack_end);
}


void struct_statement_one(variable* pvar, variable* pvar_in, function* pfunc, member* temp, Key_Word* memo, int in_func_flag) {			//变量、';' 或者错误
	have_space_judge();
	variable* pnow = NULL;
	if (in_func_flag)//函数体内调用
		pnow = pvar_in;
	else//外部调用
		pnow = pvar;
	if (Kw_identv == pcur->KwCode) {
		member* pnew = (member*)calloc(1, sizeof(member));
		strcpy(pnew->type, memo->spell);//存上类型
		if (struct_mem_repeat_judge(pnow, pnow->row))				//结构体内部成员不能重名
			longjmp(jmpbuf, var_repeat_definition);
		strcpy(pnew->word, pcur->spell);	//存上成员变量名称		
		if (NULL == pnow->mem[pnow->row]) {			//若处理的是第一个成员
			pnow->mem[pnow->row] = pnew;
		}
		else {									//那就是之后的成员
			member* next = pnow->mem[pnow->row];
			while (next) {					//让temp指向已有的最后一个成员
				temp = next;
				next = next->next;
			}
			temp->next = pnew;			//连上
		}
		next_node();
		temp = pnew;					//最新最后一个成员
		struct_statement_two(pvar, pvar_in, pfunc, 0, temp, memo, in_func_flag);				//是否还有成员
	}
	else if (Kw_semicolon == pcur->KwCode) {				//防止无变量与struct_statement_two()函数到此函数出错
		Key_Word* p = pcur;
		p = p->prior;
		while (Kw_space == p->KwCode || Kw_tabs == p->KwCode) {
			p = p->prior;
		}
		if (Kw_closebr == pcur->KwCode || Kw_identv == pcur->KwCode) {
			//前面必须是变量,若该变量为数组,最后一个符为']'
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
	if (in_func_flag)//函数体内调用
		pnow = pvar_in;
	else//外部调用
		pnow = pvar;
	if (Kw_comma == pcur->KwCode) {					//后面可能还有变量;pnow->init_flag[pnow->row]初始为零即未初始化		
		next_node();
		struct_statement_one(pvar, pvar_in, pfunc, temp, memo, in_func_flag);
	}
	else if (Kw_semicolon == pcur->KwCode) {		//此结构体变量处理完毕

	}
	else if (Kw_openbr == pcur->KwCode) {			//若是左中括号，即数组
		if (1 == from)							//'[]'后还是'[]'，错误（不支持二维数组）
			longjmp(jmpbuf, array_error);
		next_node();
		have_space_judge();
		if (Kw_cint != pcur->KwCode)		//数组个数须为正整数
			longjmp(jmpbuf, array_error);
		temp->array_flag = 1;
		temp->array_count = string_value(pcur->spell);		//将字符转换为整数值
		if (temp->array_count <= 0)			//数组长度不能为零或负数
			longjmp(jmpbuf, array_error);
		next_node();
		have_space_judge();
		if (Kw_closebr != pcur->KwCode)		//右中括号
			longjmp(jmpbuf, lack_closebr);
		struct_mem_array_part_storage(temp);	//其余数组成员
		next_node();
		struct_statement_two(pvar, pvar_in, pfunc, 1, temp, memo, in_func_flag);					//']'后下一个非空字符	,要么为',',要么为';'	
	}
	else if (Kw_semicolon == pcur->KwCode) {			//变量后接此，可结束

	}
	else
		longjmp(jmpbuf, expression_error);
}


void struct_init(variable* pvar, variable* pvar_in, function* pfunc, int from, int assign, int in_func_flag) {//处理结构体内部成员初始化，from是标记此函数从那进来的
	have_space_judge();
	variable* pnow = NULL;
	if (in_func_flag)//函数体内调用
		pnow = pvar_in;
	else//外部调用
		pnow = pvar;
	if (Kw_comma == pcur->KwCode) {					//后面可能还有变量;pnow->init_flag[pnow->row]初始为零即未初始化		
		pnow->row++;
		variable_expand(pnow);				//可能需要扩容
		next_node();
		have_space_judge();
		if (Kw_identv == pcur->KwCode) {
			strcpy(pnow->word[pnow->row], pcur->spell);				//存入变量名
			strcpy(pnow->type[pnow->row], pnow->type[pnow->row - 1]);		//前后两变量类型一致
			same_struct_mem_copy(pnow, pnow->row - 1);			//成员是一致的
			pnow->grade[pnow->row] = Kw_begin_grade;
			if (repeat_judge(pnow))						//是否为重定义变量
				longjmp(jmpbuf, var_repeat_definition);
			next_node();
			struct_init(pvar, pvar_in, pfunc, 0, 0, in_func_flag);
		}
		else											//','后不跟变量名，错误
			longjmp(jmpbuf, lack_semicolon);
	}
	else if (Kw_semicolon == pcur->KwCode) {		//此结构体变量处理完毕
		pnow->row++;
		variable_expand(pnow);
	}
	else if (Kw_openbr == pcur->KwCode) {			//若是左中括号，即数组
		if (1 == from)							//'[]'后还是'[]'，错误（不支持二维数组）
			longjmp(jmpbuf, array_error);
		next_node();
		have_space_judge();
		if (Kw_cint != pcur->KwCode)		//数组个数须为正整数
			longjmp(jmpbuf, array_error);
		pnow->array_flag[pnow->row] = 1;
		pnow->array_count[pnow->row] = string_value(pcur->spell);		//将字符转换为整数值
		next_node();
		have_space_judge();
		if (Kw_closebr != pcur->KwCode)		//右中括号
			longjmp(jmpbuf, lack_closebr);
		struct_array_part_storage(pnow);			//其余数组成员
		next_node();
		struct_init(pvar, pvar_in, pfunc, 1, 0, in_func_flag);					//']'后下一个非空字符		
	}
	else if (Kw_assign == pcur->KwCode) {			//'='初始化处理
		if (1 == assign)
			longjmp(jmpbuf, expression_error);
		next_node();
		have_space_judge();
		if (pnow->array_flag[pnow->row]) {			//结构体数组
			more_struct_mem_init(pvar, pvar_in, pfunc, in_func_flag);
			have_space_judge();
			struct_init(pvar, pvar_in, pfunc, 1, 1, in_func_flag);				//可能还有结构体变量需要处理
		}
		else {										//单个结构体变量
			struct_mem_init(pvar, pvar_in, pfunc, in_func_flag);				//初始化完一个结构体变量	
			have_space_judge();
			struct_init(pvar, pvar_in, pfunc, 1, 1, in_func_flag);				//可能还有结构体变量需要处理
		}
	}
	else
		longjmp(jmpbuf, expression_error);
}


void struct_mem_init(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {		//进入此函数时pcur指向'='后的一个非空字符
	have_space_judge();
	variable* pnow = NULL;
	if (in_func_flag)//函数体内调用
		pnow = pvar_in;
	else//外部调用
		pnow = pvar;
	if (Kw_begin == pcur->KwCode) {
		++stack_Kw_begin;						//加入一个{
		member* p = pnow->mem[pnow->row];
		next_node();
		while (0 < stack_Kw_begin) {
			struct_mem_init_one(pvar, pvar_in, pfunc, &p, in_func_flag);
			pnow->init_flag[pnow->row] = 1;		//此结构体变量已初始化
			if (p)
				p = p->next;
			if (NULL == p)
				break;
		}
		if (stack_Kw_begin)						//若不为零，说明少了'}'(已有函数判断其若小于零，会报错)
			longjmp(jmpbuf, lack_end);
		if (p) {								//若后面的结构体成员未赋值，设置其为已初始化
			p = p->next;
			while (p) {
				p->init_flag = 1;
				if (p->array_flag) {			//对成员中的数组成员处理为已初始化
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
	if (in_func_flag)//函数体内调用
		pnow = pvar_in;
	else//外部调用
		pnow = pvar;
	if (Kw_begin == pcur->KwCode) {			//'{'符
		++stack_Kw_begin;
		if (stack_Kw_begin > 2)
			longjmp(jmpbuf, expression_error);
		next_node();
		struct_mem_init_one(pvar, pvar_in, pfunc, p, in_func_flag);
	}
	else if (Is_this(Kw_cchar) || Is_this(Kw_cint) || Is_this(Kw_cfloat) || Is_this(Kw_not) || Is_this(Kw_minus) || Is_this(Kw_openpa)) {
		(*p)->init_flag = 1;												//成员变量类型与值类型一致
		expression(pvar, pvar_in, pfunc, in_func_flag);
		struct_mem_init_two(pvar, pvar_in, pfunc, p, 1, 0, in_func_flag);			//后面只能为','、'}'		
	}
	else if (Kw_cstr == pcur->KwCode) {
		if (Is_fit_type("char") && (*p)->array_flag && (0 == (*p)->init_flag)) {//字符串,字符数组只能初始化一次
			int length = strlen(pcur->spell) - 2;							//扣除两个'"'的长度
			if (length > (*p)->array_count) {				//大于则越界
				longjmp(jmpbuf, array_error);
			}
			else {					//成功初始化
				(*p)->init_flag = 1;
				next_node();
				struct_mem_init_two(pvar, pvar_in, pfunc, p, (*p)->array_count, 0, in_func_flag);			//后面只能为','、'}'且此成员已初始化完毕
			}
		}
		else if (Is_fit_type("char") || !(*p)->array_flag) {
			longjmp(jmpbuf, type_error);
		}
		else {						//已经初始化过了
			longjmp(jmpbuf, expression_error);
		}

	}
	else							//类型不一致，错误
		longjmp(jmpbuf, expression_error);
}


void struct_mem_init_two(variable* pvar, variable* pvar_in, function* pfunc, member** p, int count, int flag, int in_func_flag) {//count记录结构体成员变量数组已初始化几个成员，避免越界
	have_space_judge();									//	flag标记在进入内部成员变量数组时是否出现过'{'
	variable* pnow = NULL;
	if (in_func_flag)//函数体内调用
		pnow = pvar_in;
	else//外部调用
		pnow = pvar;
	if (Kw_comma == pcur->KwCode) {
		if (0 == (*p)->init_flag) {					//存在如"{3,}"致使切换到下一成员
			next_node();
			struct_mem_init_one(pvar, pvar_in, pfunc, p, in_func_flag);
		}
		else if ((*p)->array_flag && count < (*p)->array_count) {			//若为数组且未越界，继续看看是否接着初始化数组成员
			next_node();
			struct_mem_init_three(pvar, pvar_in, pfunc, p, count, 0, flag, in_func_flag);
		}
		else {			//不是数组但已初始化或是数组但数组成员皆已初始化，返回换下一个成员变量
			next_node();
			Key_Word* q = pcur;
			while (q && (Kw_tabs == q->KwCode || Kw_space == q->KwCode)) {
				q = q->next;
			}
			if (Kw_end == q->KwCode) {			//存在如"{3,}",切换到下一成员
				Is_init_too_more(flag);
				struct_mem_array_part(*p);
				--stack_Kw_begin;
				pcur = q;
				next_node();
				(*p) = (*p)->next;
				if (*p && stack_Kw_begin)
					struct_mem_init_two(pvar, pvar_in, pfunc, p, 0, flag, in_func_flag);//此变量待初始化,但下一个符号只能为','或'}',若为',',通过二进入一
			}
			if ((*p)->array_flag && count == (*p)->array_count && stack_Kw_begin > 1 && Kw_identv == q->KwCode)	//初始值设定项过多
				longjmp(jmpbuf, init_value_more);
		}
	}
	else if (Kw_end == pcur->KwCode) {
		Is_init_too_more(flag);
		struct_mem_array_part(*p);
		--stack_Kw_begin;
		if (0 == stack_Kw_begin) {			//匹配成功，整个结构体初始化完毕
			next_node();
		}
		else if (stack_Kw_begin < 0)
			longjmp(jmpbuf, lack_begin);
		else {
			next_node();
			struct_mem_init_two(pvar, pvar_in, pfunc, p, (*p)->array_count, flag, in_func_flag);//后面只能为','、'}';用(*p)->array_count是因为此变量可能是字符串数组
		}												//若是单变量,无影响；若是未初始化完的数组，但遇见'}',此数组初始化完
	}
	else
		longjmp(jmpbuf, expression_error);
}


void struct_mem_init_three(variable* pvar, variable* pvar_in, function* pfunc, member** p, int count, int from, int flag, int in_func_flag) {//对数组成员处理	  //from代表是从哪进入此函数的
	have_space_judge();
	variable* pnow = NULL;
	if (in_func_flag)//函数体内调用
		pnow = pvar_in;
	else//外部调用
		pnow = pvar;
	if (Is_this(Kw_cchar) || Is_this(Kw_cint) || Is_this(Kw_cfloat) || Is_this(Kw_not) || Is_this(Kw_minus) || Is_this(Kw_openpa)) {
		expression(pvar, pvar_in, pfunc, in_func_flag);
		(*p)->init_flag = 1;														//成员变量类型与值类型一致
		++count;
		struct_mem_init_two(pvar, pvar_in, pfunc, p, count, flag, in_func_flag);		//后面只能为','、'}'
	}
	else if (Kw_end == pcur->KwCode) {
		if (1 == from)						//若是struct_mem_init_three()进来的，即此括号匹配内部为空
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
			struct_mem_init_two(pvar, pvar_in, pfunc, p, count, flag, in_func_flag);		//后面只能为','、'}'
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


void more_struct_mem_init(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {	//结构体数组处理	//进入此函数时pcur指向'='后的一个非空字符
	have_space_judge();
	variable* pnow = NULL;
	if (in_func_flag)//函数体内调用
		pnow = pvar_in;
	else//外部调用
		pnow = pvar;
	if (Kw_begin == pcur->KwCode) {
		++stack_Kw_begin;						//加入一个{
		member* p = pnow->mem[pnow->row];
		int i = 0;
		next_node();
		while (0 < stack_Kw_begin) {
			more_struct_mem_init_one(pvar, pvar_in, pfunc, &p, &i, 0, in_func_flag);
			pnow->init_flag[pnow->row] = 1;		//此结构体变量已初始化
			if (i < pnow->array_count[pnow->row] - 1) {		//回来切换下一个结构体
				p = pnow->part[pnow->row]->mem[i];
				pnow->part[pnow->row]->init_flag[i] = 1;
				++i;
			}
			else
				break;
		}
		if (stack_Kw_begin)						//若不为零，说明少了'}'(已有函数判断其若小于零，会报错)
			longjmp(jmpbuf, lack_end);
		if (p) {								//若p不存在且以上无报错,说明全部结构体数组成员中的内部成员皆已标记初始化
			for (i; i < pnow->array_count[pnow->row] - 1; ++i) {
				pnow->part[pnow->row]->init_flag[i] = 1;			//标记结构体初始化
				p = pnow->part[pnow->row]->mem[i];		//首个内部成员
				struct_rest_mem(p);
			}
		}
	}
	else
		longjmp(jmpbuf, expression_error);
}


void more_struct_mem_init_one(variable* pvar, variable* pvar_in, function* pfunc, member** p, int* pi, int exchange, int in_func_flag) {//pi即i的地址,为应对此结构体可能是数组的问题
	have_space_judge();							//exchange表示此次变量是通过切换一个结构体（0）还是切换下一个内部变量而来（1）
	variable* pnow = NULL;
	if (in_func_flag)//函数体内调用
		pnow = pvar_in;
	else//外部调用
		pnow = pvar;
	if (Kw_begin == pcur->KwCode) {			//'{'符
		++stack_Kw_begin;
		if (stack_Kw_begin > 3)
			longjmp(jmpbuf, expression_error);
		next_node();
		more_struct_mem_init_one(pvar, pvar_in, pfunc, p, pi, exchange, in_func_flag);
	}
	else if (Is_this(Kw_cchar) || Is_this(Kw_cint) || Is_this(Kw_cfloat) || Is_this(Kw_not) || Is_this(Kw_minus) || Is_this(Kw_openpa)) {
		expression(pvar, pvar_in, pfunc, in_func_flag);
		(*p)->init_flag = 1;												//成员变量类型与值类型一致			
		more_struct_mem_init_two(pvar, pvar_in, pfunc, p, 1, pi, 0, exchange, in_func_flag);			//后面只能为','、'}'		
	}
	else if (Kw_cstr == pcur->KwCode) {
		if (Is_fit_type("char") && (*p)->array_flag && (0 == (*p)->init_flag)) {//字符串,字符数组只能初始化一次
			int length = strlen(pcur->spell) - 2;							//扣除两个'"'的长度
			if (length > (*p)->array_count) {				//大于则越界
				longjmp(jmpbuf, array_error);
			}
			else {					//成功初始化
				(*p)->init_flag = 1;
				next_node();
				more_struct_mem_init_two(pvar, pvar_in, pfunc, p, (*p)->array_count, pi, 0, exchange, in_func_flag);			//后面只能为','、'}'且此成员已初始化完毕
			}
		}
		else if (Is_fit_type("char") || !(*p)->array_flag) {
			longjmp(jmpbuf, type_error);
		}
		else {						//已经初始化过了
			longjmp(jmpbuf, expression_error);
		}
	}
	else							//类型不一致，错误
		longjmp(jmpbuf, expression_error);
}


void more_struct_mem_init_two(variable* pvar, variable* pvar_in, function* pfunc, member** p, int count, int* pi, int flag, int exchange, int in_func_flag) {//count记录结构体成员变量数组已初始化几个成员，避免越界
	have_space_judge();	//exchange表示此次变量是通过切换一个结构体（0）还是切换下一个内部变量而来（1);flag记录进入three函数是从two还是three
	variable* pnow = NULL;
	if (in_func_flag)//函数体内调用
		pnow = pvar_in;
	else//外部调用
		pnow = pvar;
	if (Kw_comma == pcur->KwCode) {
		if (0 == (*p)->init_flag) {					//存在如"{3,}"致使切换到下一成员
			next_node();
			more_struct_mem_init_one(pvar, pvar_in, pfunc, p, pi, exchange, in_func_flag);
		}
		else if ((*p)->array_flag && count < (*p)->array_count) {			//若为数组且未越界，继续看看是否接着初始化数组成员
			next_node();
			more_struct_mem_init_three(pvar, pvar_in, pfunc, p, count, pi, 0, flag, exchange, in_func_flag);
		}
		else {			//不是数组但已初始化或是数组但数组成员皆已初始化，返回换下一个成员变量
			next_node();
			Key_Word* q = pcur;
			while (q && (Kw_tabs == q->KwCode || Kw_space == q->KwCode)) {
				q = q->next;
			}
			if (Kw_end == q->KwCode) {			//存在如"{3,}",切换到下一成员
				Is_init_too_more(flag);
				struct_mem_array_part(*p);
				--stack_Kw_begin;
				pcur = q;
				next_node();
				(*p) = (*p)->next;
				if (*p && stack_Kw_begin)
					more_struct_mem_init_two(pvar, pvar_in, pfunc, p, 0, pi, flag, 1, in_func_flag);//此变量待初始化,但下一个符号只能为','或'}',若为',',通过二进入一
			}
			if ((*p)->array_flag && count == (*p)->array_count && stack_Kw_begin > 2 && Kw_identv == q->KwCode)	//初始值设定项过多
				longjmp(jmpbuf, init_value_more);
			(*p) = (*p)->next;				//已初始化满该变量，切换下一个
			if (*p && stack_Kw_begin)
				more_struct_mem_init_one(pvar, pvar_in, pfunc, p, pi, 1, in_func_flag);//此变量待初始化,但下一个符号只能为','或'}',若为',',通过二进入一
		}
	}
	else if (Kw_end == pcur->KwCode) {
		Is_init_too_more(flag);
		struct_mem_array_part(*p);
		--stack_Kw_begin;
		if (0 == stack_Kw_begin) {			//匹配成功
			next_node();
		}
		else if (stack_Kw_begin < 0)
			longjmp(jmpbuf, lack_begin);
		else if (1 == stack_Kw_begin && 0 == exchange) {		//则切换下一结构体
			struct_rest_mem(*p);
			if ((*pi) < pnow->array_count[pnow->row] - 1) {
				(*p) = pnow->part[pnow->row]->mem[*(pi)];
				++*(pi);
			}
			next_node();
			if (*p)
				more_struct_mem_init_two(pvar, pvar_in, pfunc, p, (*p)->array_count, pi, flag, 0, in_func_flag);//后面只能为','、'}';用(*p)->array_count是因为此变量可能是字符串数组
		}													//若是单变量,无影响；若是未初始化完的数组，但遇见'}',此数组初始化完
		else {
			next_node();
			(*p) = (*p)->next;				//切换下一内部成员
			if (NULL == (*p)) {
				++*(pi);
				if ((*pi) < pnow->array_count[pnow->row] - 1) {//切换下一结构体
					(*p) = pnow->part[pnow->row]->mem[*(pi)];
					exchange = 0;
				}
				else {		//已到最后一个结构体中的最后一个内部成员;由于此时p为NULL,不能再进去判断最后一个'}'
					have_space_judge();
					if (Kw_end == pcur->KwCode) {
						--stack_Kw_begin;
						next_node();
					}
				}
			}
			if (*p)
				more_struct_mem_init_two(pvar, pvar_in, pfunc, p, (*p)->array_count, pi, flag, exchange, in_func_flag);//后面只能为','、'}';用(*p)->array_count是因为此变量可能是字符串数组
		}													//若是单变量,无影响；若是未初始化完的数组，但遇见'}',此数组初始化完
	}
	else
		longjmp(jmpbuf, expression_error);
}


void more_struct_mem_init_three(variable* pvar, variable* pvar_in, function* pfunc, member** p, int count, int* pi, int from, int flag, int exchange, int in_func_flag) {
	have_space_judge();
	variable* pnow = NULL;
	if (in_func_flag)//函数体内调用
		pnow = pvar_in;
	else//外部调用
		pnow = pvar;
	if (Is_this(Kw_cchar) || Is_this(Kw_cint) || Is_this(Kw_cfloat) || Is_this(Kw_not) || Is_this(Kw_minus) || Is_this(Kw_openpa)) {
		expression(pvar, pvar_in, pfunc, in_func_flag);
		(*p)->init_flag = 1;														//成员变量类型与值类型一致
		++count;
		more_struct_mem_init_two(pvar, pvar_in, pfunc, p, count, pi, flag, exchange, in_func_flag);		//后面只能为','、'}'
	}
	else if (Kw_end == pcur->KwCode) {
		Is_init_too_more(flag);
		struct_mem_array_part(*p);
		--stack_Kw_begin;
		if (0 == stack_Kw_begin) {			//匹配成功
			next_node();
		}
		else if (stack_Kw_begin < 0)
			longjmp(jmpbuf, lack_begin);
		else if (1 == stack_Kw_begin && 0 == exchange) {			//则切换下一结构体
			struct_rest_mem(*p);
			if ((*pi) < pnow->array_count[pnow->row] - 1) {
				(*p) = pnow->part[pnow->row]->mem[*(pi)];
				++*(pi);
			}
			next_node();
			if (*p)
				more_struct_mem_init_two(pvar, pvar_in, pfunc, p, (*p)->array_count, pi, flag, 0, in_func_flag);//数组初始化结束
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
				else {//已到最后一个结构体中的最后一个内部成员;由于此时p为NULL,不能再进去判断最后一个'}'
					have_space_judge();
					if (Kw_end == pcur->KwCode) {
						--stack_Kw_begin;
						next_node();
					}
				}
			}
			if (*p)
				more_struct_mem_init_two(pvar, pvar_in, pfunc, p, (*p)->array_count, pi, flag, exchange, in_func_flag);		//后面只能为','、'}'
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
		if (!have_space_judge())			//未出现空格
			longjmp(jmpbuf, lack_space);
		if (Kw_identf != pcur->KwCode)		//若不是函数名
			longjmp(jmpbuf, lack_identf);
		function_handle(pvar, pvar_in, pfunc, memo, 1);
	}
	else {
		next_node();
		if (!have_space_judge())			//未出现空格
			longjmp(jmpbuf, lack_space);
		if (Kw_identv == pcur->KwCode) {			//声明变量
			identv_statement_one(pvar, pvar_in, pfunc, memo, 0);//变量声明及初始化判断函数
			++pvar->row;
			variable_expand(pvar);
		}
		else if (Kw_identf == pcur->KwCode) {			//声明函数/函数实现
			function_handle(pvar, pvar_in, pfunc, memo, 1);
		}
		else
			longjmp(jmpbuf, expression_error);
	}

}


void function_handle(variable* pvar, variable* pvar_in, function* pfunc, Key_Word* memo, int in_func_flag) {
	have_space_judge();
	strcpy(pfunc->type[pfunc->row], memo->spell);//函数返回值类型
	strcpy(pfunc->word[pfunc->row], pcur->spell);//函数名
	if (!strcmp(pfunc->word[pfunc->row], "main") && strcmp(pfunc->type[pfunc->row], "int"))
		longjmp(jmpbuf, main_error);//若现在处理的是main函数但返回值不是int
	main_flag = 1;
	next_node();
	have_space_judge();
	next_node();//走掉'('
	parameter_handle(pvar, pfunc, NULL);	//能从这出来说明'('与')'一定是匹配的
	if (Is_this(Kw_begin)) {	//函数实现
		if (!parameter_name_examine(pfunc, pfunc->row))//检查此函数是否符合函数实现的规则
			longjmp(jmpbuf, func_define_error);
		if (strcmp(pfunc->word[pfunc->row], "main")) {//如果不是主函数才需要这么做
			if (main_flag) {		//在main函数之后的函数定义，应当有函数声明
				if (!have_func_statement(pfunc, pfunc->row))	//没有该函数声明
					longjmp(jmpbuf, func_undefined);
			}
		}
		pfunc->is_define[pfunc->row] = 1;
		if (have_func_define(pfunc, pfunc->row))//该函数定义是否已存在
			longjmp(jmpbuf, func_repeat_definition);
		next_node();
		++Kw_begin_grade;
		function_body(pvar, pvar_in, pfunc, in_func_flag);		//操作函数体
		//external会走掉'}'
	}
	else if (Is_this(Kw_semicolon)) {	//函数声明(要在main函数之前，否则报错)
		if (!strcmp(pfunc->word[pfunc->row], "main"))
			longjmp(jmpbuf, main_error);//若现在处理的是main函数但不是函数实现
		if (main_flag && !have_func_statement(pfunc, pfunc->row))//在main函数之后的函数声明,又没在main函数之前的声明中找到一样的函数声明，报错
			longjmp(jmpbuf, statememnt_should_front);//函数声明应放在main函数之前
		next_node();
	}
	else	//其他符号
		longjmp(jmpbuf, expression_error);
	++pfunc->row;
	function_expand(pfunc);
}

void function_body(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {//函数体内部处理
	have_space_judge();
	Key_Word* memo = pcur;
	while (Kw_begin_grade) {
		switch (pcur->KwCode) {
		case Kw_char:		//一样的处理方式
		case Kw_int:
		case Kw_float:
			next_node();
			func_type(pvar, pvar_in, pfunc, memo, in_func_flag);
			next_node();//走掉';'号
			have_space_judge();
			break;


		case Kw_identv:		//可能是赋值表达式,也可能是不赋值表达式
			func_identv(pvar, pvar_in, pfunc, in_func_flag);
			if (!Is_this(Kw_semicolon))
				longjmp(jmpbuf, lack_semicolon);
			next_node();//走掉';'号
			have_space_judge();
			break;

		case Kw_not:		//不赋值的表达式处理
		case Kw_minus:
		case Kw_openpa:
		case Kw_cchar:
		case Kw_cint:
		case Kw_cfloat:
			func_other(pvar, pvar_in, pfunc, in_func_flag);
			if (!Is_this(Kw_semicolon))
				longjmp(jmpbuf, lack_semicolon);
			next_node();//走掉';'号
			have_space_judge();
			break;

		case Kw_struct: //声明结构体类型或结构体变量,存放在局部变量体中
			struct_dispose(pvar, pvar_in, pfunc, in_func_flag);
			next_node();
			break;

		case Kw_identf://函数调用处理
			func_identf(pvar, pvar_in, pfunc, in_func_flag);
			if (Is_this(Kw_comma)) {
				next_node();//走掉';'或者','号
				have_space_judge();
				case_comma(pvar, pvar_in, pfunc, in_func_flag);//','后可能跟着函数调用，不赋值表达式，赋值表达式
			}
			else if (Is_this(Kw_semicolon)) {
				next_node();//走掉';'或者','号
				have_space_judge();
			}
			else
				longjmp(jmpbuf, expression_error);
			break;

		case Kw_if:
			next_node();
			func_if(pvar, pvar_in, pfunc, in_func_flag);
			next_node();//走掉'}'或者';'
			have_space_judge();
			break;

		case Kw_for:
			next_node();
			func_for(pvar, pvar_in, pfunc, in_func_flag);
			next_node();//走掉'}'或者';'
			have_space_judge();

			break;
		case Kw_while:
			next_node();
			func_while(pvar, pvar_in, pfunc, in_func_flag);
			next_node();//走掉'}'或者';'
			have_space_judge();
			break;

		case Kw_begin:
			++Kw_begin_grade;
			next_node();
			have_space_judge();
			break;

		case Kw_end:
			destroy_var(pvar_in, Kw_begin_grade);//销毁大于等于此层次的局部变量
			--Kw_begin_grade;
			break;

		case Kw_semicolon:	//跳过就行
			next_node();
			have_space_judge();
			break;

		case Kw_return:
			next_node();
			func_return(pvar, pvar_in, pfunc, in_func_flag);
			next_node();//走掉';'号
			have_space_judge();
			break;

		case Kw_notes:		//注释，跳过就行
			next_node();
			have_space_judge();
			break;

		default:
			longjmp(jmpbuf, expression_error);
		}
	}
}

void func_type(variable* pvar, variable* pvar_in, function* pfunc, Key_Word* memo, int in_func_flag) {
	have_space_judge();			//未出现空格
	if (Kw_identv != pcur->KwCode)		//不支持函数体内声明或定义函数
		longjmp(jmpbuf, expression_error);
	identv_statement_one(pvar, pvar_in, pfunc, memo, in_func_flag);//变量声明及初始化判断函数
	++pvar_in->row;
	variable_expand(pvar_in);
}


void func_other(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {//不赋值的表达式
	expression(pvar, pvar_in, pfunc, in_func_flag);
	if (Is_this(Kw_comma)) {//可能还有相似表达式
		next_node();
		have_space_judge();
		if (Is_this(Kw_identv))//若是变量，可能存在赋值表达式
			func_identv(pvar, pvar_in, pfunc, in_func_flag);
		func_other(pvar, pvar_in, pfunc, in_func_flag);
	}
}


void func_identv(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {//可能存在赋值的表达式
	have_space_judge();
	if (Is_this(Kw_identv)) {
		Key_Word* temp = pcur;//记录当前pcur位置,后面判定不是赋值表达式的话,将pcur回档,再进行不赋值表达式的进行
		int ret = 0;	//记录查到该变量在变量存储体里边的位置
		member* inner = NULL;//记录结构体内部变量的地址
		parameter* func_var = NULL;//记录参数地址
		if (ret = top_first(pvar_in)) {//在函数体内进行expression()且存在此局部变量
			if (pvar_in->array_flag[ret]) {	//若是数组
				next_node();
				have_space_judge();
				if (Kw_openbr != pcur->KwCode)
					longjmp(jmpbuf, lack_openbr);
				next_node();
				have_space_judge();
				expression(pvar, pvar_in, pfunc, in_func_flag);		//'['与']'之间
				if (Kw_closebr != pcur->KwCode)
					longjmp(jmpbuf, lack_openbr);
			}
			if (pvar_in->mem[ret]) {				//若是结构体
				next_node();
				have_space_judge();
				if (Kw_dot != pcur->KwCode)
					longjmp(jmpbuf, expression_error);
				next_node();
				have_space_judge();
				if (!(inner = struct_mem_repeat_judge(pvar_in, ret)))	//是否有该内部成员
					longjmp(jmpbuf, expression_error);
				if (inner->array_flag) {			//若该成员是数组
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
		else if (func_var = have_func_var(pfunc)) {//在函数体内进行expression()且存在此函数参数变量
			if (func_var->array_flag) {	//若是数组
				next_node();
				have_space_judge();
				if (Kw_openbr != pcur->KwCode)
					longjmp(jmpbuf, lack_openbr);
				next_node();
				have_space_judge();
				expression(pvar, pvar_in, pfunc, in_func_flag);		//'['与']'之间
				if (Kw_closebr != pcur->KwCode)
					longjmp(jmpbuf, lack_openbr);
			}
			if (func_var->mem) {				//则是结构体
				next_node();
				have_space_judge();
				if (Kw_dot != pcur->KwCode)
					longjmp(jmpbuf, expression_error);
				next_node();
				have_space_judge();
				if (!(inner = parameter_mem_repeat_judge(func_var)))	//是否有该内部成员
					longjmp(jmpbuf, expression_error);
				if (inner->array_flag) {			//若该成员是数组
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

		else if (ret = have_identv(pvar)) {//则存在此全局变量
			if (pvar->array_flag[ret]) {	//若是数组（结构体数组）
				next_node();
				have_space_judge();
				if (Kw_openbr != pcur->KwCode)
					longjmp(jmpbuf, lack_openbr);
				next_node();
				have_space_judge();
				expression(pvar, pvar_in, pfunc, in_func_flag);		//'['与']'之间
				if (Kw_closebr != pcur->KwCode)
					longjmp(jmpbuf, lack_openbr);
			}
			if (pvar->mem[ret]) {				//则是结构体数组
				next_node();
				have_space_judge();
				if (Kw_dot != pcur->KwCode)
					longjmp(jmpbuf, expression_error);
				next_node();
				have_space_judge();
				if (!(inner = struct_mem_repeat_judge(pvar, ret)))	//是否有该内部成员
					longjmp(jmpbuf, expression_error);
				if (inner->array_flag) {			//若该成员是数组
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
		else//是变量，但是从所有存储变量的地方都没找到此变量，说明此变量不存在，不可使用
			longjmp(jmpbuf, var_undefined);
		have_space_judge();
		if (Is_this(Kw_assign)) {//可能是赋值表达式
			next_node();
			have_space_judge();
			func_other(pvar, pvar_in, pfunc, in_func_flag);
		}
		else {//那就是不赋值表达式
			pcur = temp;//回档
			func_other(pvar, pvar_in, pfunc, in_func_flag);
		}
	}
	else
		longjmp(jmpbuf, expression_error);
}


void func_identf(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {//函数调用处理
	have_space_judge();
	int posi = 0;
	if (!(posi = exist_func(pfunc)))//找到该函数定义的位置
		longjmp(jmpbuf, func_undefined);
	parameter* para = pfunc->para[posi];//第一个参数的位置
	next_node();
	have_space_judge();//走到'('
	++stack_Kw_openpa;
	next_node();
	have_space_judge();//走到第一个参数(也可能无参数)
	while (para) {
		if ((strcmp("char", para->type) || strcmp("int", para->type) || strcmp("float", para->type)) && (0 == para->array_flag))//传值或者变量值过去
			expression(pvar, pvar_in, pfunc, in_func_flag);
		else if ((strcmp("char", para->type) || strcmp("int", para->type) || strcmp("float", para->type)) && para->array_flag) {
			if (!Is_this(Kw_identv))
				longjmp(jmpbuf, para_type_error);
			int ret = 0;	//记录查到该变量在变量存储体里边的位置
			member* inner = NULL;//记录结构体内部变量的地址
			parameter* func_var = NULL;//记录参数地址
			if (ret = top_first(pvar_in)) {//在函数体内进行expression()且存在此局部变量
				if (pvar_in->mem[ret] && pvar_in->array_flag[ret]) {//若找到的此变量为结构体数组,查询是否其子成员符合本条件
					next_node();
					have_space_judge();
					if (Kw_openbr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
					next_node();
					have_space_judge();
					expression(pvar, pvar_in, pfunc, in_func_flag);		//'['与']'之间
					if (Kw_closebr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
					next_node();
					have_space_judge();
					if (Kw_dot != pcur->KwCode)
						longjmp(jmpbuf, expression_error);
					next_node();
					have_space_judge();
					if (!(inner = struct_mem_repeat_judge(pvar_in, ret)))	//是否有该内部成员
						longjmp(jmpbuf, para_type_error);
					if (!(inner->array_flag && !strcmp(inner->type, para->type))) //该成员是数组且类型一致
						longjmp(jmpbuf, para_type_error);
				}
				else if (pvar_in->mem[ret] && !pvar_in->array_flag[ret]) {	//若是结构体非数组
					next_node();
					have_space_judge();
					if (Kw_dot != pcur->KwCode)
						longjmp(jmpbuf, expression_error);
					next_node();
					have_space_judge();
					if (!(inner = struct_mem_repeat_judge(pvar_in, ret)))	//是否有该内部成员
						longjmp(jmpbuf, para_type_error);
					if (!(inner->array_flag && !strcmp(inner->type, para->type))) //该成员是数组且类型一致
						longjmp(jmpbuf, para_type_error);
				}
				else if (pvar_in->array_flag[ret] && !strcmp(pvar_in->type[ret], para->type)) {//非结构体数组且类型一致

				}
				else
					longjmp(jmpbuf, para_type_error);
			}
			else if (func_var = have_func_var(pfunc)) {//在函数体内进行expression()且存在此函数参数变量
				if (func_var->mem && func_var->array_flag) {//若找到的此变量为结构体数组,查询是否其子成员符合本条件
					next_node();
					have_space_judge();
					if (Kw_openbr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
					next_node();
					have_space_judge();
					expression(pvar, pvar_in, pfunc, in_func_flag);		//'['与']'之间
					if (Kw_closebr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
					next_node();
					have_space_judge();
					if (Kw_dot != pcur->KwCode)
						longjmp(jmpbuf, expression_error);
					next_node();
					have_space_judge();
					if (!(inner = parameter_mem_repeat_judge(func_var)))	//是否有该内部成员
						longjmp(jmpbuf, para_type_error);
					if (!(inner->array_flag && !strcmp(inner->type, para->type))) //该成员是数组且类型一致
						longjmp(jmpbuf, para_type_error);
				}
				else if (func_var->mem && !func_var->array_flag) {	//若是结构体非数组
					next_node();
					have_space_judge();
					if (Kw_dot != pcur->KwCode)
						longjmp(jmpbuf, expression_error);
					next_node();
					have_space_judge();
					if (!(inner = parameter_mem_repeat_judge(func_var)))	//是否有该内部成员
						longjmp(jmpbuf, para_type_error);
					if (!(inner->array_flag && !strcmp(inner->type, para->type))) //该成员是数组且类型一致
						longjmp(jmpbuf, para_type_error);
				}
				else if (func_var->array_flag && !(strcmp(func_var->type, para->type))) {//非结构体数组且类型一致

				}
				else
					longjmp(jmpbuf, para_type_error);
			}
			else if (ret = have_identv(pvar)) {//则存在此全局变量
				if (pvar->mem[ret] && pvar->array_flag[ret]) {//若找到的此变量为结构体数组,查询是否其子成员符合本条件
					next_node();
					have_space_judge();
					if (Kw_openbr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
					next_node();
					have_space_judge();
					expression(pvar, pvar_in, pfunc, in_func_flag);		//'['与']'之间
					if (Kw_closebr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
					next_node();
					have_space_judge();
					if (Kw_dot != pcur->KwCode)
						longjmp(jmpbuf, expression_error);
					next_node();
					have_space_judge();
					if (!(inner = struct_mem_repeat_judge(pvar, ret)))	//是否有该内部成员
						longjmp(jmpbuf, para_type_error);
					if (!(inner->array_flag && !strcmp(inner->type, para->type))) //该成员是数组且类型一致
						longjmp(jmpbuf, para_type_error);
				}
				else if (pvar->mem[ret] && !pvar->array_flag[ret]) {	//若是结构体非数组
					next_node();
					have_space_judge();
					if (Kw_dot != pcur->KwCode)
						longjmp(jmpbuf, expression_error);
					next_node();
					have_space_judge();
					if (!(inner = struct_mem_repeat_judge(pvar, ret)))	//是否有该内部成员
						longjmp(jmpbuf, para_type_error);
					if (!(inner->array_flag && !strcmp(inner->type, para->type))) //该成员是数组且类型一致
						longjmp(jmpbuf, para_type_error);
				}
				else if (pvar->array_flag[ret] && !strcmp(pvar->type[ret], para->type)) {//非结构体数组且类型一致

				}
				else
					longjmp(jmpbuf, para_type_error);
			}
			else//是变量，但是从所有存储变量的地方都没找到此变量，说明此变量不存在，不可使用
				longjmp(jmpbuf, var_undefined);
			next_node();
			have_space_judge();
		}
		else {//参数是结构体
			if (!Is_this(Kw_identv))
				longjmp(jmpbuf, para_type_error);
			int ret = 0;	//记录查到该变量在变量存储体里边的位置
			member* inner = NULL;//记录结构体内部变量的地址
			parameter* func_var = NULL;//记录参数地址
			if ((func_var = have_func_var(pfunc))) {
				if (!(!strcmp(func_var->type, para->type) && func_var->array_flag == para->array_flag))//类型要一致
					longjmp(jmpbuf, para_type_error);
			}
			else if (ret = have_identv(pvar_in)) {
				if (!(!strcmp(pvar_in->type[ret], para->type) && pvar_in->array_flag[ret] == para->array_flag))//类型要一致
					longjmp(jmpbuf, para_type_error);
			}
			else if (ret = have_identv(pvar)) {
				if (!(!strcmp(pvar->type[ret], para->type) && pvar->array_flag[ret] == para->array_flag))//类型要一致
					longjmp(jmpbuf, para_type_error);
			}
			else//是变量，但是从所有存储变量的地方都没找到此变量，说明此变量不存在，不可使用
				longjmp(jmpbuf, var_undefined);
			next_node();
			have_space_judge();
		}
		para = para->next;//下一个参数
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


void func_return(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {//返回类型要符合
	have_space_judge();
	if (!strcmp(pfunc->type[pfunc->row], "void")) {//若函数返回值类型为void
		if (!Is_this(Kw_semicolon))
			longjmp(jmpbuf, expression_error);
	}
	else {//则是int、char、float
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
	case Kw_identv:		//可能是赋值表达式,也可能是不赋值表达式
		func_identv(pvar, pvar_in, pfunc, in_func_flag);
		if (!Is_this(Kw_semicolon))
			longjmp(jmpbuf, lack_semicolon);
		next_node();//走掉';'号
		have_space_judge();
		break;

	case Kw_not:		//不赋值的表达式处理
	case Kw_minus:
	case Kw_openpa:
	case Kw_cchar:
	case Kw_cint:
	case Kw_cfloat:
		func_other(pvar, pvar_in, pfunc, in_func_flag);
		if (!Is_this(Kw_semicolon))
			longjmp(jmpbuf, lack_semicolon);
		next_node();//走掉';'号
		have_space_judge();
		break;

	case Kw_identf://函数调用处理
		func_identf(pvar, pvar_in, pfunc, in_func_flag);
		if (Is_this(Kw_comma)) {
			next_node();//走掉';'或者','号
			have_space_judge();
			case_comma(pvar, pvar_in, pfunc, in_func_flag);
		}
		else if (Is_this(Kw_semicolon)) {
			next_node();//走掉';'或者','号
			have_space_judge();
		}
		else
			longjmp(jmpbuf, expression_error);
		break;
	case Kw_notes:
		next_node();//走掉';'或者','号
		have_space_judge();
		case_comma(pvar, pvar_in, pfunc, in_func_flag);
		break;

	default:
		longjmp(jmpbuf, expression_error);
	}
}


void func_while_or_for_body_one(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {//无'{',后面只能接一句语句
	have_space_judge();
	switch (pcur->KwCode) {
	case Kw_identv:		//可能是赋值表达式,也可能是不赋值表达式
		func_identv(pvar, pvar_in, pfunc, in_func_flag);
		if (!Is_this(Kw_semicolon))
			longjmp(jmpbuf, lack_semicolon);
		next_node();//走掉';'号
		have_space_judge();
		break;

	case Kw_not:		//不赋值的表达式处理
	case Kw_minus:
	case Kw_openpa:
	case Kw_cchar:
	case Kw_cint:
	case Kw_cfloat:
		func_other(pvar, pvar_in, pfunc, in_func_flag);
		if (!Is_this(Kw_semicolon))
			longjmp(jmpbuf, lack_semicolon);
		next_node();//走掉';'号
		have_space_judge();
		break;

	case Kw_identf://函数调用处理
		func_identf(pvar, pvar_in, pfunc, in_func_flag);//内部走掉','或';'
		if (Is_this(Kw_comma)) {
			next_node();//走掉';'或者','号
			have_space_judge();
			case_comma(pvar, pvar_in, pfunc, in_func_flag);
		}
		else if (Is_this(Kw_semicolon)) {
			next_node();//走掉';'或者','号
			have_space_judge();
		}
		else
			longjmp(jmpbuf, expression_error);
		break;

	case Kw_if:
		next_node();
		++stack_Kw_if;
		func_if(pvar, pvar_in, pfunc, in_func_flag);
		next_node();//走掉'}'或者';'
		have_space_judge();
		break;

	case Kw_for:
		next_node();
		func_for(pvar, pvar_in, pfunc, in_func_flag);
		next_node();//走掉'}'
		have_space_judge();
		break;

	case Kw_while:
		next_node();
		func_while(pvar, pvar_in, pfunc, in_func_flag);
		next_node();//走掉'}'
		have_space_judge();
		break;

	case Kw_semicolon:	//跳过就行
		next_node();
		have_space_judge();
		break;

	case Kw_return:
		next_node();
		func_return(pvar, pvar_in, pfunc, in_func_flag);
		next_node();//走掉';'号
		have_space_judge();
		break;

	case Kw_notes:		//注释，跳过就行
		next_node();
		have_space_judge();
		func_while_or_for_body_one(pvar, pvar_in, pfunc, in_func_flag);//必须有一条语句
		break;

	case Kw_break://循环体内
		next_node();
		have_space_judge();
		if (!Is_this(Kw_semicolon))
			longjmp(jmpbuf, expression_error);
		next_node();
		have_space_judge();
		break;

	case Kw_continue://循环体内
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


void func_while_or_for_body_two(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {//有'{'，进入while内部处理
	have_space_judge();
	int while_or_for_grade = Kw_begin_grade;		//在第几层while中
	Key_Word* memo = pcur;
	while (Kw_begin_grade > (while_or_for_grade - 1)) {//若两边相等，推出该while循环
		switch (pcur->KwCode) {
		case Kw_char:		//一样的处理方式
		case Kw_int:
		case Kw_float:
			next_node();
			func_type(pvar, pvar_in, pfunc, memo, in_func_flag);
			next_node();//走掉';'号
			have_space_judge();
			break;

		case Kw_identv:		//可能是赋值表达式,也可能是不赋值表达式
			func_identv(pvar, pvar_in, pfunc, in_func_flag);
			if (!Is_this(Kw_semicolon))
				longjmp(jmpbuf, lack_semicolon);
			next_node();//走掉';'号
			have_space_judge();
			break;

		case Kw_not:		//不赋值的表达式处理
		case Kw_minus:
		case Kw_openpa:
		case Kw_cchar:
		case Kw_cint:
		case Kw_cfloat:
			func_other(pvar, pvar_in, pfunc, in_func_flag);
			if (!Is_this(Kw_semicolon))
				longjmp(jmpbuf, lack_semicolon);
			next_node();//走掉';'号
			have_space_judge();
			break;

		case Kw_struct: //声明结构体类型或结构体变量,存放在局部变量体中
			struct_dispose(pvar, pvar_in, pfunc, in_func_flag);
			next_node();
			break;

		case Kw_identf://函数调用处理
			func_identf(pvar, pvar_in, pfunc, in_func_flag);
			if (Is_this(Kw_comma)) {
				next_node();//走掉';'或者','号
				have_space_judge();
				case_comma(pvar, pvar_in, pfunc, in_func_flag);
			}
			else if (Is_this(Kw_semicolon)) {
				next_node();//走掉';'或者','号
				have_space_judge();
			}
			else
				longjmp(jmpbuf, expression_error);
			break;

		case Kw_if:
			next_node();
			++stack_Kw_if;
			func_if(pvar, pvar_in, pfunc, in_func_flag);
			next_node();//走掉'}'或者';'
			have_space_judge();
			break;

		case Kw_for:
			next_node();
			func_for(pvar, pvar_in, pfunc, in_func_flag);
			next_node();//走掉'}'
			have_space_judge();
			break;

		case Kw_while:
			next_node();
			func_while(pvar, pvar_in, pfunc, in_func_flag);
			next_node();//走掉'}'
			have_space_judge();
			break;

		case Kw_begin:
			++Kw_begin_grade;
			next_node();
			have_space_judge();
			break;
		case Kw_end:
			destroy_var(pvar_in, Kw_begin_grade);//销毁大于等于此层次的局部变量
			--Kw_begin_grade;
			break;

		case Kw_semicolon:	//跳过就行
			next_node();
			have_space_judge();
			break;

		case Kw_return:
			next_node();
			func_return(pvar, pvar_in, pfunc, in_func_flag);
			next_node();//走掉';'号
			have_space_judge();
			break;

		case Kw_notes:		//注释，跳过就行
			next_node();
			have_space_judge();
			break;

		case Kw_break://循环体内
			next_node();
			have_space_judge();
			if (!Is_this(Kw_semicolon))
				longjmp(jmpbuf, expression_error);
			next_node();
			have_space_judge();
			break;

		case Kw_continue://循环体内
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
	if (!Is_this(Kw_semicolon)) {//则有表达式
		if (Is_this(Kw_identv))
			func_identv(pvar, pvar_in, pfunc, in_func_flag);
		else
			expression(pvar, pvar_in, pfunc, in_func_flag);
	}
	if (!Is_this(Kw_semicolon))//必须是';'
		longjmp(jmpbuf, lack_semicolon);
	next_node();
	have_space_judge();
	if (!Is_this(Kw_semicolon)) {//则有表达式
		if (Is_this(Kw_identv))
			func_identv(pvar, pvar_in, pfunc, in_func_flag);
		else
			expression(pvar, pvar_in, pfunc, in_func_flag);
	}
	if (!Is_this(Kw_semicolon))//必须是';'
		longjmp(jmpbuf, lack_semicolon);
	next_node();
	have_space_judge();
	if (!Is_this(Kw_closepa)) {//则有表达式
		if (Is_this(Kw_identv))
			func_identv(pvar, pvar_in, pfunc, in_func_flag);
		else
			expression(pvar, pvar_in, pfunc, in_func_flag);
	}
	if (!Is_this(Kw_closepa))//必须是')'
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


void func_if(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {//if语句处理
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
	if (Is_this(Kw_begin)) {//if后面接'{',进入处理
		++Kw_begin_grade;
		next_node();
		have_space_judge();
		func_if_else_body_two(pvar, pvar_in, pfunc, in_func_flag);
	}
	else//那就只能接一句
		func_if_else_body_one(pvar, pvar_in, pfunc, in_func_flag);
	next_node();//走掉';'或'}'
	have_space_judge();
	while (Is_this(Kw_notes)) {//走掉注释
		next_node();
		have_space_judge();
	}
	if (Is_this(Kw_else)) //if语句处理后，后面跟着else(也可能是else if)
		func_else_if(pvar, pvar_in, pfunc, in_func_flag);
}


void func_else_if(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {
	have_space_judge();
	if (Is_this(Kw_else)) {//if语句处理后，后面跟着else
		next_node();
		have_space_judge();
		if (Is_this(Kw_if)) {//判断是否else if 语句
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
			if (Is_this(Kw_begin)) {//else if（）后面接着'{'，进入处理
				++Kw_begin_grade;
				next_node();
				have_space_judge();
				func_if_else_body_two(pvar, pvar_in, pfunc, in_func_flag);
			}
			else
				func_if_else_body_one(pvar, pvar_in, pfunc, in_func_flag);
			next_node();
			have_space_judge();
			while (Is_this(Kw_notes)) {//走掉注释
				next_node();
				have_space_judge();
			}
			if (Is_this(Kw_else)) {
				func_else_if(pvar, pvar_in, pfunc, in_func_flag);
			}

		}
		else if (Is_this(Kw_begin)) {//else 后接'{',进入处理
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

	case Kw_identv:		//可能是赋值表达式,也可能是不赋值表达式
		func_identv(pvar, pvar_in, pfunc, in_func_flag);
		if (!Is_this(Kw_semicolon))
			longjmp(jmpbuf, lack_semicolon);
		next_node();//走掉';'号
		have_space_judge();
		break;

	case Kw_not:		//不赋值的表达式处理
	case Kw_minus:
	case Kw_openpa:
	case Kw_cchar:
	case Kw_cint:
	case Kw_cfloat:
		func_other(pvar, pvar_in, pfunc, in_func_flag);
		if (!Is_this(Kw_semicolon))
			longjmp(jmpbuf, lack_semicolon);
		next_node();//走掉';'号
		have_space_judge();
		break;

	case Kw_identf://函数调用处理
		func_identf(pvar, pvar_in, pfunc, in_func_flag);//内部走掉','或';'
		if (Is_this(Kw_comma)) {
			next_node();//走掉';'或者','号
			have_space_judge();
			case_comma(pvar, pvar_in, pfunc, in_func_flag);
		}
		else if (Is_this(Kw_semicolon)) {
			next_node();//走掉';'或者','号
			have_space_judge();
		}
		else
			longjmp(jmpbuf, expression_error);
		break;

	case Kw_if:
		next_node();
		++stack_Kw_if;
		func_if(pvar, pvar_in, pfunc, in_func_flag);
		next_node();//走掉'}'或者';'
		have_space_judge();
		break;

	case Kw_for:
		next_node();
		func_for(pvar, pvar_in, pfunc, in_func_flag);
		next_node();//走掉'}'或者';'
		have_space_judge();
		break;

	case Kw_while:
		next_node();
		func_while(pvar, pvar_in, pfunc, in_func_flag);
		next_node();//走掉'}'或者';'
		have_space_judge();
		break;

	case Kw_semicolon:	//跳过就行
		next_node();
		have_space_judge();
		break;

	case Kw_return:
		next_node();
		func_return(pvar, pvar_in, pfunc, in_func_flag);
		next_node();//走掉';'号
		have_space_judge();
		break;

	case Kw_notes:		//注释，跳过就行
		next_node();
		have_space_judge();
		func_if_else_body_one(pvar, pvar_in, pfunc, in_func_flag);//此if语句尚未结束,再进去
		break;

	default:
		longjmp(jmpbuf, expression_error);
	}
}


void func_if_else_body_two(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {
	have_space_judge();
	int while_if_grade = Kw_begin_grade;		//在第几层while中
	Key_Word* memo = pcur;
	while (Kw_begin_grade > (while_if_grade - 1)) {//若两边相等，推出该while循环
		switch (pcur->KwCode) {

		case Kw_char:		//一样的处理方式
		case Kw_int:
		case Kw_float:
			next_node();
			func_type(pvar, pvar_in, pfunc, memo, in_func_flag);
			next_node();//走掉';'号
			have_space_judge();
			break;


		case Kw_identv:		//可能是赋值表达式,也可能是不赋值表达式
			func_identv(pvar, pvar_in, pfunc, in_func_flag);
			if (!Is_this(Kw_semicolon))
				longjmp(jmpbuf, lack_semicolon);
			next_node();//走掉';'号
			have_space_judge();
			break;

		case Kw_not:		//不赋值的表达式处理
		case Kw_minus:
		case Kw_openpa:
		case Kw_cchar:
		case Kw_cint:
		case Kw_cfloat:
			func_other(pvar, pvar_in, pfunc, in_func_flag);
			if (!Is_this(Kw_semicolon))
				longjmp(jmpbuf, lack_semicolon);
			next_node();//走掉';'号
			have_space_judge();
			break;

		case Kw_struct: //声明结构体类型或结构体变量,存放在局部变量体中
			struct_dispose(pvar, pvar_in, pfunc, in_func_flag);
			next_node();
			break;


		case Kw_identf://函数调用处理
			func_identf(pvar, pvar_in, pfunc, in_func_flag);
			if (Is_this(Kw_comma)) {
				next_node();//走掉';'或者','号
				have_space_judge();
				case_comma(pvar, pvar_in, pfunc, in_func_flag);
			}
			else if (Is_this(Kw_semicolon)) {
				next_node();//走掉';'或者','号
				have_space_judge();
			}
			else
				longjmp(jmpbuf, expression_error);
			break;

		case Kw_if:
			next_node();
			func_if(pvar, pvar_in, pfunc, in_func_flag);
			next_node();//走掉'}'或者';'
			have_space_judge();
			break;

		case Kw_for:
			next_node();
			func_for(pvar, pvar_in, pfunc, in_func_flag);
			next_node();//走掉'}'
			have_space_judge();
			break;

		case Kw_while:
			next_node();
			func_while(pvar, pvar_in, pfunc, in_func_flag);
			next_node();//走掉'}'
			have_space_judge();
			break;

		case Kw_begin:
			++Kw_begin_grade;
			next_node();
			have_space_judge();
			break;

		case Kw_end:
			destroy_var(pvar_in, Kw_begin_grade);//销毁大于等于此层次的局部变量
			--Kw_begin_grade;
			break;

		case Kw_semicolon:	//跳过就行
			next_node();
			have_space_judge();
			break;

		case Kw_return:
			next_node();
			func_return(pvar, pvar_in, pfunc, in_func_flag);
			next_node();//走掉';'号
			have_space_judge();
			break;

		case Kw_notes:		//注释，跳过就行
			next_node();
			have_space_judge();
			break;

		default:
			longjmp(jmpbuf, expression_error);
		}
	}
}


void destroy_var(variable* pvar_in, int grade) {//销毁层次高的局部变量
	int i = 1;
	for (i; i < pvar_in->row; ++i) {
		if (pvar_in->grade[i] >= grade) {
			member* temp1 = NULL, * temp2 = NULL;
			memset(pvar_in->word[i], 0, sizeof(pvar_in->word[i]));
			memset(pvar_in->type[i], 0, sizeof(pvar_in->type[i]));
			if (pvar_in->part[i]) {
				free(pvar_in->part[i]->init_flag);
				for (int j = 0; j < pvar_in->count - 1; ++j) {//若是结构体数组，销毁
					temp1 = pvar_in->part[i]->mem[i], temp2 = NULL;
					while (temp1) {//若是结构体,销毁其成员
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
			while (temp1) {//若是结构体,销毁其成员
				temp2 = temp1;
				if (temp2->part_init)
					free(temp2->part_init);
				free(temp2);
				temp1 = temp1->next;
			}
			pvar_in->mem[i] = NULL;
			if (i != (pvar_in->row - 1)) {//最后一个变量
				strcpy(pvar_in->word[i], pvar_in->word[pvar_in->row - 1]);
				strcpy(pvar_in->type[i], pvar_in->type[pvar_in->row - 1]);
				pvar_in->array_flag[i] = pvar_in->array_flag[pvar_in->row - 1];
				pvar_in->array_count[i] = pvar_in->array_count[pvar_in->row - 1];
				pvar_in->init_flag[i] = pvar_in->init_flag[pvar_in->row - 1];
				pvar_in->grade[i] = pvar_in->grade[pvar_in->row - 1];
				pvar_in->mem[i] = pvar_in->mem[pvar_in->row - 1];
				pvar_in->part[i] = pvar_in->part[pvar_in->row - 1];//以上将最后一个变量复制到当前已销毁的变量位置

				memset(pvar_in->word[pvar_in->row - 1], 0, sizeof(pvar_in->word[pvar_in->row - 1]));
				memset(pvar_in->type[pvar_in->row - 1], 0, sizeof(pvar_in->type[pvar_in->row - 1]));
				pvar_in->array_flag[pvar_in->row - 1] = 0;
				pvar_in->array_count[pvar_in->row - 1] = 0;
				pvar_in->init_flag[pvar_in->row - 1] = 0;
				pvar_in->grade[pvar_in->row - 1] = 0;
				pvar_in->mem[pvar_in->row - 1] = NULL;
				pvar_in->part[pvar_in->row - 1] = NULL;//将最后一个变量置为空
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
			Key_Word* mark = pcur;		//记录struct
			int length = strlen(mark->spell);
			next_node();
			have_space_judge();
			if (!Is_this(Kw_identv))
				longjmp(jmpbuf, unknown_struct_type);
			strcpy(pnew->type, mark->spell);
			strcpy(pnew->type + length, pcur->spell);//存下该结构体类型
			int flag = 0, i = 1;							//是否存在该结构体类型的标志
			for (i; i < pvar->row;) {
				int ret = strcmp(pnew->type, pvar->type[i]);
				if (0 == ret) {		//则存在该结构体类型
					flag = 1;
					break;
				}
			}
			if (!flag)		//则不存在该结构体类型
				longjmp(jmpbuf, unknown_struct_type);
			pnew->mem = (member*)calloc(1, sizeof(member));//为结构体内部成员申请一样的结构体内部成员空间
			*(pnew->mem) = *(pvar->mem[i]);		//将其同步为一样的设置;
			member* q = pvar->mem[i]->next;		//下一个结构体成员
			member* p = pnew->mem, * pn = NULL;
			while (q) {	//同步为一样的结构体
				pn = (member*)calloc(1, sizeof(member));
				*(pn) = *q;				//成员一致						
				p->next = pn;			//结构体内部成员指向下个结构体内部成员
				p = p->next;
				q = q->next;
			}		//到这将结构体的内部成员同步完毕
			next_node();
			have_space_judge();
		}
		if (Is_this(Kw_identv)) {			//如果不是变量名，则是声明;如果是变量名，可能是声明，也可能是定义;这里还不知道
			strcpy(pnew->word, pcur->spell);
			next_node();
			have_space_judge();
		}
		if (Is_this(Kw_openbr)) {
			next_node();
			have_space_judge();
			if (Is_this(Kw_cint)) {	//不确定是函数定义还是函数声明，故以此代替
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
		if (NULL == pfunc->para[pfunc->row]) {//若处理的是第一个成员
			pfunc->para[pfunc->row] = pnew;
		}
		else {	//那就是之后的成员
			parameter* next = pfunc->para[pfunc->row];
			while (next) {		//让temp指向已有的最后一个成员
				temp = next;
				next = next->next;
			}
			temp->next = pnew;//连上
		}
		temp = pnew;	//最新最后一个成员
		if (Is_this(Kw_comma)) {//可能还有参数
			next_node();
			parameter_handle(pvar, pfunc, temp);
		}
		else if (Is_this(Kw_closepa)) {//参数处理完毕
			next_node();
		}
		else
			longjmp(jmpbuf, expression_error);
	}
	else if (Is_this(Kw_closepa)) {		//参数处理完毕
		Key_Word* front = pcur->prior;
		while (Kw_space == front->KwCode || Kw_tabs == front->KwCode) {
			front = front->prior;
		}
		if (Kw_comma == front->KwCode)		//若')'前有一个','
			longjmp(jmpbuf, expression_error);
		next_node();
	}
	else
		longjmp(jmpbuf, type_error);
}


void identv_statement_one(variable* pvar, variable* pvar_in, function* pfunc, Key_Word* memo, int in_func_flag) {//变量声明及初始化处理
	have_space_judge();
	variable* pnow = NULL;
	if (in_func_flag)//函数体内调用
		pnow = pvar_in;
	else//外部调用
		pnow = pvar;
	if (Kw_identv == pcur->KwCode) {
		pnow->grade[pnow->row] = Kw_begin_grade;
		strcpy(pnow->word[pnow->row], pcur->spell);	//存上变量名称
		strcpy(pnow->type[pnow->row], memo->spell);	//其类型
		if (in_func_flag && 1 == Kw_begin_grade) {//对比函数参数
			if (cmp_para(pfunc, pnow))//看看与函数参数是否有重名
				longjmp(jmpbuf, var_repeat_definition);
		}
		if (repeat_judge(pnow))				//变量不能重名
			longjmp(jmpbuf, var_repeat_definition);
		next_node();
		identv_statement_two(pvar, pvar_in, pfunc, 0, memo, 0, in_func_flag);				//是否还有成员
	}
	else if (Kw_semicolon == pcur->KwCode) {				//防止无变量与identv_statement_two()函数到此函数出错
		Key_Word* p = pcur;
		p = p->prior;
		while (Kw_space == p->KwCode || Kw_tabs == p->KwCode) {
			p = p->prior;
		}
		if (Kw_closebr == pcur->KwCode || Kw_identv == pcur->KwCode) {
			//前面必须是变量,若该变量为数组,最后一个符为']'
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
	if (in_func_flag)//函数体内调用
		pnow = pvar_in;
	else//外部调用
		pnow = pvar;
	if (Kw_comma == pcur->KwCode) {					//后面可能还有变量;pnow->init_flag[pnow->row]初始为零即未初始化		
		next_node();
		++pnow->row;
		variable_expand(pnow);				//可能需要扩容
		identv_statement_one(pvar, pvar_in, pfunc, memo, in_func_flag);
	}
	else if (Kw_semicolon == pcur->KwCode) {		//此变量处理完毕

	}
	else if (Kw_openbr == pcur->KwCode) {			//若是左中括号，即数组
		if (1 == from)							//'[]'后还是'[]'，错误（不支持二维数组）
			longjmp(jmpbuf, array_error);
		next_node();
		have_space_judge();
		if (Kw_cint != pcur->KwCode)		//数组个数须为正整数
			longjmp(jmpbuf, array_error);
		pnow->array_flag[pnow->row] = 1;
		pnow->array_count[pnow->row] = string_value(pcur->spell);		//将字符转换为整数值
		if (pnow->array_count[pnow->row] <= 0)			//数组长度不能为零或负数
			longjmp(jmpbuf, array_error);
		next_node();
		have_space_judge();
		if (Kw_closebr != pcur->KwCode)		//右中括号
			longjmp(jmpbuf, lack_closebr);
		identv_array_part_storage(pnow);	//其余数组成员
		next_node();
		identv_statement_two(pvar, pvar_in, pfunc, 1, memo, 0, in_func_flag);					//']'后下一个非空字符	,要么为',',要么为';'	
	}
	else if (Kw_assign == pcur->KwCode) {			//'='初始化处理
		if (1 == assign)
			longjmp(jmpbuf, expression_error);
		next_node();
		if (pnow->array_flag[pnow->row]) {
			more_identv_init(pvar, pvar_in, pfunc, in_func_flag);		//其余数组成员标记已初始化
			identv_array_part_init(pnow);
		}
		else {		//非数组处理
			if (Kw_begin == pcur->KwCode) {
				next_node();
				have_space_judge();
				++stack_Kw_begin;
			}
			expression(pvar, pvar_in, pfunc, in_func_flag);				//初始化完一个变量	
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
		identv_statement_two(pvar, pvar_in, pfunc, 1, memo, 1, in_func_flag);				//可能还有结构体变量需要处理
	}
	else
		longjmp(jmpbuf, expression_error);
}


void more_identv_init(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {	//处理数组初始化
	have_space_judge();
	variable* pnow = NULL;
	if (in_func_flag)//函数体内调用
		pnow = pvar_in;
	else//外部调用
		pnow = pvar;
	if (!strcmp("char", pnow->type[pnow->row]) && Is_this(Kw_cstr)) {//变量类型为char且此时pcur指向字符串
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
	if (in_func_flag)//函数体内调用
		pnow = pvar_in;
	else//外部调用
		pnow = pvar;
	if (Is_this(Kw_begin)) {			//'{'符
		++stack_Kw_begin;
		if (stack_Kw_begin > 2)
			longjmp(jmpbuf, expression_error);
		next_node();
		more_identv_init_one(pvar, pvar_in, pfunc, in_func_flag);
	}
	else if (Is_this(Kw_cchar) || Is_this(Kw_cint) || Is_this(Kw_cfloat) || Is_this(Kw_not) || Is_this(Kw_minus) || Is_this(Kw_openpa)) {
		expression(pvar, pvar_in, pfunc, in_func_flag);
		more_identv_init_two(pvar, pvar_in, pfunc, 1, 0, in_func_flag);			//后面只能为','、'}'		
	}
	else if (Kw_cstr == pcur->KwCode) {
		if (!strcmp(pnow->type[pnow->row], "char")) {//字符串,字符数组只能初始化一次
			if (stack_Kw_begin > 1)
				longjmp(jmpbuf, lack_value);
			next_node();
			int length = strlen(pcur->spell) - 2;							//扣除两个'"'的长度
			if (length > pnow->array_count[pnow->row])				//大于则越界
				longjmp(jmpbuf, array_error);
			more_identv_init_two(pvar, pvar_in, pfunc, pnow->array_count[pnow->row], 0, in_func_flag);			//后面只能为','、'}'且此成员已初始化完毕			
		}
		else
			longjmp(jmpbuf, type_error);
	}
	else							//类型不一致，错误
		longjmp(jmpbuf, expression_error);
}


void more_identv_init_two(variable* pvar, variable* pvar_in, function* pfunc, int count, int flag, int in_func_flag) {
	have_space_judge();									//	flag标记在进入内部成员变量数组时是否出现过'{'
	variable* pnow = NULL;
	if (in_func_flag)//函数体内调用
		pnow = pvar_in;
	else//外部调用
		pnow = pvar;
	if (Kw_comma == pcur->KwCode) {
		if (count < pnow->array_count[pnow->row]) {			//若为数组且未越界，继续看看是否接着初始化数组成员
			next_node();
			more_identv_init_three(pvar, pvar_in, pfunc, count, 0, flag, in_func_flag);
		}
		else {			//数组成员皆已初始化，返回
			next_node();
			Key_Word* q = pcur;
			while (q && (Kw_tabs == q->KwCode || Kw_space == q->KwCode)) {
				q = q->next;
			}
			if (Kw_end == q->KwCode) {			//存在如"{3,}"
				--stack_Kw_begin;
				pcur = q;
				Is_init_more(flag);
				next_node();
				if (stack_Kw_begin)		//不会小于零
					more_identv_init_two(pvar, pvar_in, pfunc, count, 0, in_func_flag);//后面只能为','、'}'
			}
		}
	}
	else if (Kw_end == pcur->KwCode) {
		--stack_Kw_begin;
		Is_init_more(flag);
		if (0 == stack_Kw_begin) {			//匹配成功，整个数组初始化完毕
			next_node();
		}
		else if (stack_Kw_begin < 0)
			longjmp(jmpbuf, lack_begin);
		else {
			next_node();
			more_identv_init_two(pvar, pvar_in, pfunc, count, flag, in_func_flag);//后面只能为','、'}'
		}
	}
	else
		longjmp(jmpbuf, expression_error);
}


void more_identv_init_three(variable* pvar, variable* pvar_in, function* pfunc, int count, int from, int flag, int in_func_flag) {//对数组成员处理	  //from代表是从哪进入此函数的
	have_space_judge();
	if (Is_this(Kw_cchar) || Is_this(Kw_cint) || Is_this(Kw_cfloat) || Is_this(Kw_not) || Is_this(Kw_minus) || Is_this(Kw_openpa)) {
		expression(pvar, pvar_in, pfunc, in_func_flag);
		++count;
		more_identv_init_two(pvar, pvar_in, pfunc, count, 0, in_func_flag);			//后面只能为','、'}'		
	}
	else if (Kw_end == pcur->KwCode) {
		if (1 == from)						//若是more_identv_init_three()进来的，即此括号匹配内部为空
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
			more_identv_init_two(pvar, pvar_in, pfunc, count, flag, in_func_flag);		//后面只能为','、'}'
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


void expression(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {//如果是在函数体内初始化可以用变量,函数体外必须用常量
	have_space_judge();
	seventh(pvar, pvar_in, pfunc, in_func_flag);
}


void seventh(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {			//处理'||'
	sixth(pvar, pvar_in, pfunc, in_func_flag);
	while (Kw_or == pcur->KwCode) {
		next_node();
		have_space_judge();
		sixth(pvar, pvar_in, pfunc, in_func_flag);
	}
}


void sixth(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {		//处理'&&'
	fifth(pvar, pvar_in, pfunc, in_func_flag);
	while (Kw_and == pcur->KwCode) {
		next_node();
		have_space_judge();
		fifth(pvar, pvar_in, pfunc, in_func_flag);
	}
}


void fifth(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {		//处理'=='和'!='
	fourth(pvar, pvar_in, pfunc, in_func_flag);
	while (Kw_eq == pcur->KwCode || Kw_neq == pcur->KwCode) {
		next_node();
		have_space_judge();
		fourth(pvar, pvar_in, pfunc, in_func_flag);
	}
}


void fourth(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {		//处理'<'、'<='、'>'和'>='
	third(pvar, pvar_in, pfunc, in_func_flag);
	while (Kw_lt <= pcur->KwCode && Kw_geq >= pcur->KwCode) {
		next_node();
		have_space_judge();
		third(pvar, pvar_in, pfunc, in_func_flag);
	}
}


void third(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag) {				//处理'+'和'-'
	second(pvar, pvar_in, pfunc, in_func_flag, 0);
	while (Kw_plus == pcur->KwCode || Kw_minus == pcur->KwCode) {
		next_node();
		have_space_judge();
		second(pvar, pvar_in, pfunc, in_func_flag, 0);
	}
}


void second(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag, int from) {		//处理'*'、'/'和'%'
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


void in_func_first(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag, int from) {			//处理'('和')'
	if (Kw_identv == pcur->KwCode || (Kw_cchar <= pcur->KwCode && Kw_cfloat >= pcur->KwCode)) {
		if (Kw_identv == pcur->KwCode) {
			int ret = 0;	//记录查到该变量在变量存储体里边的位置
			member* inner = NULL;//记录结构体内部变量的地址
			parameter* func_var = NULL;//记录参数地址
			if (ret = top_first(pvar_in)) {//在函数体内进行expression()且存在此局部变量
				if (pvar_in->array_flag[ret]) {	//若是数组
					next_node();
					have_space_judge();
					if (Kw_openbr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
					next_node();
					have_space_judge();
					expression(pvar, pvar_in, pfunc, in_func_flag);		//'['与']'之间
					if (Kw_closebr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
				}
				if (pvar_in->mem[ret]) {				//若是结构体
					next_node();
					have_space_judge();
					if (Kw_dot != pcur->KwCode)
						longjmp(jmpbuf, expression_error);
					next_node();
					have_space_judge();
					if (!(inner = struct_mem_repeat_judge(pvar_in, ret)))	//是否有该内部成员
						longjmp(jmpbuf, expression_error);
					if (inner->array_flag) {			//若该成员是数组
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
			else if (func_var = have_func_var(pfunc)) {//在函数体内进行expression()且存在此函数参数变量
				if (func_var->array_flag) {	//若是数组
					next_node();
					have_space_judge();
					if (Kw_openbr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
					next_node();
					have_space_judge();
					expression(pvar, pvar_in, pfunc, in_func_flag);		//'['与']'之间
					if (Kw_closebr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
				}
				if (func_var->mem) {				//则是结构体
					next_node();
					have_space_judge();
					if (Kw_dot != pcur->KwCode)
						longjmp(jmpbuf, expression_error);
					next_node();
					have_space_judge();
					if (!(inner = parameter_mem_repeat_judge(func_var)))	//是否有该内部成员
						longjmp(jmpbuf, expression_error);
					if (inner->array_flag) {			//若该成员是数组
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
			else if (ret = have_identv(pvar)) {//则存在此全局变量
				if (pvar->array_flag[ret]) {	//若是数组（结构体数组）
					next_node();
					have_space_judge();
					if (Kw_openbr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
					next_node();
					have_space_judge();
					expression(pvar, pvar_in, pfunc, in_func_flag);		//'['与']'之间
					if (Kw_closebr != pcur->KwCode)
						longjmp(jmpbuf, lack_openbr);
				}
				if (pvar->mem[ret]) {				//则是结构体数组
					next_node();
					have_space_judge();
					if (Kw_dot != pcur->KwCode)
						longjmp(jmpbuf, expression_error);
					next_node();
					have_space_judge();
					if (!(inner = struct_mem_repeat_judge(pvar, ret)))	//是否有该内部成员
						longjmp(jmpbuf, expression_error);
					if (inner->array_flag) {			//若该成员是数组
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
			else//是变量，但是从所有存储变量的地方都没找到此变量，说明此变量不存在，不可使用
				longjmp(jmpbuf, var_undefined);
		}
		else {	//那么就是Kw_cchar、Kw_cint、 Kw_cfloat 
			next_node();
			have_space_judge();
		}
	}
	else if (Kw_openpa == pcur->KwCode) {		//如果是'('
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
	else if (Kw_minus == pcur->KwCode || Kw_not == pcur->KwCode) {	//处理'-'（取负）和'!'	//from代表是从哪来的
		if (1 == from)
			longjmp(jmpbuf, expression_error);
		from = 1;
		next_node();
		have_space_judge();
		in_func_first(pvar, pvar_in, pfunc, in_func_flag, from);
	}
	else //不应出现的其它字符
		longjmp(jmpbuf, expression_error);
}


void  out_func_first(variable* pvar, variable* pvar_in, function* pfunc, int in_func_flag, int from) {
	if (Kw_cchar <= pcur->KwCode && Kw_cfloat >= pcur->KwCode) {
		next_node();
		have_space_judge();
	}
	else if (Kw_openpa == pcur->KwCode) {		//如果是'('
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
	else if (Kw_minus == pcur->KwCode || Kw_not == pcur->KwCode) {	//处理'-'（取负）和'!'	//from代表是从哪来的
		if (1 == from)
			longjmp(jmpbuf, expression_error);
		from = 1;
		next_node();
		have_space_judge();
		out_func_first(pvar, pvar_in, pfunc, in_func_flag, from);
	}
	else //不应出现的其它字符
		longjmp(jmpbuf, expression_error);
}


void identv_dispose(variable* pvar) {//外部变量处理
	have_space_judge();
	if (Is_this(Kw_identv)) {
		//查询是否有该变量
		if (!have_identv(pvar))
			longjmp(jmpbuf, var_undefined);
		next_node();
		identv_one(pvar);
	}
	else
		longjmp(jmpbuf, expression_error);
}


void identv_one(variable* pvar) {//外部变量后只能为','或';'
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