<<<<<<< HEAD
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

typedef struct BiTree{
	int value;
	struct BiTree *lchild,*rchild;
}BiTree; 

int predt=-32767;

BiTree* BST_Insert(BiTree*T, int a[],int n);
BiTree* BST_Srarch(BiTree*T,int x);
void Judge_AVL(BiTree*T,int*balance,int*h);
int Judge_BST(BiTree*T);


int main()
{
	BiTree*T=NULL;
	int a[10]={357,258,99,985,211,996,007,263,258};	
	T=BST_Insert(T,a,10);
	BiTree*search=NULL;	
if(search=BST_Srarch(T,985))	printf("�ҵ���λ����%p,ֵΪ%d\n",search,search->value); 		//���� 

int balance=0,h=0;

Judge_AVL(T,&balance,&h);
if(balance)	printf("����Ϊƽ�������\n");
else printf("��������ƽ�������\n");
if(!h)	printf("����Ϊ����\n");

if(Judge_BST(T))	printf("����Ϊ����������\n");
else printf("�������Ƕ���������\n");
return 0;	
} 



BiTree* BST_Insert(BiTree*T,int a[],int n)
{
	int i;
if(NULL==T){
	T=(BiTree*)malloc(sizeof(BiTree));
	T->value=a[0];									//��һ��Ԫ����Ϊ���ڵ� 
	T->lchild=T->rchild=NULL;	}
	BiTree* p=T,*s=NULL,*q=NULL; 
for(i=0;i<n;i++){
	s=(BiTree*)malloc(sizeof(BiTree));
	s->lchild=s->rchild=NULL;
	s->value=a[i];	
while(p!=NULL)
{
if(a[i]==p->value){		//;������������ȵ�Ԫ������ʧ�ܣ�ֱ���߼������֮ǰ����Ŀռ� 
	printf("������ȵ�ֵ��\n"); 
	free(s);
goto keep; 	}											//goto����� 
	q=p;													//����һ��������Ѱ�������λ�� 
if(s->value<p->value)	p=p->lchild;		//С���� 
else  p=p->rchild;							//������ 	
}					//���Ѿ��ҵ�������λ�õĸ��ڵ� 
if(s->value<q->value)	q->lchild=s; 
else 	q->rchild=s;
  	keep:
	p=T;					//���´Ӹ��ڵ���� 
}
return T; 				//ֻ��ȫ�������ɹ��������ڵ�ŷ��� 
} 
 
 
 
BiTree* BST_Srarch(BiTree*T,int x)
{
while(T&&x!=T->value){						//�ǿ�������ڴ˽ڵ�ֵ����ѭ�� 
	if(x<T->value) T=T->lchild;
	else T=T->rchild;
	}
return T;
}


int Judge_BST(BiTree*T)
{
	int b1,b2;					//Ϊ1���Ƕ��������� 
if(T==NULL){
	return 1;	}
else{
	b1=Judge_BST(T->lchild);		//�ж��������ǲ��� 
	if(b1==0||predt>=T->value)		//��������ǰ�����ڵ��ڵ�ǰ�ڵ����� 
	return 0;
	predt=T->value;					//��������ǰ���ڵ��ֵ��Ӧ�ȵ�ǰС�� 
	b2=Judge_BST(T->rchild);
	return b2;
	}
}




void Judge_AVL(BiTree*T,int*balance,int*h)			//����ַ��������� 
{
	int bl=0,br=0,hl=0,hr=0;						//����������ƽ��Ǻţ�Ϊ1��ƽ�⣬�߶� 
if(NULL==T){										//��Ϊ���� 
		*h=0;
		*balance=1;		}							//�����Ҳ��ƽ��� 
else if(NULL==T->lchild&&NULL==T->rchild){			//���Һ��Ӿ�Ϊ�գ�����1����ƽ��� 
		*h=1;
		*balance=1;			}
else{
	Judge_AVL(T->lchild,&bl,&hl);					//�ݹ��ж������������Ƿ�ƽ�� 
	Judge_AVL(T->rchild,&br,&hr);
	*h=(hl>hr?hl:hr)+1;								//���ϸ��ڵ�ĸ߶� 
	if(abs(hl-hr)<2)	*balance=bl&&br;	//���������߲����ֵС��2�����ж����������Ƿ�ƽ�� 
	else	*balance=0;		}
}







=======
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

