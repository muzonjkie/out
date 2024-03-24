#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#define maxsize 100

typedef struct BiTree{
	int  value;
	struct BiTree *lchild,*rchild;
}BiTree; 



BiTree* BiTcreate(BiTree*T);
int LeafNode(BiTree*T);

int main()
{
	BiTree *T=NULL;		
T=BiTcreate(T);				//将根节点位置返回给T	
int ret=LeafNode(T);
printf("%d",ret);
return 0;
}



BiTree* BiTcreate(BiTree*T)			//层序生成树节点 
{
	int value;
	BiTree*queue[maxsize];
	int front=0,rear=0;
	BiTree*p=T;									//p暂存T的值 
	while(printf("输入节点值\n"),scanf("%d",&value)!=EOF){
		BiTree* pnew=(BiTree*)calloc(1,sizeof(BiTree));			//calloc会让此空间初始化为0 
		pnew->value=value;
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
	}
	return p;	
}




int LeafNode(BiTree*T)
{
	int num1,num2;
	if(NULL==T)	
		return 0;
	else if(NULL==T->lchild&&NULL==T->rchild)
		return 1;
	else{
		num1=LeafNode(T->lchild);
		num2=LeafNode(T->rchild);
		return num1+num2;
	}
 } 
