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

BiTree* BiTcreat(BiTree*T)			//�ݹ��������ڵ� 
{					
	char nodename;
	printf("������ڵ��ֵnodename\n");
	scanf("%c",&nodename);
if('/'!=nodename){									
	T=(BiTree*)malloc(sizeof(BiTree));
	T->nodename=nodename;
	cnt++;
	T->lchild=NULL;
	T->rchild=NULL;
	printf("�˽ڵ�Ϊ����\n");
	fflush(stdin);							 			//��ջ��������ϴ����������Ļس��� 
	T->lchild=BiTcreat(T->lchild);						//�ȴӸ��ڵ�����һ·������֮�� 
	printf("�˽ڵ�Ϊ�Һ���\n");
	fflush(stdin);
	T->rchild=BiTcreat(T->rchild);						//�ٴӸ��ڵ����Ҵ��� 
} 
	return T;											//���ؽڵ�λ����Ϣ 
}



//--------------����Ҫ����------------ 
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



void BiTreeRead(BiTree*T)
{           				// ���Ѱ� 
	BiTree* stack[maxsize]; 
	int top=-1;	
	while(T||-1!=top){
		if(T){	
			stack[++top]=T;									//��Ϊ�գ�����ջ 
			T=T->lchild;	}
		else {
			T=stack[top--];									//�գ���ջ 
			if(NULL==T->lchild){		
			T->lchild=pre;							//����������һ������ʱpreΪNULL��û���� 
			T->ltag=1;		}						//֮���û����  
			else T->ltag=0;
			if(pre&&NULL==pre->rchild){			//preʼ����һ�� 
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



