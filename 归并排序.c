<<<<<<< HEAD
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#define maxsize 10
#include <time.h>



void Merge(int list[],int low,int mid,int high,int B[]);
void Mergesort(int list[],int low,int high,int B[]);



int main()
{
	int i; 
//	int list[maxsize]={35,32,6,13,22,28,31,20,23,18};
	srand((unsigned)time(0));
	int list[maxsize];
for(i=0;i<maxsize;i++){
	list[i]=rand()%100+1;	}
	time_t start=clock();
	int* B=(int*)malloc(maxsize*sizeof(int));	//��������ռ䣬ÿ�����������Ե������޳�ͻ 
	Mergesort(list,0,maxsize-1,B);
	time_t end=clock();	
	printf("��ʱ%fs\n",(double)(end-start)/CLOCKS_PER_SEC);			
for(i=0;i<maxsize;i++){
	printf("�����ݵ�%dλ������%d\n",i,list[i]);			}
	return 0;
}


void Merge(int list[],int low,int mid,int high,int B[])
{
	int i,j,k;
	for(k=low;k<=high;++k)				//���ֵĶ��� 
		B[k]=list[k];
	for(i=low,j=mid+1,k=i;i<=mid&&j<=high;++k){		//���ڷ����Ҳ��� 
		if(B[i]<=B[j])					
			list[k]=B[i++];
		else
			list[k]=B[j++];
	}
	while(i<=mid)	list[k++]=B[i++];			//����δ����� 
	while(j<=high)	list[k++]=B[j++];
}


void Mergesort(int list[],int low,int high,int B[])
{
	if(low<high){					//���ֵ���Сһ��ֻ��һ��Ԫ�� 
		int mid=(low+high)/2;
		Mergesort(list,low,mid,B);
		Mergesort(list,mid+1,high,B);
		Merge(list,low,mid,high,B);
	}
}
=======
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#define maxsize 10
#include <time.h>



void Merge(int list[],int low,int mid,int high,int B[]);
void Mergesort(int list[],int low,int high,int B[]);



int main()
{
	int i; 
//	int list[maxsize]={35,32,6,13,22,28,31,20,23,18};
	srand((unsigned)time(0));
	int list[maxsize];
for(i=0;i<maxsize;i++){
	list[i]=rand()%100+1;	}
	time_t start=clock();
	int* B=(int*)malloc(maxsize*sizeof(int));	//��������ռ䣬ÿ�����������Ե������޳�ͻ 
	Mergesort(list,0,maxsize-1,B);
	time_t end=clock();	
	printf("��ʱ%fs\n",(double)(end-start)/CLOCKS_PER_SEC);			
for(i=0;i<maxsize;i++){
	printf("�����ݵ�%dλ������%d\n",i,list[i]);			}
	return 0;
}


void Merge(int list[],int low,int mid,int high,int B[])
{
	int i,j,k;
	for(k=low;k<=high;++k)				//���ֵĶ��� 
		B[k]=list[k];
	for(i=low,j=mid+1,k=i;i<=mid&&j<=high;++k){		//���ڷ����Ҳ��� 
		if(B[i]<=B[j])					
			list[k]=B[i++];
		else
			list[k]=B[j++];
	}
	while(i<=mid)	list[k++]=B[i++];			//����δ����� 
	while(j<=high)	list[k++]=B[j++];
}


void Mergesort(int list[],int low,int high,int B[])
{
	if(low<high){					//���ֵ���Сһ��ֻ��һ��Ԫ�� 
		int mid=(low+high)/2;
		Mergesort(list,low,mid,B);
		Mergesort(list,mid+1,high,B);
		Merge(list,low,mid,high,B);
	}
}
>>>>>>> 7edc0a04ff39d0dd7f2435bd378bcebed8945e78
