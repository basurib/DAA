#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int rand(void);

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int array[], int low, int high) {
    int pivot = array[high];
    int i = (low - 1);

    for(int j = low; j < high; j++) {
        if(array[j] <= pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }

    swap(&array[i + 1], &array[high]);

    return (i + 1);
}

void quickSort(int array[], int low, int high) {
    if(low < high) {
        int pi = partition(array, low, high);
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

int main()
{
    
    FILE *fptr;
    fptr = (fopen("quick.txt", "w"));

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
        quickSort(arr, 0, i*100 - 1);
        clock_t end = clock();
        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
        printf("%f\n", time_spent);
    }
    fclose(fptr);
    
    return 0;
}