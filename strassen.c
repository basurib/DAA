//header files
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include<time.h>

//functions for dynamic creation, destruction of matrices
int** createMatrix(int order){
    int** matrix;
    matrix=(int**)calloc(order,sizeof(int*));
    for(int i=0; i<order; i++){
        matrix[i]=(int*)calloc(order,sizeof(int));
    }
    return matrix;
}

void destroyMatrix(int** matrix, int order){
    for(int i=0; i<order; i++){
        free(matrix[i]);
    }
    free(matrix);
}

//function for addition of matrices
int** addSubMat(int** matA, int** matB, int order, bool isAdd){
    int** resultMat=createMatrix(order);
    for(int i=0; i<order; i++){
        for(int j=0; j<order; j++){
            if(isAdd)
                resultMat[i][j]=matA[i][j]+matB[i][j];
            else
                resultMat[i][j]=matA[i][j]-matB[i][j];
        }
    }
    return resultMat;
}

//functions for matrix input and output
void takeMatInput(int** matrix, int rowM, int colM){
    for(int i=0; i<rowM; i++){
        for(int j=0; j<colM; j++){
            //scanf("%d",&matrix[i][j]);
            matrix[i][j]=1;
        }
    }
}

void displayMat(int** matrix, int rowM, int colM){
    for(int i=0; i<rowM; i++){
        for(int j=0; j<colM; j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}

//functions for partioning and joining of matrices
void partitionMat(int*** matrices, int** matA, int** matB, int order){
    int tempi=0, tempj=0;
    for(int i=0; i<order/2; i++){
        for(int j=0; j<order/2; j++){
            matrices[0][i][j]=matA[i][j];
            matrices[4][i][j]=matB[i][j];
        }
    }
    for(int i=0; i<order/2; i++){
        for(int j=order/2; j<order; j++){
            matrices[1][i][tempj]=matA[i][j];
            matrices[5][i][tempj]=matB[i][j];
            tempj++;
        }
        tempj=0;
    }
    for(int i=order/2; i<order; i++){
        for(int j=0; j<order/2; j++){
            matrices[2][tempi][j]=matA[i][j];
            matrices[6][tempi][j]=matB[i][j];
        }
        tempi++;
    }
    tempi=tempj=0;
    for(int i=order/2; i<order; i++){
        for(int j=order/2; j<order; j++){
            matrices[3][tempi][tempj]=matA[i][j];
            matrices[7][tempi][tempj]=matB[i][j];
            tempj++;
        }
        tempi++;
        tempj=0;
    }
}

void joinMats(int*** matrices, int** resultMat, int order){
    int tempi=0, tempj=0;
    for(int i=0; i<order/2; i++){
        for(int j=0; j<order/2; j++){
            resultMat[i][j]=matrices[8][i][j];
        }
    }
    for(int i=0; i<order/2; i++){
        for(int j=order/2; j<order; j++){
            resultMat[i][j]=matrices[9][i][tempj];
            tempj++;
        }
        tempj=0;
    }
    for(int i=order/2; i<order; i++){
        for(int j=0; j<order/2; j++){
            resultMat[i][j]=matrices[10][tempi][j];
        }
        tempi++;
    }
    tempi=tempj=0;
    for(int i=order/2; i<order; i++){
        for(int j=order/2; j<order; j++){
            resultMat[i][j]=matrices[11][tempi][tempj];
            tempj++;
        }
        tempi++;
        tempj=0;
    }
}

//using strassens method of matrix multiplication
int** strassensMul(int** matA, int** matB, int order){
    int** resultMat=createMatrix(order);
    int*** matrices;
    //base condition
    if(order==1){
        resultMat[0][0]=matA[0][0]*matB[0][0];
        return resultMat;
    }
    //strassen's logic
    matrices=(int***)malloc(19*sizeof(int**));
    for(int i=0; i<19; i++)
        matrices[i]=createMatrix(order/2);
    //partitioning the original matrix into 4 smaller matrices
    partitionMat(matrices,matA,matB,order);
    //using the obtained partitions to get the result matrix
    matrices[12]=strassensMul(addSubMat(matrices[0],matrices[2],order/2,true),addSubMat(matrices[4],matrices[5],order/2,true),order/2);
    matrices[13]=strassensMul(addSubMat(matrices[1],matrices[3],order/2,true),addSubMat(matrices[6],matrices[7],order/2,true),order/2);
    matrices[14]=strassensMul(addSubMat(matrices[0],matrices[3],order/2,false),addSubMat(matrices[4],matrices[7],order/2,true),order/2);
    matrices[15]=strassensMul(matrices[0],addSubMat(matrices[5],matrices[7],order/2,false),order/2);
    matrices[16]=strassensMul(addSubMat(matrices[2],matrices[3],order/2,true),matrices[4],order/2);
    matrices[17]=strassensMul(addSubMat(matrices[0],matrices[1],order/2,true),matrices[7],order/2);
    matrices[18]=strassensMul(matrices[3],addSubMat(matrices[6],matrices[4],order/2,false),order/2);
    //obtaining the result partitions
    matrices[8]=addSubMat(addSubMat(matrices[13],matrices[14],order/2,true),addSubMat(matrices[17],matrices[18],order/2,true),order/2,false);
    matrices[9]=addSubMat(matrices[15],matrices[17],order/2,true);
    matrices[10]=addSubMat(matrices[16],matrices[18],order/2,true);
    matrices[11]=addSubMat(addSubMat(matrices[12],matrices[14],order/2,false),addSubMat(matrices[15],matrices[16],order/2,true),order/2,false);
    //combining the partitions to get the final result
    joinMats(matrices,resultMat,order);
    //deallocating the used matrices
    for(int i=0; i<19; i++)
        destroyMatrix(matrices[i],order/2);
    free(matrices);
    return resultMat;
}

//defining naive approach of matrix multiplication for comparison
int** naiveMul(int** matA, int** matB, int rA, int cA, int cB, int order){
    int** resultMat=createMatrix(order);
    int sum;
    for(int i=0; i<rA; i++){
        for(int j=0; j<cB; j++){
            sum=0;
            for(int k=0; k<cA; k++){
                sum+=matA[i][k]*matB[k][j];
            }
            resultMat[i][j]=sum;
        }
    }
    return resultMat;
}

//main function
void main(){
    clock_t time;
    //taking user input of order of matrices and converting it to suitable square order
    int rA, cA, rB, cB;
    printf("\nEnter the number of rows and columns in matrix-A -----> ");
    scanf("%d %d",&rA,&cA);
    printf("Enter the number of rows and columns in matrix-B -----> ");
    scanf("%d %d",&rB,&cB);
    int max1=rA>cA?rA:cA;
    int max2=rB>cB?rB:cB;
    int max=max1>max2?max1:max2;
    int order=(int)pow(2,ceil((log(max)/log(2))));
    int** matA=createMatrix(order);
    int** matB=createMatrix(order);
    int** resultMat=createMatrix(order);
    //printf("\nEnter Matrix-A-\n\n");
    takeMatInput(matA,rA,cA);
    //printf("\nEnter Matrix-B-\n\n");
    takeMatInput(matB,rB,cB);
    printf("\nAll cells in the matrices were initialized with 1.....\n");
    time=clock();
    resultMat=strassensMul(matA,matB,order);
    time=clock()-time;
    //printf("\nMatrix AxB as obtained-\n\n");
    //displayMat(resultMat,rA,cB);
    printf("\nTime taken to perform the strassen's multiplication: %lf seconds",(double)time/CLOCKS_PER_SEC);
    //temp
    time=clock();
    resultMat=naiveMul(matA,matB,rA,cA,cB,order);
    time=clock()-time;
    //displayMat(resultMat,rA,cB);
    printf("\nTime taken to perform the naive matrix multiplication: %lf seconds\n\n",(double)time/CLOCKS_PER_SEC);
    //temp
    destroyMatrix(matA,order);
    destroyMatrix(matB,order);
    destroyMatrix(resultMat,order);
    printf("\n\n");
}