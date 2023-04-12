#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//file for handling the input
FILE* data=NULL;
FILE* output=NULL;

//functions for sorting
void swap(int arr[], int ix, int iy){
	int temp=arr[ix];
	arr[ix]=arr[iy];
	arr[iy]=temp;
}

void insertionSort(int arr[], int size)
{
    int currentElem,j;
    for(int i=1; i<size; i++){
        currentElem=arr[i];
        j=i-1;
        while(j>=0 && arr[j]>currentElem){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=currentElem;
    }
}

void selectionSort(int arr[], int size)
{
    int minIndex;
    for (int i=0; i<size-1; i++){
        minIndex=i;
        for (int j=i+1; j<size; j++)
            if(arr[j]<arr[minIndex])
                minIndex=j;
        if(minIndex!=i)
            swap(arr,minIndex,i);
    }
}

//for bringing the values into the array(for sorting)
void arrayLoading(int arr[],int endpoint){
    data=fopen("data.txt","r");
    for(int i=0; i<endpoint; i++){
        fscanf(data,"%d",&arr[i]);
    }
    fclose(data);
}

void main(){
    srand(time(NULL));
    clock_t t;
	int tempArr[100000];

    //intiating the data file
    data=fopen("data.txt","w");
    for(int i=0; i<100000; i++){
        fprintf(data,"%d\n",rand());
    }
    fclose(data);

    //sorting and printing out the time taken
    output=fopen("output.txt","w");
    double timeI, timeS;
    for(int i=100; i<=100000; i+=100){
        arrayLoading(tempArr,i);
        t=clock();
        insertionSort(tempArr,i);
        t=clock()-t;
        timeI=((double)t)/CLOCKS_PER_SEC;
        arrayLoading(tempArr,i);
        t=clock();
        selectionSort(tempArr,i);
        t=clock()-t;
        timeS=((double)t)/CLOCKS_PER_SEC;
        fprintf(output,"%d\t\t%lf\t\t%lf\n",i,timeI,timeS);
        printf("Block count -----> %d\n",i);
    }
    fclose(output);
}