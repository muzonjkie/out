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
T=BiTcreate(T);				//�����ڵ�λ�÷��ظ�T	
int ret=width(T);
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
			tmp++;					//�ۼƱ����ѳ��ӵ�Ԫ�ظ��� 
			if(T->lchild)
				queue[++rear]=T->lchild;
			if(T->rchild)
				queue[++rear]=T->rchild;
			if(front==last){		//���ӵ��������һ���ڵ� 
				last=rear;			//���±������һ���ڵ� 
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
T=BiTcreate(T);				//�����ڵ�λ�÷��ظ�T	
int ret=width(T);
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
			tmp++;					//�ۼƱ����ѳ��ӵ�Ԫ�ظ��� 
			if(T->lchild)
				queue[++rear]=T->lchild;
			if(T->rchild)
				queue[++rear]=T->rchild;
			if(front==last){		//���ӵ��������һ���ڵ� 
				last=rear;			//���±������һ���ڵ� 
				if(tmp>maxw)	maxw=tmp;
				tmp=0;
			}					
		}
		return maxw;
	}
}
>>>>>>> 7edc0a04ff39d0dd7f2435bd378bcebed8945e78
