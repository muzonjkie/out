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
if(T=BiTcreate(T)){				//�����ڵ�λ�÷��ظ�T	
	//system("pause");
	PreOrder(T);
	printf("\n");	
	InOrder(T);
	printf("\n");
	PostOrder(T);
	printf("\n");
	Levelorder(T);		
}
else printf("���գ�\n");
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





 


void PreOrder(BiTree*T)					//������� 
{

	BiTree* stack[maxsize];
	int top=-1; 
	printf("�����������");
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


void InOrder(BiTree*T)							//������� 
{
	BiTree* stack[maxsize];
	int top=-1; 
	printf("�����������"); 
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



void PostOrder(BiTree*T)					//�������	
{
	BiTree* stack[maxsize],*r=NULL;
	int top=-1; 
	printf("�����������");
while(NULL!=T||-1!=top){			
if(NULL!=T){		
	stack[++top]=T;
	T=T->lchild;	}
else{
  	T=stack[top];	
  if(T->rchild&&T->rchild!=r)						//rָ������ϴ�Tָ����ʵĽڵ� 
	T=T->rchild;								
  else{										//����Һ��Ӵ������Ѿ����ʹ�����ô˵�����Գ�ջ����ڵ��� 
	T=stack[top--];	
	printf("%c",T->nodename); 	
	r=T;									//��ջ��r���ٳ�ջ�ڵ�
	T=NULL;  } 								//��ջ����TΪNULL�������˽ڵ��ǲ����丸�ڵ���Һ��� 
}
}
}




void Levelorder(BiTree*T)
{
	BiTree*queue[maxsize];
	int front=0,rear=0;	
	queue[rear]=T;
	rear=(rear+1)%maxsize;
	printf("�����������");
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

