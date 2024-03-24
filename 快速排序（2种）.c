<<<<<<< HEAD
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#define maxsize 50000
#include <time.h>

void quicksort(int list[],int low,int high);
int Parition(int list[],int low,int high);
void swap(int *a,int *b);
void quicksort2(int list[],int low,int high);
int Parition2(int list[],int low,int high);


int main(){
//	int list[maxsize]={21,41,77,25,26,39,11,14,6,6};
	int i;  
	srand((unsigned)time(0));
	int list[maxsize];
for(i=0;i<maxsize;i++){
	list[i]=rand()%10000+1;	}
	time_t start=clock();
	quicksort(list,0,maxsize-1);
	time_t end=clock();	
	printf("用时%fs\n",(double)(end-start)/CLOCKS_PER_SEC);		
//for(i=0;i<maxsize;i++){
//	printf("表数据第%d位置数据%d\n",i,list[i]);
//}	
	return 0;
}




void quicksort(int list[],int low,int high){

	if(high>low){
		int pivotpos=Parition(list,low,high);
		quicksort(list,low,pivotpos-1);
		quicksort(list,pivotpos+1,high);
	}
}
	
int Parition(int list[],int low,int high){
	int pivot=list[low];
while(low<high){
	while(low<high&&list[high]>=pivot) --high;
	list[low]=list[high];
	while(low<high&&list[low]<=pivot)  ++low;
	list[high]=list[low];
}
	list[low]=pivot;
	return low;
}	
	
	
//--------------------------------------------版本二-------------	
	
void quicksort2(int list[],int low,int high){
	int k=0;
	if(high>low){
		int pivotpos=Parition2(list,low,high);
		quicksort2(list,low,pivotpos-1);
		quicksort2(list,pivotpos+1,high);
	}
}
 
int Parition2(int list[],int low,int high)	
{	
	srand((unsigned)time(0));
	int index=low+rand()%(high-low+1);
	swap(&list[index],&list[low]);
	int pivot=list[low];
	int i=low,j;					
	for(j=low+1;j<=high;j++)
		if(list[j]<pivot)
		swap(&list[++i],&list[j]);	/*从第二个位置开始，若有小于枢轴元素的时候就把它放到左边 
		当没有之后，这个i就是枢轴元素的位置*/ 
		swap(&list[i],&list[low]);			//放到枢轴位置 

	return i;
}


void swap(int *a,int *b)
{
	int temp=*a;
		*a=*b;
		*b=temp;		
}	
	
	
	
	
=======
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#define maxsize 50000
#include <time.h>

void quicksort(int list[],int low,int high);
int Parition(int list[],int low,int high);
void swap(int *a,int *b);
void quicksort2(int list[],int low,int high);
int Parition2(int list[],int low,int high);


int main(){
//	int list[maxsize]={21,41,77,25,26,39,11,14,6,6};
	int i;  
	srand((unsigned)time(0));
	int list[maxsize];
for(i=0;i<maxsize;i++){
	list[i]=rand()%10000+1;	}
	time_t start=clock();
	quicksort(list,0,maxsize-1);
	time_t end=clock();	
	printf("用时%fs\n",(double)(end-start)/CLOCKS_PER_SEC);		
//for(i=0;i<maxsize;i++){
//	printf("表数据第%d位置数据%d\n",i,list[i]);
//}	
	return 0;
}




void quicksort(int list[],int low,int high){

	if(high>low){
		int pivotpos=Parition(list,low,high);
		quicksort(list,low,pivotpos-1);
		quicksort(list,pivotpos+1,high);
	}
}
	
int Parition(int list[],int low,int high){
	int pivot=list[low];
while(low<high){
	while(low<high&&list[high]>=pivot) --high;
	list[low]=list[high];
	while(low<high&&list[low]<=pivot)  ++low;
	list[high]=list[low];
}
	list[low]=pivot;
	return low;
}	
	
	
//--------------------------------------------版本二-------------	
	
void quicksort2(int list[],int low,int high){
	int k=0;
	if(high>low){
		int pivotpos=Parition2(list,low,high);
		quicksort2(list,low,pivotpos-1);
		quicksort2(list,pivotpos+1,high);
	}
}
 
int Parition2(int list[],int low,int high)	
{	
	srand((unsigned)time(0));
	int index=low+rand()%(high-low+1);
	swap(&list[index],&list[low]);
	int pivot=list[low];
	int i=low,j;					
	for(j=low+1;j<=high;j++)
		if(list[j]<pivot)
		swap(&list[++i],&list[j]);	/*从第二个位置开始，若有小于枢轴元素的时候就把它放到左边 
		当没有之后，这个i就是枢轴元素的位置*/ 
		swap(&list[i],&list[low]);			//放到枢轴位置 

	return i;
}


void swap(int *a,int *b)
{
	int temp=*a;
		*a=*b;
		*b=temp;		
}	
	
	
	
	
>>>>>>> 7edc0a04ff39d0dd7f2435bd378bcebed8945e78
