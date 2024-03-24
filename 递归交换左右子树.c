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
T=BiTcreate(T);				//将根节点位置返回给T
Levelorder(T);	
swap_tree(&T);				//成功！ 
Levelorder(T);
return 0;
}



BiTree* BiTcreate(BiTree*T)			//层序生成树节点 
{
	char  nodename;
	BiTree*queue[maxsize];
	int front=0,rear=0;
	BiTree*p=T;									//p暂存T的值 
	while(printf("输入节点值\n"),scanf("%c",&nodename)!=EOF){
		BiTree* pnew=(BiTree*)calloc(1,sizeof(BiTree));			//calloc会让此空间初始化为0 
		pnew->nodename=nodename;
		if(NULL==T)	{					//若根节点为空 
			T=pnew;
			p=T;	}					//p暂存T的值 
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



void swap_tree(BiTree**T)			//完美！ 
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
	printf("层序遍历次序：");
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
T=BiTcreate(T);				//将根节点位置返回给T
Levelorder(T);	
swap_tree(&T);				//成功！ 
Levelorder(T);
return 0;
}



BiTree* BiTcreate(BiTree*T)			//层序生成树节点 
{
	char  nodename;
	BiTree*queue[maxsize];
	int front=0,rear=0;
	BiTree*p=T;									//p暂存T的值 
	while(printf("输入节点值\n"),scanf("%c",&nodename)!=EOF){
		BiTree* pnew=(BiTree*)calloc(1,sizeof(BiTree));			//calloc会让此空间初始化为0 
		pnew->nodename=nodename;
		if(NULL==T)	{					//若根节点为空 
			T=pnew;
			p=T;	}					//p暂存T的值 
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



void swap_tree(BiTree**T)			//完美！ 
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
	printf("层序遍历次序：");
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
