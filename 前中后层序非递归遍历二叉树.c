#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#define maxsize 100

typedef struct BiTree{
	char nodename;
	struct BiTree *lchild,*rchild;
	int ltag,rtag;
}BiTree; 


int cnt=0;

BiTree* BiTcreat(BiTree*T);
BiTree* BiTcreate(BiTree*T);
void PreOrder(BiTree*T);
void InOrder(BiTree*T);
void PostOrder(BiTree*T);
void Levelorder(BiTree*T);

int main()
{
	BiTree *T=NULL;		
if(T=BiTcreate(T)){				//将根节点位置返回给T	
	//system("pause");
	PreOrder(T);
	printf("\n");	
	InOrder(T);
	printf("\n");
	PostOrder(T);
	printf("\n");
	Levelorder(T);		
}
else printf("树空！\n");
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





 


void PreOrder(BiTree*T)					//先序遍历 
{

	BiTree* stack[maxsize];
	int top=-1; 
	printf("先序遍历次序：");
while(NULL!=T||-1!=top){			
if(NULL!=T){		
		stack[++top]=T;
		printf("%c",T->nodename);
		T=T->lchild;}
else{
	T=stack[top--];	
	T=T->rchild; 	}
}
}


void InOrder(BiTree*T)							//中序遍历 
{
	BiTree* stack[maxsize];
	int top=-1; 
	printf("中序遍历次序："); 
while(NULL!=T||-1!=top){			
if(NULL!=T){		
		stack[++top]=T;
		T=T->lchild;	}
else{
	T=stack[top--];	
	printf("%c",T->nodename);
	T=T->rchild; 	}
}
}



void PostOrder(BiTree*T)					//后序遍历	
{
	BiTree* stack[maxsize],*r=NULL;
	int top=-1; 
	printf("后序遍历次序：");
while(NULL!=T||-1!=top){			
if(NULL!=T){		
	stack[++top]=T;
	T=T->lchild;	}
else{
  	T=stack[top];	
  if(T->rchild&&T->rchild!=r)						//r指针跟踪上次T指针访问的节点 
	T=T->rchild;								
  else{										//如果右孩子存在且已经访问过，那么说明可以出栈这个节点了 
	T=stack[top--];	
	printf("%c",T->nodename); 	
	r=T;									//出栈后r跟踪出栈节点
	T=NULL;  } 								//出栈后让T为NULL，看看此节点是不是其父节点的右孩子 
}
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

