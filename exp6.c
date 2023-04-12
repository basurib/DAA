//header files
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//graph handling
int** graphData; 
int* visited;
int* distances;
int* prevNode;
int numOfNodes;

//queue handling
int* nodesQueue;
int front=-1, rear=-1;

void enqueue(int elem){
    rear++;
    nodesQueue[rear]=elem;
}

int dequeue(){
	front++;
	return nodesQueue[front];
}

void sortQueue(){
    int temp;
    for(int i=front+1; i<rear; i++){
        if(distances[nodesQueue[i]]>distances[nodesQueue[i+1]]){
            temp=nodesQueue[i];
            nodesQueue[i]=nodesQueue[i+1];
            nodesQueue[i+1]=temp;
            i=front;
        }
    }
}

//dijkstra's algorithm
void dijkstras(int sourceNode){
	int currNode, tempDistance;
	enqueue(sourceNode);
    printf("Table showing the updated distances as the new nodes are getting visited-\n\n");
    printf("Node\t");
    for(int i=0; i<numOfNodes; i++){
        if(i!=sourceNode) printf("%d\t",i);
    }
    printf("\n-\t");
    for(int i=0; i<numOfNodes-1; i++){
        printf("%c\t",236);
    }
	while(front!=rear){
		currNode=dequeue();
		for(int i=0; i<numOfNodes; i++){
            if(graphData[currNode][i]!=-1){
                tempDistance=distances[currNode]+graphData[currNode][i];
                if(distances[i]==-1||tempDistance<distances[i]){
                    distances[i]=tempDistance;
                    prevNode[i]=currNode;
                }
                if(visited[i]==0){
                enqueue(i);
                visited[i]=1;
                }
            }
		}
        sortQueue();
        printf("\n%d\t",currNode);
        for(int i=0; i<numOfNodes; i++){
            if(i!=sourceNode){
                if(distances[i]==-1){
                    printf("%c\t",236);
                }
                else{
                    printf("%d\t",distances[i]);
                }
            }
        }
	}
}

//function for printing path with minimum cost
void printPath(int targetNode, int sourceNode){
    if(targetNode!=sourceNode){
        printPath(prevNode[targetNode], sourceNode);
        printf(" -> %d",targetNode);
    }
    else{
        printf("%d",sourceNode);
    }
}

//main function
void main(){
	int node,distance,sourceNode;
	
	printf("\nEnter the number of nodes in the graph -----> ");
	scanf("%d",&numOfNodes);
	
	graphData=(int**)malloc(numOfNodes*sizeof(int*));
	visited=(int*)malloc(numOfNodes*sizeof(int));
    distances=(int*)malloc(numOfNodes*sizeof(int));
    prevNode=(int*)malloc(numOfNodes*sizeof(int));
	nodesQueue=(int*)malloc(numOfNodes*sizeof(int));
	
	for(int i=0; i<numOfNodes; i++){
		visited[i]=0;
        distances[i]=-1;
		graphData[i]=(int*)malloc(numOfNodes*sizeof(int));
		for(int j=0; j<numOfNodes; j++){
			graphData[i][j]=-1;
		}
	}
	
	printf("Nodes 0 to %d were initialized...\n",numOfNodes-1);
	
	printf("Enter the information regarding graph connectivity-");
	for(int i=0; i<numOfNodes; i++){
		printf("\n\nEnter the nodes connected to %d along with the edge-cost(-1 to terminate)-\n",i);
		while(true){
			scanf("%d",&node);
			if(node==-1){
				break;
			}
			scanf("%d",&distance);
			graphData[i][node]=distance;
		}
	}
	
	printf("\nEnter the source node -----> ");
	scanf("%d",&sourceNode);
	distances[sourceNode]=0;
    visited[sourceNode]=1;
	
    printf("\nFollowing information was obtained from Dijkstra's algorithm-\n\n");
	dijkstras(sourceNode);
	
    printf("\n\nFollowing are the shortest paths obtained-");
    for(int i=0; i<numOfNodes; i++){
        if(i!=sourceNode){
            printf("\n\nFrom Node-%d to Node-%d(Cost: %d)\n",sourceNode,i,distances[i]);
            printPath(i,sourceNode);
        }
    }
    printf("\n\n");

    free(visited);
    free(distances);
    free(prevNode);
    free(nodesQueue);
    for(int i=0; i<numOfNodes; i++){
        free(graphData[i]);
    }
    free(graphData);
	
}