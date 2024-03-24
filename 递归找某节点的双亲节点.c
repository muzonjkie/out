#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#define maxsize 100

typedef struct BiTree{
	char  nodename;
	struct BiTree *lchild,*rchild;
}BiTree; 



BiTree* BiTcreate(BiTree*T);
void FindParent(BiTree*T,int x,BiTree**p); 


int main()
{
	char x;
	BiTree *T=NULL,*p=NULL;		
T=BiTcreate(T);				//将根节点位置返回给T
//fflush(stdin);
printf("输入查找的节点\n");
scanf("%c",&x);
FindParent(T,x,&p);
if(p)
	printf("其双亲节点为%c",p->nodename);
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




void FindParent(BiTree*T,int x,BiTree**p)
{
	if(T){
		if(x==T->nodename)		*p=NULL;
		else if(T->lchild&&x==T->lchild->nodename)
			*p=T;
		else if(T->rchild&&x==T->rchild->nodename)
			*p=T;
		else{
			FindParent(T->lchild,x,p);			//p已是地址的地址 
			if(*p==NULL)
			FindParent(T->rchild,x,p);
		}
	}
	else *p=NULL;	
 } 
