//header files
#include<stdio.h>
#include<stdlib.h>

//structure for an item in the knapsack problem
struct item{
    int itemId;
    double weight;
    double profitVal;
    double profitByWeightRatio;
};

//function to solve the knapsack problem
int solveKnapsack(struct item items[], int numOfItems, double capacity){

    //sorting the array
    struct item tempItem;
    for(int i=0; i<numOfItems-1; i++){
        if(items[i].profitByWeightRatio<items[i+1].profitByWeightRatio){
            tempItem=items[i];
            items[i]=items[i+1];
            items[i+1]=tempItem;
            i=-1;
        }
    }
    printf("\nThe rearranged items based on their profit to weight ratio are as follows-\n\n");
    printf("Item\tProfit\tWeight\tProfit to Weight Ratio\n");
    for(int i=0; i<numOfItems; i++){
        printf("I%d\t%.0lf\t%.0lf\t%.2lf\n",items[i].itemId,items[i].profitVal,items[i].weight,items[i].profitByWeightRatio);
    }

    //selecting the required items as per greedy approach
    int index=0;
    double maxProfitVal=0;
    while(index<numOfItems){
        if(items[index].weight<=capacity){
            maxProfitVal+=items[index].profitVal;
            capacity-=items[index].weight;
            index++;
        }
        else if(capacity>0){
            maxProfitVal+=(items[index].profitVal)*(capacity/items[index].weight);
            break;
        }
    }
    printf("\nThe max profit value as obtained(considering greedy approach towards both weight and profit) -----> %.2lf\n",maxProfitVal);

    return index;

}

//main function
void main(){

    //taking user inputs
    int numOfItems;
    double capacity;
    printf("\nEnter the number of items to be considered for knapsack -----> ");
    scanf("%d",&numOfItems);
    printf("Enter the capacity of knapsack -----> ");
    scanf("%lf",&capacity);

    //dynamically allocating the memory for array of items
    struct item* items=malloc(numOfItems*sizeof(struct item*));

    //taking inputs regarding all the items
    printf("\nEnter the Weight and Profit value of all the items-\n");
    for(int i=0; i<numOfItems; i++){
        printf("Item-%d -----> ",i+1);
        items[i].itemId=i+1;
        scanf("%lf",&items[i].weight);
        scanf("%lf",&items[i].profitVal);
        items[i].profitByWeightRatio=(items[i].profitVal)/(items[i].weight);
    }

    //solving the knapsack problem
    int index=solveKnapsack(items,numOfItems,capacity);
    double weightSum=0;
    printf("Set of items to be included in the knapsack -----> {");
    for(int i=0; i<index; i++){
        printf("I%d, ",items[i].itemId);
        weightSum+=items[i].weight;
    }
    if(weightSum<capacity){
        printf("(%.0lf/%.0lf) of I%d}\n\n",capacity-weightSum,items[index].weight,items[index].itemId);
    }

    //deallocating the used memory
    free(items);

}