#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#define maxsize 100

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


typedef struct{
	BiTree* data[maxsize];
	int top;
}stack;
			
BiTree* BiTcreat(BiTree*T);	
BiTree* BiTcreate(BiTree*T);
void BiTreeRead(BiTree*T);

 
int main()
{
	BiTree *T=NULL;	
	T=BiTcreate(T);
	BiTreeRead(T);
	printf("\n"); 
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



//--------------鼠鼠要晕了------------ 
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



void BiTreeRead(BiTree*T)
{           				// 好难啊 
	BiTree* stack[maxsize]; 
	int top=-1;	
	while(T||-1!=top){
		if(T){	
			stack[++top]=T;									//不为空，则入栈 
			T=T->lchild;	}
		else {
			T=stack[top--];									//空，出栈 
			if(NULL==T->lchild){		
			T->lchild=pre;							//如果是中序第一个，此时pre为NULL，没问题 
			T->ltag=1;		}						//之后的没问题  
			else T->ltag=0;
			if(pre&&NULL==pre->rchild){			//pre始终慢一步 
	 		pre->rchild=T;
			T->rtag=1;		}
			else if(pre)	pre->rtag=0;
		pre=T;
		T=T->rchild;	
}
}
pre->rchild=NULL;
pre->rtag=1;
}



