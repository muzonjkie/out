#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#define maxsize 100

typedef struct BiTree{
	char  nodename;
	struct BiTree *lchild,*rchild;
}BiTree; 



BiTree* BiTcreate(BiTree*T);
void BiTreetoexp(BiTree*T,int deep);
void Integral_BiTreetoexp(BiTree*T);
 
int main()
{
	BiTree *T=NULL;		
T=BiTcreate(T);				//�����ڵ�λ�÷��ظ�T
Integral_BiTreetoexp(T);
return 0;
}



BiTree* BiTcreate(BiTree*T)			//�����������ڵ� 
{
	char  nodename;
	BiTree*queue[maxsize];
	int front=0,rear=0;
	BiTree*p=T;									//p�ݴ�T��ֵ 
	while(printf("����ڵ�ֵ\n"),scanf("%c",&nodename)!=EOF){
		BiTree* pnew=(BiTree*)calloc(1,sizeof(BiTree));			//calloc���ô˿ռ��ʼ��Ϊ0 
		pnew->nodename=nodename;
		if(NULL==T)	{					//�����ڵ�Ϊ�� 
			T=pnew;
			p=T;	}					//p�ݴ�T��ֵ 
		else if(NULL==T->lchild){
			T->lchild=pnew;
			queue[rear++]=pnew;		}
		else{
			T->rchild=pnew;
			queue[rear++]=pnew;
			T=queue[front++];		}
			fflush(stdin);			
	}
	return p;	
}


void BiTreetoexp(BiTree*T,int deep)
{
	if(T==NULL)	return;
	else if(NULL==T->lchild&&NULL==T->rchild) 
		printf("%c",T->nodename);
	else{
		if(deep>1)		printf("(");			//�������� 
		BiTreetoexp(T->lchild,deep+1);
		printf("%c",T->nodename);				//������ 
		BiTreetoexp(T->rchild,deep+1);
		if(deep>1)		printf(")");			//����������� 
	}	
} 


void Integral_BiTreetoexp(BiTree*T)
{
	BiTreetoexp(T,1);			//���ĸ߶�Ϊ1 
}
