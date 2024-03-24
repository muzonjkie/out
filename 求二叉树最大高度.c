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
T=BiTcreate(T);				//�����ڵ�λ�÷��ظ�T	
int ret=Bidepth_2(T);
printf("%d",ret);
return 0;
}



BiTree* BiTcreate(BiTree*T)			//�����������ڵ� 
{
	char nodename;
	BiTree*queue[maxsize];
	int front=0,rear=0;
	BiTree*p=T;									//p�ݴ�T��ֵ 
	while(printf("����ڵ���\n"),scanf("%c",&nodename)!=EOF){
		BiTree* pnew=(BiTree*)calloc(1,sizeof(BiTree));			//calloc���ô˿ռ��ʼ��Ϊ0 
		pnew->nodename=nodename;
		if(NULL==T)	{					//�����ڵ�Ϊ�� 
			T=pnew;
			p=T;	}					//p�ݴ�T��ֵ 
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
			if(front==last){		//���ӵ��������һ���ڵ� 
				level++;
				last=rear;			//���±������һ���ڵ� 
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
T=BiTcreate(T);				//�����ڵ�λ�÷��ظ�T	
int ret=Bidepth_2(T);
printf("%d",ret);
return 0;
}



BiTree* BiTcreate(BiTree*T)			//�����������ڵ� 
{
	char nodename;
	BiTree*queue[maxsize];
	int front=0,rear=0;
	BiTree*p=T;									//p�ݴ�T��ֵ 
	while(printf("����ڵ���\n"),scanf("%c",&nodename)!=EOF){
		BiTree* pnew=(BiTree*)calloc(1,sizeof(BiTree));			//calloc���ô˿ռ��ʼ��Ϊ0 
		pnew->nodename=nodename;
		if(NULL==T)	{					//�����ڵ�Ϊ�� 
			T=pnew;
			p=T;	}					//p�ݴ�T��ֵ 
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
			if(front==last){		//���ӵ��������һ���ڵ� 
				level++;
				last=rear;			//���±������һ���ڵ� 
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
