<<<<<<< HEAD
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#define maxsize 10
#include <time.h>

int setpartition(int list[],int n);



int main(){
	int list[maxsize]={21,41,77,25,26,39,11,14,6,6};
	int i;  
//	srand((unsigned)time(0));
//	int list[maxsize];
//for(i=0;i<maxsize;i++){
//	list[i]=rand()%10000+1;	}
//	time_t start=clock();
	int ret=setpartition(list,maxsize);
	printf("��Ϊ%d\n",ret);
//	time_t end=clock();	
//	printf("��ʱ%fs\n",(double)(end-start)/CLOCKS_PER_SEC);		
for(i=0;i<maxsize;i++){
	printf("�����ݵ�%dλ������%d\n",i,list[i]);
}	
	return 0;
}


int setpartition(int list[],int n)
{
	int pivotkey,low=0,left=0,high=n-1,right=n-1,flag=1,k=n/2;
	int i,s1=0,s2=0;
	while(flag){
		pivotkey=list[low];
		while(low<high){
			while(low<high&&list[high]>=pivotkey)	--high;
			list[low]=list[high];
			while(low<high&&list[low]<=pivotkey)	++low;
			list[high]=list[low];
		}
		list[low]=pivotkey;
		if(k-1==low)	flag=0;		//������Ԫ�������м�ʱ���� 
		else if(low<k-1){
			left=++low;				//�����½� 
			high=right;	}
		else{
			right=--high;			//�����Ͻ� 
			low=left;	}
	}
	for(i=0;i<k;++i){
		s1+=list[i];
		s2+=list[i+k];
	}
	return s2-s1;
}

//ƽ��ʱ��O(n),�ռ�O(1) 

=======
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#define maxsize 10
#include <time.h>

int setpartition(int list[],int n);



int main(){
	int list[maxsize]={21,41,77,25,26,39,11,14,6,6};
	int i;  
//	srand((unsigned)time(0));
//	int list[maxsize];
//for(i=0;i<maxsize;i++){
//	list[i]=rand()%10000+1;	}
//	time_t start=clock();
	int ret=setpartition(list,maxsize);
	printf("��Ϊ%d\n",ret);
//	time_t end=clock();	
//	printf("��ʱ%fs\n",(double)(end-start)/CLOCKS_PER_SEC);		
for(i=0;i<maxsize;i++){
	printf("�����ݵ�%dλ������%d\n",i,list[i]);
}	
	return 0;
}


int setpartition(int list[],int n)
{
	int pivotkey,low=0,left=0,high=n-1,right=n-1,flag=1,k=n/2;
	int i,s1=0,s2=0;
	while(flag){
		pivotkey=list[low];
		while(low<high){
			while(low<high&&list[high]>=pivotkey)	--high;
			list[low]=list[high];
			while(low<high&&list[low]<=pivotkey)	++low;
			list[high]=list[low];
		}
		list[low]=pivotkey;
		if(k-1==low)	flag=0;		//������Ԫ�������м�ʱ���� 
		else if(low<k-1){
			left=++low;				//�����½� 
			high=right;	}
		else{
			right=--high;			//�����Ͻ� 
			low=left;	}
	}
	for(i=0;i<k;++i){
		s1+=list[i];
		s2+=list[i+k];
	}
	return s2-s1;
}

//ƽ��ʱ��O(n),�ռ�O(1) 

>>>>>>> 7edc0a04ff39d0dd7f2435bd378bcebed8945e78
