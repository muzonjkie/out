<<<<<<< HEAD
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#define maxsize 100

typedef struct BiTree{
	char nodename;
	struct BiTree *lchild,*rchild;
}BiTree; 


BiTree* BiTcreate(BiTree*T);
int Bidepth_1(BiTree*T);
int Bidepth_2(BiTree*T);



int main()
{
	BiTree *T=NULL;		
T=BiTcreate(T);				//将根节点位置返回给T	
int ret=Bidepth_2(T);
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





int Bidepth_1(BiTree*T)
{
	if(NULL==T)    return 0;
	else{
		BiTree*queue[maxsize];
		int front=-1,rear=-1;
		int last=0,level=0;
		queue[++rear]=T;
		while(front<rear){
			T=queue[++front];
			if(T->lchild)
				queue[++rear]=T->lchild;
			if(T->rchild)
				queue[++rear]=T->rchild;
			if(front==last){		//出队到本层最后一个节点 
				level++;
				last=rear;			//更新本层最后一个节点 
			}					
		}
		return level;
	}
 } 



int Bidepth_2(BiTree*T)
{
	if(NULL==T)    return 0;
	int ldep,rdep;
	ldep=Bidepth_2(T->lchild);
	rdep=Bidepth_2(T->rchild);
	return (ldep>rdep?ldep:rdep)+1;
}






=======
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#define maxsize 100

typedef struct BiTree{
	char nodename;
	struct BiTree *lchild,*rchild;
}BiTree; 


BiTree* BiTcreate(BiTree*T);
int Bidepth_1(BiTree*T);
int Bidepth_2(BiTree*T);



int main()
{
	BiTree *T=NULL;		
T=BiTcreate(T);				//将根节点位置返回给T	
int ret=Bidepth_2(T);
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





int Bidepth_1(BiTree*T)
{
	if(NULL==T)    return 0;
	else{
		BiTree*queue[maxsize];
		int front=-1,rear=-1;
		int last=0,level=0;
		queue[++rear]=T;
		while(front<rear){
			T=queue[++front];
			if(T->lchild)
				queue[++rear]=T->lchild;
			if(T->rchild)
				queue[++rear]=T->rchild;
			if(front==last){		//出队到本层最后一个节点 
				level++;
				last=rear;			//更新本层最后一个节点 
			}					
		}
		return level;
	}
 } 



int Bidepth_2(BiTree*T)
{
	if(NULL==T)    return 0;
	int ldep,rdep;
	ldep=Bidepth_2(T->lchild);
	rdep=Bidepth_2(T->rchild);
	return (ldep>rdep?ldep:rdep)+1;
}






>>>>>>> 7edc0a04ff39d0dd7f2435bd378bcebed8945e78
