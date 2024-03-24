<<<<<<< HEAD
#include<stdio.h>						
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define size 65536					//值的范围-1才是 
#define maxsize 1000
#include <time.h>


void rangesort(int*array,int length/*待排数组长度*/);
void cmpcountsort(int list[],int length);


int main()
{
	int i; 
//	int list[maxsize]={35,32,6,13,22,28,31,20,23,18};
	srand((unsigned)time(0));
	int list[maxsize];
for(i=0;i<maxsize;i++){
	list[i]=rand()%65536;	}
	time_t start=clock();
	int* B=(int*)malloc(maxsize*sizeof(int));	//辅助数组空间，每个函数都可以调动，无冲突 
	cmpcountsort(list,maxsize);
	time_t end=clock();	
	printf("用时%fs\n",(double)(end-start)/CLOCKS_PER_SEC);			
for(i=0;i<maxsize;i++){
	printf("表数据第%d位置数据%d\n",i,list[i]);			}
	return 0;
}



void rangesort(int*list,int length/*待排数组长度*/)
{
	int* data=(int*)malloc(size*sizeof(int));;
	int i=0,j=0;
	memset(data,0,size*sizeof(int));
	for(i=0;i<length;++i)
		data[list[i]]++;		//统计各个数有几个 
	for(i=0;i<size;++i){
		while(data[i]--){		//有几个输出几个 
			list[j++]=i;
		}
	}
	free(data);
 } 
 
 
 
void cmpcountsort(int list[],int length)
 {
 	int i,j;
 	int*b,*count;
 	count=(int*)malloc(length*sizeof(int));
 	b=(int*)malloc(length*sizeof(int));
 	for(i=0;i<length;++i){
 		count[i]=0;
 		b[i]=list[i];
	 }
	 for(i=0;i<length;++i){
	 	for(j=i+1;j<length;++j)
	 		if(list[i]<=list[j])	count[j]++;			//统计应该在哪个位置 
	 		else	count[i]++;
	 }
	 for(i=0;i<length;++i)	list[count[i]]=b[i];
	 free(count);
	 free(b);
 }
=======
#include<stdio.h>						
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define size 65536					//值的范围-1才是 
#define maxsize 1000
#include <time.h>


void rangesort(int*array,int length/*待排数组长度*/);
void cmpcountsort(int list[],int length);


int main()
{
	int i; 
//	int list[maxsize]={35,32,6,13,22,28,31,20,23,18};
	srand((unsigned)time(0));
	int list[maxsize];
for(i=0;i<maxsize;i++){
	list[i]=rand()%65536;	}
	time_t start=clock();
	int* B=(int*)malloc(maxsize*sizeof(int));	//辅助数组空间，每个函数都可以调动，无冲突 
	cmpcountsort(list,maxsize);
	time_t end=clock();	
	printf("用时%fs\n",(double)(end-start)/CLOCKS_PER_SEC);			
for(i=0;i<maxsize;i++){
	printf("表数据第%d位置数据%d\n",i,list[i]);			}
	return 0;
}



void rangesort(int*list,int length/*待排数组长度*/)
{
	int* data=(int*)malloc(size*sizeof(int));;
	int i=0,j=0;
	memset(data,0,size*sizeof(int));
	for(i=0;i<length;++i)
		data[list[i]]++;		//统计各个数有几个 
	for(i=0;i<size;++i){
		while(data[i]--){		//有几个输出几个 
			list[j++]=i;
		}
	}
	free(data);
 } 
 
 
 
void cmpcountsort(int list[],int length)
 {
 	int i,j;
 	int*b,*count;
 	count=(int*)malloc(length*sizeof(int));
 	b=(int*)malloc(length*sizeof(int));
 	for(i=0;i<length;++i){
 		count[i]=0;
 		b[i]=list[i];
	 }
	 for(i=0;i<length;++i){
	 	for(j=i+1;j<length;++j)
	 		if(list[i]<=list[j])	count[j]++;			//统计应该在哪个位置 
	 		else	count[i]++;
	 }
	 for(i=0;i<length;++i)	list[count[i]]=b[i];
	 free(count);
	 free(b);
 }
>>>>>>> 7edc0a04ff39d0dd7f2435bd378bcebed8945e78
