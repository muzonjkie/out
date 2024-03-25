#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#define maxsize 100

typedef struct BiTree{
	char nodename;
	struct BiTree *lchild,*rchild;
	int ltag,rtag;
}BiTree,*PBiTree;

int cnt=0;
BiTree* pre=NULL;


				//	完整的递归中序线索化 
BiTree* BiTcreat(BiTree*T);	
BiTree* BiTcreate(BiTree*T);
void BiTreeRead(BiTree*T);
void IntegralInorder(BiTree*T);
void preorder(BiTree*T);
void inorder(BiTree*T);
void postorder(BiTree*T);
void visit(BiTree*T);



 
int main()
{
	BiTree *T=NULL;	
	T=BiTcreate(T);
	preorder(T);
	printf("\n");
	inorder(T);
	printf("\n"); 
	postorder(T);
	printf("\n"); 
	IntegralInorder(T);
	
return 0;
}

BiTree* BiTcreat(BiTree*T)			//递归生成树节点 
{					
	char nodename;
	printf("请输入节点的值nodename\n");
	scanf("%c",&nodename);
if('/'!=nodename){									
	T=(BiTree*)malloc(sizeof(BiTree));
	T->nodename=nodename;
	cnt++;
	T->lchild=NULL;
	T->rchild=NULL;
	printf("此节点为左孩子\n");
	fflush(stdin);							 			//清空缓冲区，上次输入遗留的回车符 
	T->lchild=BiTcreat(T->lchild);						//先从根节点往左一路创建完之后 
	printf("此节点为右孩子\n");
	fflush(stdin);
	T->rchild=BiTcreat(T->rchild);						//再从根节点往右创建 
} 
	return T;											//返回节点位置信息 
}



BiTree* BiTcreate(BiTree*T)			//层序生成树节点 
{
	char nodename;
	BiTree*queue[maxsize];
	int front=0,rear=0;
	BiTree*p=T;									//p暂存T的值 
	while(printf("输入节点编号\n"),scanf("%c",&nodename)!=EOF){
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




void BiTreeRead(BiTree*T){               //递归中序线索化 
if(T){
	BiTreeRead(T->lchild);
	if(NULL==T->lchild){
		T->lchild=pre;	
		T->ltag=1;	}
	else{
		T->ltag=0;}
	if(NULL!=pre&&NULL==pre->rchild){
		pre->rchild=T;	
		pre->rtag=1;	}
	else if(NULL!=pre){					//防止遗漏节点的右tag未初始化为0 
		pre->rtag=0;}
	pre=T;								//追踪上次访问的节点 
	BiTreeRead(T->rchild);
}
}

void IntegralInorder(BiTree*T)
{			//补充完整递归中序线索 
	BiTreeRead(T);
	pre->rchild=NULL;
	pre->rtag=1;	
}

void visit(BiTree*T){
	printf("%c",T->nodename);
}


void preorder(BiTree*T){					//先序递归遍历 
	if(T){
	visit(T);
	preorder(T->lchild);
	preorder(T->rchild);
	}
}


void inorder(BiTree*T){					//中序递归遍历 
	if(T){
	inorder(T->lchild);
	visit(T);
	inorder(T->rchild);
	}
}

void postorder(BiTree*T){					//中序递归遍历 
	if(T){
	postorder(T->lchild);
	postorder(T->rchild);
	visit(T);
	}
}


