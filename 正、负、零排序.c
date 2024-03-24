#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#define maxsize 10
#include <time.h>



typedef enum {RED,WHITE,BLUE} color; 


void Flag_Arrange(color A[],int n);
void swap(color *a,color *b);

int main()
{
	int i;
color list[maxsize]={BLUE,RED,WHITE,WHITE,RED,WHITE,WHITE,RED,BLUE,BLUE};
Flag_Arrange(list,maxsize);	
	
for(i=0;i<maxsize;i++){
	printf("表数据第%d位置数据%d\n",i,list[i]);
}	
	return 0;
}



void Flag_Arrange(color list[],int n)
{
	int i=0,j=0,k=n-1;			//i之前全红，k之后全蓝 
	while(j<=k)
		switch(list[j]){
			case RED:	swap(&list[i],&list[j]); i++; j++; break;
			case WHITE:	j++; break;
			case BLUE:	swap(&list[j],&list[k]); k--;		//无j++是因为可能交换到的那个元素也是蓝色 
			}
}


void swap(color *a,color *b)
{
	color temp=*a;
		*a=*b;
		*b=temp;		
}
