<<<<<<< HEAD
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#define maxsize 100

typedef struct BiTree{
	int  weight;
	struct BiTree *lchild,*rchild;
}BiTree; 



BiTree* BiTcreate(BiTree*T);
int WPL_levelorder(BiTree*T);

int main()
{
	BiTree *T=NULL;		
T=BiTcreate(T);				//将根节点位置返回给T	
int ret=WPL_levelorder(T);
printf("%d",ret);
return 0;
}



BiTree* BiTcreate(BiTree*T)			//层序生成树节点 
{
	int weight;
	BiTree*queue[maxsize];
	int front=0,rear=0;
	BiTree*p=T;									//p暂存T的值 
	while(printf("输入节点值\n"),scanf("%d",&weight)!=EOF){
		BiTree* pnew=(BiTree*)calloc(1,sizeof(BiTree));			//calloc会让此空间初始化为0 
		pnew->weight=weight;
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




int WPL_levelorder(BiTree*T)
{
	BiTree* queue[maxsize];
	int front=0,rear=0;	
	int wpl=0,deep=0;
	BiTree *lastnode,*newlastnode; 
	lastnode=T;
	queue[rear++]=T;
	while(rear!=front){
		T=queue[front++];
		if(NULL==T->lchild&&NULL==T->rchild)
			wpl+=deep*T->weight;		
		if(T->lchild){
			queue[rear++]=T->lchild;	
			newlastnode=T->lchild;
		}					
		if(T->rchild){
			queue[rear++]=T->rchild;	
			newlastnode=T->rchild;	
		}
		if(T==lastnode){			//若为本层最后一个节点，更新 
			lastnode=newlastnode;
			deep+=1;
		}
	}
	return wpl;
 } 
=======
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#define maxsize 100

typedef struct BiTree{
	int  weight;
	struct BiTree *lchild,*rchild;
}BiTree; 



BiTree* BiTcreate(BiTree*T);
int WPL_levelorder(BiTree*T);

int main()
{
	BiTree *T=NULL;		
T=BiTcreate(T);				//将根节点位置返回给T	
int ret=WPL_levelorder(T);
printf("%d",ret);
return 0;
}



BiTree* BiTcreate(BiTree*T)			//层序生成树节点 
{
	int weight;
	BiTree*queue[maxsize];
	int front=0,rear=0;
	BiTree*p=T;									//p暂存T的值 
	while(printf("输入节点值\n"),scanf("%d",&weight)!=EOF){
		BiTree* pnew=(BiTree*)calloc(1,sizeof(BiTree));			//calloc会让此空间初始化为0 
		pnew->weight=weight;
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




int WPL_levelorder(BiTree*T)
{
	BiTree* queue[maxsize];
	int front=0,rear=0;	
	int wpl=0,deep=0;
	BiTree *lastnode,*newlastnode; 
	lastnode=T;
	queue[rear++]=T;
	while(rear!=front){
		T=queue[front++];
		if(NULL==T->lchild&&NULL==T->rchild)
			wpl+=deep*T->weight;		
		if(T->lchild){
			queue[rear++]=T->lchild;	
			newlastnode=T->lchild;
		}					
		if(T->rchild){
			queue[rear++]=T->rchild;	
			newlastnode=T->rchild;	
		}
		if(T==lastnode){			//若为本层最后一个节点，更新 
			lastnode=newlastnode;
			deep+=1;
		}
	}
	return wpl;
 } 
>>>>>>> 7edc0a04ff39d0dd7f2435bd378bcebed8945e78
