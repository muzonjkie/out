<<<<<<< HEAD
#include<stdio.h>							
#include<stdlib.h>
#include<stdbool.h>
#define maxsize 20

typedef struct bracketcheck{
	char sign;
	struct bracketcheck* prior;
	struct bracketcheck* next;
}stackNode;									//��ָ��˫ѭ��ʽ������ջ 


bool StackBraket(int *sum);
bool StackBraket_2(char str[],int*sum);

int main()
{
	int sum=0;
	char str[]="()k[]{";
	printf("%s\n",str);
	if(StackBraket_2(str,&sum)){
		printf("ȫ��ƥ��ɹ���\n");
		printf("ƥ��ɹ������Ŷ���Ϊ%d��\n",sum);		}
	else{
		printf("ƥ��ʧ�ܣ�\n");
		printf("�ۼ�ƥ��ɹ������Ŷ���Ϊ%d��\n",sum);		}	
return 0;	
}

	
bool StackBraket(int *sum)									//��ʽ 
{	
	stackNode* head=(stackNode*)malloc(sizeof(stackNode));
	head->next=NULL;
	head->prior=NULL;
	char symbol;
	int cnt=0;
	stackNode*p=NULL,*end=head,*temp;
	while(printf("���������ݣ�\n"),scanf("%c",&symbol)!=EOF){
		p=(stackNode*)malloc(sizeof(stackNode));
		p->sign=symbol;
		p->next=NULL;	
		switch(p->sign){
			case '(':  	p->prior=end; end->next=p; end=p; cnt++; break;  		//����β��Ϊջ�� 
			case '[':	p->prior=end; end->next=p; end=p; cnt++; break;
 			case '{':	p->prior=end; end->next=p; end=p; cnt++; break;
 			case ')':	if(cnt==0||end->sign!='(') return false;				//��һ�������������Ž�����������
			 			temp=end; end=end->prior; end->next=temp->next; 
						free(temp); free(p); 
						cnt--; (*sum)++; printf("ƥ��ɹ���\n"); break;			
			case ']':	if(cnt==0||end->sign!='[') return false;
						temp=end; end=end->prior; end->next=temp->next; 
						free(temp); free(p); 
						cnt--; (*sum)++; printf("ƥ��ɹ���\n"); break;
			case '}':	if(cnt==0||end->sign!='{') return false;
						temp=end; end=end->prior; end->next=temp->next; 
						free(temp); free(p); 
						cnt--; (*sum)++; printf("ƥ��ɹ���\n"); break;
			default:	free(p); break; 
		}
	fflush(stdin);							//�������������ֹ�س���Ӱ�� 
}				 
if(cnt==0)		return true;				//ʣ��ڵ��� 		
else 	return false;   	
} 



//-----------------------�汾��------------------------ 

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
			case ')':	if(top==-1)	return false; 				//��һ�������������Ž�����������
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
	if(top==-1)		return true;				//ʣ��ڵ��� 		
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
}stackNode;									//��ָ��˫ѭ��ʽ������ջ 


bool StackBraket(int *sum);
bool StackBraket_2(char str[],int*sum);

int main()
{
	int sum=0;
	char str[]="()k[]{";
	printf("%s\n",str);
	if(StackBraket_2(str,&sum)){
		printf("ȫ��ƥ��ɹ���\n");
		printf("ƥ��ɹ������Ŷ���Ϊ%d��\n",sum);		}
	else{
		printf("ƥ��ʧ�ܣ�\n");
		printf("�ۼ�ƥ��ɹ������Ŷ���Ϊ%d��\n",sum);		}	
return 0;	
}

	
bool StackBraket(int *sum)									//��ʽ 
{	
	stackNode* head=(stackNode*)malloc(sizeof(stackNode));
	head->next=NULL;
	head->prior=NULL;
	char symbol;
	int cnt=0;
	stackNode*p=NULL,*end=head,*temp;
	while(printf("���������ݣ�\n"),scanf("%c",&symbol)!=EOF){
		p=(stackNode*)malloc(sizeof(stackNode));
		p->sign=symbol;
		p->next=NULL;	
		switch(p->sign){
			case '(':  	p->prior=end; end->next=p; end=p; cnt++; break;  		//����β��Ϊջ�� 
			case '[':	p->prior=end; end->next=p; end=p; cnt++; break;
 			case '{':	p->prior=end; end->next=p; end=p; cnt++; break;
 			case ')':	if(cnt==0||end->sign!='(') return false;				//��һ�������������Ž�����������
			 			temp=end; end=end->prior; end->next=temp->next; 
						free(temp); free(p); 
						cnt--; (*sum)++; printf("ƥ��ɹ���\n"); break;			
			case ']':	if(cnt==0||end->sign!='[') return false;
						temp=end; end=end->prior; end->next=temp->next; 
						free(temp); free(p); 
						cnt--; (*sum)++; printf("ƥ��ɹ���\n"); break;
			case '}':	if(cnt==0||end->sign!='{') return false;
						temp=end; end=end->prior; end->next=temp->next; 
						free(temp); free(p); 
						cnt--; (*sum)++; printf("ƥ��ɹ���\n"); break;
			default:	free(p); break; 
		}
	fflush(stdin);							//�������������ֹ�س���Ӱ�� 
}				 
if(cnt==0)		return true;				//ʣ��ڵ��� 		
else 	return false;   	
} 



//-----------------------�汾��------------------------ 

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
			case ')':	if(top==-1)	return false; 				//��һ�������������Ž�����������
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
	if(top==-1)		return true;				//ʣ��ڵ��� 		
	else 	return false; 
}


>>>>>>> 7edc0a04ff39d0dd7f2435bd378bcebed8945e78
