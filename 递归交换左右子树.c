<<<<<<< HEAD
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#define maxsize 100

typedef struct BiTree{
	char  nodename;
	struct BiTree *lchild,*rchild;
}BiTree; 



BiTree* BiTcreate(BiTree*T);
void swap_tree(BiTree**T);
void Levelorder(BiTree*T);


int main()
{
	BiTree *T=NULL;		
T=BiTcreate(T);				//�����ڵ�λ�÷��ظ�T
Levelorder(T);	
swap_tree(&T);				//�ɹ��� 
Levelorder(T);
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



void swap_tree(BiTree**T)			//������ 
{
	BiTree*temp;
	if(*T){
		swap_tree(&(*T)->lchild);
		swap_tree(&(*T)->rchild);
		temp=(*T)->lchild;
		(*T)->lchild=(*T)->rchild;
		(*T)->rchild=temp;
	}
 } 


void Levelorder(BiTree*T)
{
	BiTree*queue[maxsize];
	int front=0,rear=0;	
	queue[rear]=T;
	rear=(rear+1)%maxsize;
	printf("�����������");
	while(rear!=front){
		T=queue[front];
		printf("%c",T->nodename);
		front=(front+1)%maxsize;
		if(NULL!=T->lchild){
			queue[rear]=T->lchild;	
			rear=(rear+1)%maxsize;		}
		if(NULL!=T->rchild){
			queue[rear]=T->rchild;	
			rear=(rear+1)%maxsize;		}
	}
}

=======
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#define maxsize 100

typedef struct BiTree{
	char  nodename;
	struct BiTree *lchild,*rchild;
}BiTree; 



BiTree* BiTcreate(BiTree*T);
void swap_tree(BiTree**T);
void Levelorder(BiTree*T);


int main()
{
	BiTree *T=NULL;		
T=BiTcreate(T);				//�����ڵ�λ�÷��ظ�T
Levelorder(T);	
swap_tree(&T);				//�ɹ��� 
Levelorder(T);
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



void swap_tree(BiTree**T)			//������ 
{
	BiTree*temp;
	if(*T){
		swap_tree(&(*T)->lchild);
		swap_tree(&(*T)->rchild);
		temp=(*T)->lchild;
		(*T)->lchild=(*T)->rchild;
		(*T)->rchild=temp;
	}
 } 


void Levelorder(BiTree*T)
{
	BiTree*queue[maxsize];
	int front=0,rear=0;	
	queue[rear]=T;
	rear=(rear+1)%maxsize;
	printf("�����������");
	while(rear!=front){
		T=queue[front];
		printf("%c",T->nodename);
		front=(front+1)%maxsize;
		if(NULL!=T->lchild){
			queue[rear]=T->lchild;	
			rear=(rear+1)%maxsize;		}
		if(NULL!=T->rchild){
			queue[rear]=T->rchild;	
			rear=(rear+1)%maxsize;		}
	}
}

>>>>>>> 7edc0a04ff39d0dd7f2435bd378bcebed8945e78
