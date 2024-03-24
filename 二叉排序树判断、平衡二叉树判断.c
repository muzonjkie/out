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
if(search=BST_Srarch(T,985))	printf("找到的位置是%p,值为%d\n",search,search->value); 		//测试 

int balance=0,h=0;

Judge_AVL(T,&balance,&h);
if(balance)	printf("此树为平衡二叉树\n");
else printf("此树不是平衡二叉树\n");
if(!h)	printf("此树为空树\n");

if(Judge_BST(T))	printf("此树为二叉排序树\n");
else printf("此树不是二叉排序树\n");
return 0;	
} 



BiTree* BST_Insert(BiTree*T,int a[],int n)
{
	int i;
if(NULL==T){
	T=(BiTree*)malloc(sizeof(BiTree));
	T->value=a[0];									//第一个元素作为根节点 
	T->lchild=T->rchild=NULL;	}
	BiTree* p=T,*s=NULL,*q=NULL; 
for(i=0;i<n;i++){
	s=(BiTree*)malloc(sizeof(BiTree));
	s->lchild=s->rchild=NULL;
	s->value=a[i];	
while(p!=NULL)
{
if(a[i]==p->value){		//途中若发现有相等的元素则建树失败，直接逻辑上清除之前申请的空间 
	printf("存在相等的值！\n"); 
	free(s);
goto keep; 	}											//goto真好用 
	q=p;													//任有一个成立则寻找其插入位置 
if(s->value<p->value)	p=p->lchild;		//小往左 
else  p=p->rchild;							//大往右 	
}					//则已经找到待插入位置的父节点 
if(s->value<q->value)	q->lchild=s; 
else 	q->rchild=s;
  	keep:
	p=T;					//重新从根节点出发 
}
return T; 				//只有全部建立成功此树根节点才返回 
} 
 
 
 
BiTree* BST_Srarch(BiTree*T,int x)
{
while(T&&x!=T->value){						//非空树或等于此节点值跳出循环 
	if(x<T->value) T=T->lchild;
	else T=T->rchild;
	}
return T;
}


int Judge_BST(BiTree*T)
{
	int b1,b2;					//为1则是二叉排序树 
if(T==NULL){
	return 1;	}
else{
	b1=Judge_BST(T->lchild);		//判断左子树是不是 
	if(b1==0||predt>=T->value)		//左子树的前驱大于等于当前节点则不是 
	return 0;
	predt=T->value;					//保存中序前驱节点的值（应比当前小） 
	b2=Judge_BST(T->rchild);
	return b2;
	}
}




void Judge_AVL(BiTree*T,int*balance,int*h)			//传地址，方便输出 
{
	int bl=0,br=0,hl=0,hr=0;						//左右子树的平衡记号，为1则平衡，高度 
if(NULL==T){										//则为空树 
		*h=0;
		*balance=1;		}							//设空树也是平衡的 
else if(NULL==T->lchild&&NULL==T->rchild){			//左右孩子均为空，树高1，是平衡的 
		*h=1;
		*balance=1;			}
else{
	Judge_AVL(T->lchild,&bl,&hl);					//递归判断其左右子树是否平衡 
	Judge_AVL(T->rchild,&br,&hr);
	*h=(hl>hr?hl:hr)+1;								//加上根节点的高度 
	if(abs(hl-hr)<2)	*balance=bl&&br;	//左右子树高差绝对值小于2，再判断左右子树是否都平衡 
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
if(search=BST_Srarch(T,985))	printf("找到的位置是%p,值为%d\n",search,search->value); 		//测试 

int balance=0,h=0;

Judge_AVL(T,&balance,&h);
if(balance)	printf("此树为平衡二叉树\n");
else printf("此树不是平衡二叉树\n");
if(!h)	printf("此树为空树\n");

if(Judge_BST(T))	printf("此树为二叉排序树\n");
else printf("此树不是二叉排序树\n");
return 0;	
} 



BiTree* BST_Insert(BiTree*T,int a[],int n)
{
	int i;
if(NULL==T){
	T=(BiTree*)malloc(sizeof(BiTree));
	T->value=a[0];									//第一个元素作为根节点 
	T->lchild=T->rchild=NULL;	}
	BiTree* p=T,*s=NULL,*q=NULL; 
for(i=0;i<n;i++){
	s=(BiTree*)malloc(sizeof(BiTree));
	s->lchild=s->rchild=NULL;
	s->value=a[i];	
while(p!=NULL)
{
if(a[i]==p->value){		//途中若发现有相等的元素则建树失败，直接逻辑上清除之前申请的空间 
	printf("存在相等的值！\n"); 
	free(s);
goto keep; 	}											//goto真好用 
	q=p;													//任有一个成立则寻找其插入位置 
if(s->value<p->value)	p=p->lchild;		//小往左 
else  p=p->rchild;							//大往右 	
}					//则已经找到待插入位置的父节点 
if(s->value<q->value)	q->lchild=s; 
else 	q->rchild=s;
  	keep:
	p=T;					//重新从根节点出发 
}
return T; 				//只有全部建立成功此树根节点才返回 
} 
 
 
 
BiTree* BST_Srarch(BiTree*T,int x)
{
while(T&&x!=T->value){						//非空树或等于此节点值跳出循环 
	if(x<T->value) T=T->lchild;
	else T=T->rchild;
	}
return T;
}


int Judge_BST(BiTree*T)
{
	int b1,b2;					//为1则是二叉排序树 
if(T==NULL){
	return 1;	}
else{
	b1=Judge_BST(T->lchild);		//判断左子树是不是 
	if(b1==0||predt>=T->value)		//左子树的前驱大于等于当前节点则不是 
	return 0;
	predt=T->value;					//保存中序前驱节点的值（应比当前小） 
	b2=Judge_BST(T->rchild);
	return b2;
	}
}




void Judge_AVL(BiTree*T,int*balance,int*h)			//传地址，方便输出 
{
	int bl=0,br=0,hl=0,hr=0;						//左右子树的平衡记号，为1则平衡，高度 
if(NULL==T){										//则为空树 
		*h=0;
		*balance=1;		}							//设空树也是平衡的 
else if(NULL==T->lchild&&NULL==T->rchild){			//左右孩子均为空，树高1，是平衡的 
		*h=1;
		*balance=1;			}
else{
	Judge_AVL(T->lchild,&bl,&hl);					//递归判断其左右子树是否平衡 
	Judge_AVL(T->rchild,&br,&hr);
	*h=(hl>hr?hl:hr)+1;								//加上根节点的高度 
	if(abs(hl-hr)<2)	*balance=bl&&br;	//左右子树高差绝对值小于2，再判断左右子树是否都平衡 
	else	*balance=0;		}
}







>>>>>>> 7edc0a04ff39d0dd7f2435bd378bcebed8945e78
