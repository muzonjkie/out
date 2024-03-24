#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include <time.h>
#define maxsize 50000

void Bubblesort(int list[],int n);
void Bubblesort_2(int list[],int n);
void swap(int *a,int *b);

int main(){
	int i; 
	//int list[maxsize]={35,32,6,13,22,28,31,20,23,18};
	srand((unsigned)time(0));
	int list[maxsize];
for(i=0;i<maxsize;i++){
	list[i]=rand()%10000+1;	}
time_t start=clock();
Bubblesort(list,maxsize);
time_t end=clock();			
printf("用时%fs\n",(double)(end-start)/CLOCKS_PER_SEC);		
//for(i=0;i<maxsize;i++){
//	printf("表数据第%d位置数据%d\n",i,list[i]);			}	
	return 0;
}




void Bubblesort(int list[],int n)				//冒泡排序 
{
	int i,j;
	for(i=0;i<n-1;++i){			//n-1趟，n个元素 
		bool flag=false;
		for(j=n-1;j>i;--j)
			if(list[j-1]>list[j]){
				swap(&list[j-1],&list[j]);
				flag=true;
			}
			if(false==flag)		return;
	}
 } 
 
 
 
void Bubblesort_2(int list[],int n)			//双向冒泡排序 
{
	int low=0,high=n-1,i;
	bool flag=true;
	while(low<high&&flag){
		flag=false;					//每趟初始化为false 
		for(i=low;i<high;++i)
			if(list[i]>list[i+1]){
				swap(&list[i],&list[i+1]);
				flag=true;			//发生交换 
			}
		high--;						//更新上界 
		for(i=high;i>low;--i)
			if(list[i]<list[i-1]){
				swap(&list[i],&list[i-1]);
				flag=true;	
			}
		low++;						//更新下界 
	}
}
 
 
 
void swap(int *a,int *b)
{
	int temp=*a;
		*a=*b;
		*b=temp;		
}	
