/*
   Name: Amit Vikram Singh
   Roll No: 111601001
   Date: 10/10/2017
   Task: eulerian.c
   Running Programme: enter "make" command in terminal, and output(object) file eulerian.o will be created.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<stdbool.h>
#include "heap.h"
#include<time.h>

clock_t clock(void);

struct Graph{		//Structure to store graph information
	int **adjWt;
	int V;    	   //V: no of vertices
	char GraphName[100];
	int isolated;
	int components;
};

struct v_Info{			//structure to store information about vertices during BFS
		int dist;	//distance of vertex from root
		bool Checked;
		int prev;
		int connected_to_goal;
};

typedef struct Graph Graph;
typedef struct v_Info v_Info;

Graph *CreateGraph(int V){		//Creating graph data
	Graph *G = (Graph*)malloc(sizeof(Graph));
	G->V = V;
	G->adjWt = (int**)malloc(G->V * sizeof(int*));
	for(int i=0; i<G->V; i++)		//allocating space for adjacency matrix
		G->adjWt[i] = (int*)calloc(G->V, sizeof(int));

	G->components = 0;
	G->isolated = 0;

	return G;
}

v_Info* bfsv_Info(Graph *G, int root, int goal){
	v_Info *v_InfoPtr;

	v_InfoPtr = (v_Info*)malloc(G->V * sizeof(v_Info));

  for(int i = 0; i<G->V; i++){
    v_InfoPtr[i].dist = 0;
		v_InfoPtr[i].Checked = false;
  }
	v_InfoPtr[root].dist = 0;
	return v_InfoPtr;
}

//Creating dot file
void MakeDot(Graph *G,v_Info *v_I, int x, int y){
	FILE *fp;
	char GraphName_cp[50];
	strcpy(GraphName_cp,G->GraphName);
	strcat(GraphName_cp,"new.dot");
	printf("Output: %s\n",GraphName_cp);
	fp = fopen(GraphName_cp,"w");
	fprintf(fp, "%s%s%s\n", "graph ",G->GraphName,"{");
	for(int i=0; i< G->V-1; i++){
		for(int j=i; j<G->V; j++){
			if(G->adjWt[i][j]>0){
			if(v_I[j].connected_to_goal == 1 && (i == v_I[j].prev || j == v_I[i].prev) && v_I[i].connected_to_goal == 1){
			 fprintf(fp, "%s%d -- %d%s%d%s","\t",i,j,"[color =red][label=",G->adjWt[i][j],"];\n");
			 }
			else fprintf(fp, "%s%d -- %d%s","\t",i,j,";\n");
			}
		}
	}
	fprintf(fp, "%s%d%s","\t",G->V-1,"\n");

	fprintf(fp, "%s\n", "}");
}


//Printing adjacency matrix
void printAdjacency(Graph *G){

	for(int i=0; i<G->V; i++){
		printf("%d: ",i);
		for(int j=0; j<G->V; j++){
			printf("%d ",G->adjWt[i][j]);
		}
		printf("\n");
	}

}

void printPath(Graph *G, v_Info *v_I, int x, int y){
	while(y!=x){
		printf("%d ",y);
		v_I[y].connected_to_goal = 1;
		y = v_I[y].prev;
	}

	printf("%d \n",y);
	v_I[y].connected_to_goal = 1;
}

void dijkstra(Graph *G, v_Info *v_I, heap **h, int x, int y){

	clock_t t;
	 t = clock();

	while(!isEmptyHeap(h)){
		// printf("value: %d: ", popHeapMin(h).value);
		arr data = popHeapMin(h);

		v_I[data.index].Checked = true;

		for(int i = 0; i<G->V; i++){
			if(v_I[i].Checked == false && G->adjWt[data.index][i] > 0){
				int loc = (*h)->hashTable[i];
				// printf("i: %d location: %d\n",i, loc);
				int temp = data.value + G->adjWt[data.index][i];
				if(temp < (*h)->array[loc].value){
					(*h)->array[loc].value = temp;
					minHeapifyUp(h, loc);
					v_I[i].dist = temp;
					v_I[i].prev = data.index;
				}
			}
		}

	}

	printf("Path is: ");

	printPath(G, v_I,x, y);//fundtion to print path
	MakeDot(G, v_I, x, y); //fundtion to make dot file
	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC;
	printf("Time Taken: %f\n",time_taken );
}

void insertHeap(Graph *G,v_Info *v_I, heap **h, int x){
	for(int i = 0; i<G->V; i++){
		heapInsert(h, 1000, i);
	}

	(*h)->array[x].value = 0;
	swap(h, x, 0);
	// printHeap(h);
}

//Reading Graph file
Graph* Read(FILE **fp){
	char GraphName[50] ;
	fscanf(*fp, " %[^\n]s", GraphName);	//reading graph name
	char GraphType[50];
	fscanf(*fp, " %[^\n]s", GraphType);	//reding graph type
	int num_vertices;
	fscanf(*fp, "%d", &num_vertices);	//scannig number of vertices in the graph
	Graph* G = CreateGraph(num_vertices);

	for(int i=0;i<G->V; i++){	//reading adjacecy matrix
		for(int j=0;j<G->V;j++){
			fscanf(*fp, "%1d", &G->adjWt[i][j]);
		}
	}

	strcpy(G->GraphName,GraphName);

	printAdjacency(G);
	return G;
}

//main begins here
int main(){
	char FileName[50];
	printf("Enter Filename: ");
	scanf("%s", FileName);

	FILE *fp;
	fp=fopen(FileName, "r");	//Opening .txt file


	 if(fp==0)	//Checking for file error in opening
	 {
	  	printf("Error in opening the file %s.\n", FileName);
	  	return(1);
	 }
	Graph *G = Read(&fp);
	v_Info *v_I = bfsv_Info(G, 0, 0);
	printf("Enter x and y: ");
	int x, y;
	scanf("%d%d",&x,&y);
	heap *h = createHeap(G->V);
	insertHeap(G, v_I, &h, x);
	fclose(fp);

	dijkstra(G, v_I, &h, x, y);
	return 0;

}
//main ends here
