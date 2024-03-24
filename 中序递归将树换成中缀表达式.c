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
T=BiTcreate(T);				//将根节点位置返回给T
Integral_BiTreetoexp(T);
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


void BiTreetoexp(BiTree*T,int deep)
{
	if(T==NULL)	return;
	else if(NULL==T->lchild&&NULL==T->rchild) 
		printf("%c",T->nodename);
	else{
		if(deep>1)		printf("(");			//若有子树 
		BiTreetoexp(T->lchild,deep+1);
		printf("%c",T->nodename);				//操作符 
		BiTreetoexp(T->rchild,deep+1);
		if(deep>1)		printf(")");			//有则合上括号 
	}	
} 


void Integral_BiTreetoexp(BiTree*T)
{
	BiTreetoexp(T,1);			//根的高度为1 
}