typedef struct BiTree{
	int value;
	struct BiTree *lchild,*rchild;
}BiTree; 

int predt=-32767;

BiTree* BST_Insert(BiTree*T, int a[],int n);
BiTree* BST_Srarch(BiTree*T,int x);
void Judge_AVL(BiTree*T,int*balance,int*h);
int Judge_BST(BiTree*T);


int main()
{
	BiTree*T=NULL;
	int a[10]={357,258,99,985,211,996,007,263,258};	
	T=BST_Insert(T,a,10);
	BiTree*search=NULL;	
if(search=BST_Srarch(T,985))	printf("�ҵ���λ����%p,ֵΪ%d\n",search,search->value); 		//���� 

int balance=0,h=0;

Judge_AVL(T,&balance,&h);
if(balance)	printf("����Ϊƽ�������\n");
else printf("��������ƽ�������\n");
if(!h)	printf("����Ϊ����\n");

if(Judge_BST(T))	printf("����Ϊ����������\n");
else printf("�������Ƕ���������\n");
return 0;	
} 



BiTree* BST_Insert(BiTree*T,int a[],int n)
{
	int i;
if(NULL==T){
	T=(BiTree*)malloc(sizeof(BiTree));
	T->value=a[0];									//��һ��Ԫ����Ϊ���ڵ� 
	T->lchild=T->rchild=NULL;	}
	BiTree* p=T,*s=NULL,*q=NULL; 
for(i=0;i<n;i++){
	s=(BiTree*)malloc(sizeof(BiTree));
	s->lchild=s->rchild=NULL;
	s->value=a[i];	
while(p!=NULL)
{
if(a[i]==p->value){		//;������������ȵ�Ԫ������ʧ�ܣ�ֱ���߼������֮ǰ����Ŀռ� 
	printf("������ȵ�ֵ��\n"); 
	free(s);
goto keep; 	}											//goto����� 
	q=p;													//����һ��������Ѱ�������λ�� 
if(s->value<p->value)	p=p->lchild;		//С���� 
else  p=p->rchild;							//������ 	
}					//���Ѿ��ҵ�������λ�õĸ��ڵ� 
if(s->value<q->value)	q->lchild=s; 
else 	q->rchild=s;
  	keep:
	p=T;					//���´Ӹ��ڵ���� 
}
return T; 				//ֻ��ȫ�������ɹ��������ڵ�ŷ��� 
} 
 
 
 
BiTree* BST_Srarch(BiTree*T,int x)
{
while(T&&x!=T->value){						//�ǿ�������ڴ˽ڵ�ֵ����ѭ�� 
	if(x<T->value) T=T->lchild;
	else T=T->rchild;
	}
return T;
}


int Judge_BST(BiTree*T)
{
	int b1,b2;					//Ϊ1���Ƕ��������� 
if(T==NULL){
	return 1;	}
else{
	b1=Judge_BST(T->lchild);		//�ж��������ǲ��� 
	if(b1==0||predt>=T->value)		//��������ǰ�����ڵ��ڵ�ǰ�ڵ����� 
	return 0;
	predt=T->value;					//��������ǰ���ڵ��ֵ��Ӧ�ȵ�ǰС�� 
	b2=Judge_BST(T->rchild);
	return b2;
	}
}




void Judge_AVL(BiTree*T,int*balance,int*h)			//����ַ��������� 
{
	int bl=0,br=0,hl=0,hr=0;						//����������ƽ��Ǻţ�Ϊ1��ƽ�⣬�߶� 
if(NULL==T){										//��Ϊ���� 
		*h=0;
		*balance=1;		}							//�����Ҳ��ƽ��� 
else if(NULL==T->lchild&&NULL==T->rchild){			//���Һ��Ӿ�Ϊ�գ�����1����ƽ��� 
		*h=1;
		*balance=1;			}
else{
	Judge_AVL(T->lchild,&bl,&hl);					//�ݹ��ж������������Ƿ�ƽ�� 
	Judge_AVL(T->rchild,&br,&hr);
	*h=(hl>hr?hl:hr)+1;								//���ϸ��ڵ�ĸ߶� 
	if(abs(hl-hr)<2)	*balance=bl&&br;	//���������߲����ֵС��2�����ж����������Ƿ�ƽ�� 
	else	*balance=0;		}
}







>>>>>>> 7edc0a04ff39d0dd7f2435bd378bcebed8945e78
