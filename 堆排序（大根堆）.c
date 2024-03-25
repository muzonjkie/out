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
	printf("�����ݵ�%dλ������%d\n",i,list[i]);
}		
	return 0;
}




void BuildMaxHeap(int list[],int n)
{
	int i;
	for(i=n/2;i>0;--i)			//�����һ�����ڵ㿪ʼ,list��һ��ʼ�洢 
		HeapAdjust(list,i,n);
}


void HeapAdjust(int list[],int k,int n)
{								//����kΪ������������Ϊ�� 
	int i;
	list[0]=list[k];
	for(i=2*k;i<=n;i*=2){
		if(i<n&&list[i]<list[i+1])	i++;
		if(list[0]>=list[i])		break;		//������Ѿ����������������� 
		else{
			list[k]=list[i];	
			k=i;						//���������Ϊ��������ԭ��Ӧ�ڵ�λ�� 
		}
	}
	list[k]=list[0];
}



void Heapsort(int list[],int n)
{
	int i;
	BuildMaxHeap(list,n);
	for(i=n;i>1;--i){
		swap(&list[i],&list[1]);		//�����ķŵ������ 
		HeapAdjust(list,1,i-1);			//�����һ��Ԫ���⣬�ٵ����ɴ���� 
	}
}


void swap(int *a,int *b)
{
	int temp=*a;
		*a=*b;
		*b=temp;		
}
