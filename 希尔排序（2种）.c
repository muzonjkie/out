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
	printf("��ʱ%fs\n",(double)(end-start)/CLOCKS_PER_SEC);	
//for(i=0;i<maxsize;i++){
//	printf("�����ݵ�%dλ������%d\n",i,list[i]);
//}	
	return 0;
}




void shellsort1(int list[],int n){
	int d,i,j,k,temp;
for(d=n/2;d>=1;d=d/2){
	for(i=0;i<d;i++){				//�ĺ�һ��������һ�� 
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
	for(i=d;i<n;i++){						//����л��� 
	if(list[i]<list[i-d]){
	temp=list[i];							//temp���Բ��� 
		for(j=i-d;j>=0&&temp<list[j];j-=d){			//��ϲ��� 
		list[j+d]=list[j];	}
		list[j+d]=temp;		}
		}
	}
}

