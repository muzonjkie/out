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


				//	�����ĵݹ����������� 
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




void BiTreeRead(BiTree*T){               //�ݹ����������� 
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
	else if(NULL!=pre){					//��ֹ��©�ڵ����tagδ��ʼ��Ϊ0 
		pre->rtag=0;}
	pre=T;								//׷���ϴη��ʵĽڵ� 
	BiTreeRead(T->rchild);
}
}

void IntegralInorder(BiTree*T)
{			//���������ݹ��������� 
	BiTreeRead(T);
	pre->rchild=NULL;
	pre->rtag=1;	
}

void visit(BiTree*T){
	printf("%c",T->nodename);
}


void preorder(BiTree*T){					//����ݹ���� 
	if(T){
	visit(T);
	preorder(T->lchild);
	preorder(T->rchild);
	}
}


void inorder(BiTree*T){					//����ݹ���� 
	if(T){
	inorder(T->lchild);
	visit(T);
	inorder(T->rchild);
	}
}

void postorder(BiTree*T){					//����ݹ���� 
	if(T){
	postorder(T->lchild);
	postorder(T->rchild);
	visit(T);
	}
}


