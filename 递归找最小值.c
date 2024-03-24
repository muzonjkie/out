#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#define maxsize 100

typedef struct BiTree{
	int  value;
	struct BiTree *lchild,*rchild;
}BiTree; 





BiTree* BiTcreate(BiTree*T);
void FindMinNode(BiTree*T,int*min);
void MinNode(BiTree*T);




int main()
{
	BiTree *T=NULL;		
T=BiTcreate(T);				//�����ڵ�λ�÷��ظ�T	
MinNode(T);
return 0;
}



BiTree* BiTcreate(BiTree*T)			//�����������ڵ� 
{
	int value;
	BiTree*queue[maxsize];
	int front=0,rear=0;
	BiTree*p=T;									//p�ݴ�T��ֵ 
	while(printf("����ڵ�ֵ\n"),scanf("%d",&value)!=EOF){
		BiTree* pnew=(BiTree*)calloc(1,sizeof(BiTree));			//calloc���ô˿ռ��ʼ��Ϊ0 
		pnew->value=value;
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
	}
	return p;	
}



void FindMinNode(BiTree*T,int*min)
{
	if(T){
		if(T->value<*min)	*min=T->value;			
		FindMinNode(T->lchild,min);
		FindMinNode(T->rchild,min);
}
}


void MinNode(BiTree*T)
{
	if(T){
		int min=T->value;
		FindMinNode(T,&min);
		printf("Min=%d\n",min);
	}
}
