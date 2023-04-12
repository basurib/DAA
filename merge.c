#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int rand(void);

void merge(int arr[], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;

    int L[n1], M[n2];

    for(int i = 0; i < n1; i++)
        L[i] = arr[p + i];
    for(int j = 0; j < n2; j++)
        M[j] = arr[q + 1 + j];

    int i, j, k;
    i = 0;
    j = 0;
    k = p;

    while(i < n1 && j < n2) {
        if(L[i] <= M[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = M[j];
            j++;
        }
        k++;
    }

    while(i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j < n2) {
        arr[k] = M[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if(l < r) {
        int m = l + (r - 1) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int main()
{
    
    FILE *fptr;
    fptr = (fopen("merge.txt", "w"));

    for(int i = 1; i <= 1000; i++)
    {
        int arr[i*100];
        for(int j = 0; j < (i*100); j++)
        {
            int num = (rand() % (i*100)) + 1;
            arr[i] = num;
            fprintf(fptr,"%d \n", num);
        }
        double time_spent = 0.0;
        clock_t begin = clock();
        mergeSort(arr,0,i*100 - 1);
        clock_t end = clock();
        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
        printf("%f\n", time_spent);
    }
    fclose(fptr);
    
    return 0;
}