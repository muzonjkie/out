<<<<<<< HEAD
#include<stdio.h>							
#include<stdlib.h>
#include<stdbool.h>
#define maxsize 20

typedef struct bracketcheck{
	char sign;
	struct bracketcheck* prior;
	struct bracketcheck* next;
}stackNode;									//单指针双循环式链表做栈 


bool StackBraket(int *sum);
bool StackBraket_2(char str[],int*sum);

int main()
{
	int sum=0;
	char str[]="()k[]{";
	printf("%s\n",str);
	if(StackBraket_2(str,&sum)){
		printf("全部匹配成功！\n");
		printf("匹配成功的括号对数为%d对\n",sum);		}
	else{
		printf("匹配失败！\n");
		printf("累计匹配成功的括号对数为%d对\n",sum);		}	
return 0;	
}

	
bool StackBraket(int *sum)									//链式 
{	
	stackNode* head=(stackNode*)malloc(sizeof(stackNode));
	head->next=NULL;
	head->prior=NULL;
	char symbol;
	int cnt=0;
	stackNode*p=NULL,*end=head,*temp;
	while(printf("请输入数据！\n"),scanf("%c",&symbol)!=EOF){
		p=(stackNode*)malloc(sizeof(stackNode));
		p->sign=symbol;
		p->next=NULL;	
		switch(p->sign){
			case '(':  	p->prior=end; end->next=p; end=p; cnt++; break;  		//以链尾作为栈顶 
			case '[':	p->prior=end; end->next=p; end=p; cnt++; break;
 			case '{':	p->prior=end; end->next=p; end=p; cnt++; break;
 			case ')':	if(cnt==0||end->sign!='(') return false;				//第一个就输入右括号结束整个程序
			 			temp=end; end=end->prior; end->next=temp->next; 
						free(temp); free(p); 
						cnt--; (*sum)++; printf("匹配成功！\n"); break;			
			case ']':	if(cnt==0||end->sign!='[') return false;
						temp=end; end=end->prior; end->next=temp->next; 
						free(temp); free(p); 
						cnt--; (*sum)++; printf("匹配成功！\n"); break;
			case '}':	if(cnt==0||end->sign!='{') return false;
						temp=end; end=end->prior; end->next=temp->next; 
						free(temp); free(p); 
						cnt--; (*sum)++; printf("匹配成功！\n"); break;
			default:	free(p); break; 
		}
	fflush(stdin);							//清除缓冲区，防止回车符影响 
}				 
if(cnt==0)		return true;				//剩余节点数 		
else 	return false;   	
} 



//-----------------------版本二------------------------ 

bool StackBraket_2(char str[],int*sum)
{
	char stack[maxsize];
	int i=0,top=-1;
	char e;
	while(str[i]!='\0'){
		switch(str[i]){
			case '(':  	stack[++top]='(';  break;  		 
			case '[':	stack[++top]='[';  break;
 			case '{':	stack[++top]='{';  break;	
			case ')':	if(top==-1)	return false; 				//第一个就输入右括号结束整个程序
						e=stack[top--]; if(e!='(') return false; 
						(*sum)++; break;
			case ']':	if(top==-1)	return false; 
						e=stack[top--]; if(e!='[') return false; 
						(*sum)++; break;
			case '}':	if(top==-1)	return false; 
						e=stack[top--]; if(e!='{') return false; 
						(*sum)++; break;
			default :	break;
		}
		i++;
	}
	if(top==-1)		return true;				//剩余节点数 		
	else 	return false; 
}


=======
#include<stdio.h>							
#include<stdlib.h>
#include<stdbool.h>
#define maxsize 20

typedef struct bracketcheck{
	char sign;
	struct bracketcheck* prior;
	struct bracketcheck* next;
}stackNode;									//单指针双循环式链表做栈 


bool StackBraket(int *sum);
bool StackBraket_2(char str[],int*sum);

int main()
{
	int sum=0;
	char str[]="()k[]{";
	printf("%s\n",str);
	if(StackBraket_2(str,&sum)){
		printf("全部匹配成功！\n");
		printf("匹配成功的括号对数为%d对\n",sum);		}
	else{
		printf("匹配失败！\n");
		printf("累计匹配成功的括号对数为%d对\n",sum);		}	
return 0;	
}

	
bool StackBraket(int *sum)									//链式 
{	
	stackNode* head=(stackNode*)malloc(sizeof(stackNode));
	head->next=NULL;
	head->prior=NULL;
	char symbol;
	int cnt=0;
	stackNode*p=NULL,*end=head,*temp;
	while(printf("请输入数据！\n"),scanf("%c",&symbol)!=EOF){
		p=(stackNode*)malloc(sizeof(stackNode));
		p->sign=symbol;
		p->next=NULL;	
		switch(p->sign){
			case '(':  	p->prior=end; end->next=p; end=p; cnt++; break;  		//以链尾作为栈顶 
			case '[':	p->prior=end; end->next=p; end=p; cnt++; break;
 			case '{':	p->prior=end; end->next=p; end=p; cnt++; break;
 			case ')':	if(cnt==0||end->sign!='(') return false;				//第一个就输入右括号结束整个程序
			 			temp=end; end=end->prior; end->next=temp->next; 
						free(temp); free(p); 
						cnt--; (*sum)++; printf("匹配成功！\n"); break;			
			case ']':	if(cnt==0||end->sign!='[') return false;
						temp=end; end=end->prior; end->next=temp->next; 
						free(temp); free(p); 
						cnt--; (*sum)++; printf("匹配成功！\n"); break;
			case '}':	if(cnt==0||end->sign!='{') return false;
						temp=end; end=end->prior; end->next=temp->next; 
						free(temp); free(p); 
						cnt--; (*sum)++; printf("匹配成功！\n"); break;
			default:	free(p); break; 
		}
	fflush(stdin);							//清除缓冲区，防止回车符影响 
}				 
if(cnt==0)		return true;				//剩余节点数 		
else 	return false;   	
} 



//-----------------------版本二------------------------ 

bool StackBraket_2(char str[],int*sum)
{
	char stack[maxsize];
	int i=0,top=-1;
	char e;
	while(str[i]!='\0'){
		switch(str[i]){
			case '(':  	stack[++top]='(';  break;  		 
			case '[':	stack[++top]='[';  break;
 			case '{':	stack[++top]='{';  break;	
			case ')':	if(top==-1)	return false; 				//第一个就输入右括号结束整个程序
						e=stack[top--]; if(e!='(') return false; 
						(*sum)++; break;
			case ']':	if(top==-1)	return false; 
						e=stack[top--]; if(e!='[') return false; 
						(*sum)++; break;
			case '}':	if(top==-1)	return false; 
						e=stack[top--]; if(e!='{') return false; 
						(*sum)++; break;
			default :	break;
		}
		i++;
	}
	if(top==-1)		return true;				//剩余节点数 		
	else 	return false; 
}


>>>>>>> 7edc0a04ff39d0dd7f2435bd378bcebed8945e78
