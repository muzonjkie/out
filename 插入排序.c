<<<<<<< HEAD
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include <time.h>
#define maxsize 50000


void Insertsort(int list[],int n);
void Insertsort_2(int list[],int n);


int main(){
	int i; 
//	int list[maxsize]={35,32,6,13,22,28,31,20,23,18};
	srand((unsigned)time(0));
	int list[maxsize];
for(i=0;i<maxsize;i++){
	list[i]=rand()%10000+1;	}
	time_t start=clock();
	Insertsort_2(list,maxsize);
	time_t end=clock();	
	printf("��ʱ%fs\n",(double)(end-start)/CLOCKS_PER_SEC);			
//for(i=0;i<maxsize;i++){
//	printf("�����ݵ�%dλ������%d\n",i,list[i]);			}	
	return 0;
}



void Insertsort(int list[],int n)
{
	int i,j,temp;
for(i=1;i<n;i++)
	if(list[i]<list[i-1]){						
		temp=list[i];							//�����ں����Ԫ�ر�ǰ�滹С���ݴ� 
		for(j=i-1;temp<list[j]&&j>=0;--j)		//�Ӵ�Ԫ��ǰһλ������Ųֱ���ҵ���Ӧ�ڵ�λ�� 
		list[j+1]=list[j];
		list[j+1]=temp; 	}					//�����λ�ã����Բ���temp 
}



void Insertsort_2(int list[],int n)
{
	int i,j,low,high,mid;
for(i=2;i<=n;++i){
	list[0]=list[i];					//�ݴ� 
	low=1;
	high=i-1;
	while(low<=high){
		mid=(low+high)/2;
		if(list[mid]>list[0])	high=mid-1;
		else	low=mid+1;
	}
	for(j=i-1;j>=high+1;--j)		//ͳһ�����ڿռ� 
		list[j+1]=list[j];
		list[j+1]=list[0]; 						//�����λ��
}							 
}
=======
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include <time.h>
#define maxsize 50000


void Insertsort(int list[],int n);
void Insertsort_2(int list[],int n);


int main(){
	int i; 
//	int list[maxsize]={35,32,6,13,22,28,31,20,23,18};
	srand((unsigned)time(0));
	int list[maxsize];
for(i=0;i<maxsize;i++){
	list[i]=rand()%10000+1;	}
	time_t start=clock();
	Insertsort_2(list,maxsize);
	time_t end=clock();	
	printf("��ʱ%fs\n",(double)(end-start)/CLOCKS_PER_SEC);			
//for(i=0;i<maxsize;i++){
//	printf("�����ݵ�%dλ������%d\n",i,list[i]);			}	
	return 0;
}



void Insertsort(int list[],int n)
{
	int i,j,temp;
for(i=1;i<n;i++)
	if(list[i]<list[i-1]){						
		temp=list[i];							//�����ں����Ԫ�ر�ǰ�滹С���ݴ� 
		for(j=i-1;temp<list[j]&&j>=0;--j)		//�Ӵ�Ԫ��ǰһλ������Ųֱ���ҵ���Ӧ�ڵ�λ�� 
		list[j+1]=list[j];
		list[j+1]=temp; 	}					//�����λ�ã����Բ���temp 
}



void Insertsort_2(int list[],int n)
{
	int i,j,low,high,mid;
for(i=2;i<=n;++i){
	list[0]=list[i];					//�ݴ� 
	low=1;
	high=i-1;
	while(low<=high){
		mid=(low+high)/2;
		if(list[mid]>list[0])	high=mid-1;
		else	low=mid+1;
	}
	for(j=i-1;j>=high+1;--j)		//ͳһ�����ڿռ� 
		list[j+1]=list[j];
		list[j+1]=list[0]; 						//�����λ��
}							 
}
>>>>>>> 7edc0a04ff39d0dd7f2435bd378bcebed8945e78
