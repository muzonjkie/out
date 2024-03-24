<<<<<<< HEAD
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#define maxsize 100

typedef struct BiTree{
	char nodename;
	struct BiTree *lchild,*rchild;
	int ltag,rtag;
}BiTree; 


BiTree* BiTcreate(BiTree*T);
int width(BiTree*T);



int main()
{
	BiTree *T=NULL;		
T=BiTcreate(T);				//将根节点位置返回给T	
int ret=width(T);
printf("%d",ret);
return 0;
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







int width(BiTree*T)
{
	if(NULL==T)    return 0;
	else{
		BiTree*queue[maxsize];
		int front=-1,rear=-1;
		int last=0,tmp=0,maxw=0;
		queue[++rear]=T;
		while(front<rear){
			T=queue[++front];
			tmp++;					//累计本层已出队的元素个数 
			if(T->lchild)
				queue[++rear]=T->lchild;
			if(T->rchild)
				queue[++rear]=T->rchild;
			if(front==last){		//出队到本层最后一个节点 
				last=rear;			//更新本层最后一个节点 
				if(tmp>maxw)	maxw=tmp;
				tmp=0;
			}					
		}
		return maxw;
	}
}
=======
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#define maxsize 100

typedef struct BiTree{
	char nodename;
	struct BiTree *lchild,*rchild;
	int ltag,rtag;
}BiTree; 


BiTree* BiTcreate(BiTree*T);
int width(BiTree*T);



int main()
{
	BiTree *T=NULL;		
T=BiTcreate(T);				//将根节点位置返回给T	
int ret=width(T);
printf("%d",ret);
return 0;
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







int width(BiTree*T)
{
	if(NULL==T)    return 0;
	else{
		BiTree*queue[maxsize];
		int front=-1,rear=-1;
		int last=0,tmp=0,maxw=0;
		queue[++rear]=T;
		while(front<rear){
			T=queue[++front];
			tmp++;					//累计本层已出队的元素个数 
			if(T->lchild)
				queue[++rear]=T->lchild;
			if(T->rchild)
				queue[++rear]=T->rchild;
			if(front==last){		//出队到本层最后一个节点 
				last=rear;			//更新本层最后一个节点 
				if(tmp>maxw)	maxw=tmp;
				tmp=0;
			}					
		}
		return maxw;
	}
}
>>>>>>> 7edc0a04ff39d0dd7f2435bd378bcebed8945e78
