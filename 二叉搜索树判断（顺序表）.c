<<<<<<< HEAD
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#define maxsize 20


typedef struct {
	int sqBiTNode[maxsize];
	int num;							//ʵ��ռ�ÿռ� 
}sqBiTree; 


int predt=-32767;						//����ǰ�� 
int Judge_BST(sqBiTree T,int i);

int main()
{
	sqBiTree T={{40,50,60,-1,30,-1,-1,-1,-1,-1,35},11};
if(Judge_BST(T,0))
	printf("��");
	else printf("����");
	return 0;
 } 
 
 
int Judge_BST(sqBiTree T,int i)
{
	int b1,b2;
	if(T.sqBiTNode[i]==-1)						//�սڵ� 
		return 1;
	else{
		if(2*i+1<T.num)							//δԽ�� 
			b1=Judge_BST(T,2*i+1);
		else b1=1;								//Խ��һ���ж��Ƕ��������� 
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
	int num;							//ʵ��ռ�ÿռ� 
}sqBiTree; 


int predt=-32767;						//����ǰ�� 
int Judge_BST(sqBiTree T,int i);

int main()
{
	sqBiTree T={{40,50,60,-1,30,-1,-1,-1,-1,-1,35},11};
if(Judge_BST(T,0))
	printf("��");
	else printf("����");
	return 0;
 } 
 
 
int Judge_BST(sqBiTree T,int i)
{
	int b1,b2;
	if(T.sqBiTNode[i]==-1)						//�սڵ� 
		return 1;
	else{
		if(2*i+1<T.num)							//δԽ�� 
			b1=Judge_BST(T,2*i+1);
		else b1=1;								//Խ��һ���ж��Ƕ��������� 
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
