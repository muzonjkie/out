<<<<<<< HEAD
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#define maxsize 20


typedef struct {
	int sqBiTNode[maxsize];
	int num;							//实际占用空间 
}sqBiTree; 


int predt=-32767;						//中序前驱 
int Judge_BST(sqBiTree T,int i);

int main()
{
	sqBiTree T={{40,50,60,-1,30,-1,-1,-1,-1,-1,35},11};
if(Judge_BST(T,0))
	printf("是");
	else printf("不是");
	return 0;
 } 
 
 
int Judge_BST(sqBiTree T,int i)
{
	int b1,b2;
	if(T.sqBiTNode[i]==-1)						//空节点 
		return 1;
	else{
		if(2*i+1<T.num)							//未越界 
			b1=Judge_BST(T,2*i+1);
		else b1=1;								//越界一律判断是二叉搜索树 
		if(0==b1||predt>=T.sqBiTNode[i])
			return 0;
			predt=T.sqBiTNode[i];
		if(2*i+2<T.num)
				b2=Judge_BST(T,2*i+2);
		else b2=1;
			return b2;	
		} 
}
=======
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#define maxsize 20


typedef struct {
	int sqBiTNode[maxsize];
	int num;							//实际占用空间 
}sqBiTree; 


int predt=-32767;						//中序前驱 
int Judge_BST(sqBiTree T,int i);

int main()
{
	sqBiTree T={{40,50,60,-1,30,-1,-1,-1,-1,-1,35},11};
if(Judge_BST(T,0))
	printf("是");
	else printf("不是");
	return 0;
 } 
 
 
int Judge_BST(sqBiTree T,int i)
{
	int b1,b2;
	if(T.sqBiTNode[i]==-1)						//空节点 
		return 1;
	else{
		if(2*i+1<T.num)							//未越界 
			b1=Judge_BST(T,2*i+1);
		else b1=1;								//越界一律判断是二叉搜索树 
		if(0==b1||predt>=T.sqBiTNode[i])
			return 0;
			predt=T.sqBiTNode[i];
		if(2*i+2<T.num)
				b2=Judge_BST(T,2*i+2);
		else b2=1;
			return b2;	
		} 
}
>>>>>>> 7edc0a04ff39d0dd7f2435bd378bcebed8945e78
