#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#define maxsize 10
#include <time.h>


void BuildMaxHeap(int list[],int n);
void HeapAdjust(int list[],int k,int n);
void Heapsort(int list[],int n);
void swap(int *a,int *b);


int main()
{
	int list[maxsize]={21,41,77,25,26,39,11,14,6,6};
	int i;	
Heapsort(list,maxsize);	
for(i=0;i<maxsize;i++){
	printf("表数据第%d位置数据%d\n",i,list[i]);
}		
	return 0;
}




void BuildMaxHeap(int list[],int n)
{
	int i;
	for(i=n/2;i>0;--i)			//从最后一个父节点开始,list从一开始存储 
		HeapAdjust(list,i,n);
}


void HeapAdjust(int list[],int k,int n)
{								//将以k为根的子树调整为堆 
	int i;
	list[0]=list[k];
	for(i=2*k;i<=n;i*=2){
		if(i<n&&list[i]<list[i+1])	i++;
		if(list[0]>=list[i])		break;		//如果根已经比左右子树都大了 
		else{
			list[k]=list[i];	
			k=i;						//以最大子树为根往下找原根应在的位置 
		}
	}
	list[k]=list[0];
}



void Heapsort(int list[],int n)
{
	int i;
	BuildMaxHeap(list,n);
	for(i=n;i>1;--i){
		swap(&list[i],&list[1]);		//将最大的放到最后面 
		HeapAdjust(list,1,i-1);			//除最后一个元素外，再调整成大根堆 
	}
}


void swap(int *a,int *b)
{
	int temp=*a;
		*a=*b;
		*b=temp;		
}
