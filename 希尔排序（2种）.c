#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include <time.h>
#define maxsize 50000

void shellsort1(int list[],int n);
void shellsort2(int list[],int n);



int main(){
//	int list[maxsize]={3,9,35,32,5,18,30,16,11,6};
	int i,n; 	

	srand((unsigned)time(0));
	int list[maxsize];
for(i=0;i<maxsize;i++){
	list[i]=rand()%10000+1;	}
	time_t start=clock();
	shellsort2(list,maxsize);
	time_t end=clock();	
	printf("用时%fs\n",(double)(end-start)/CLOCKS_PER_SEC);	
//for(i=0;i<maxsize;i++){
//	printf("表数据第%d位置数据%d\n",i,list[i]);
//}	
	return 0;
}




void shellsort1(int list[],int n){
	int d,i,j,k,temp;
for(d=n/2;d>=1;d=d/2){
	for(i=0;i<d;i++){				//拍好一组再排下一组 
		for(j=i+d;j<n;j+=d){
			temp=list[j];
			k=j-d;
			while(k>=0&&list[k]>temp){
				list[k+d]=list[k];
				k=k-d;		}
			list[k+d]=temp;	
			}
		}
	}
}


void shellsort2(int list[],int n){
	int d,i,j,k,temp;
for(d=n/2;d>=1;d=d/2){
	for(i=d;i<n;i++){						//组间切换排 
	if(list[i]<list[i-d]){
	temp=list[i];							//temp可以不用 
		for(j=i-d;j>=0&&temp<list[j];j-=d){			//结合插排 
		list[j+d]=list[j];	}
		list[j+d]=temp;		}
		}
	}
}

