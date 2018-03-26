/*
	Exercise: Vertex Coloring
	1. Complete the basic greedy coloring program below.
	2. Analyze the running time of the program.
		graphColoring() iterates over all the vertices [v times],

		In each of those iterations, it calls the function getAvailableColor()
		that traverses over all vertices adjacent to the vertex that finds available color
		which in worst case is v-1 [all vertices are connected to all other vertices]

		Therefore the entire algorithm runs in O(n^2) time. 
		
	3. Improve the quality of your solution by determining a good starting vertex.
		The starting vertex should have the most number of edges in such a way that the succeeding verteces
		will decrease in the number of edges
*/

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct node{
	int x;
	struct node *next;
}graph;

graph **createAdjList(int *, int *);
void viewList(graph **, int);
int * graphColoring(graph **, int);
int getAvailableColor(graph **, int *, int, int);
void viewColor(int *, int);
void deleteGraph(graph **, int);

int main(){
	graph **g;
	int v, e;
	int *color;

	
	g = createAdjList(&v, &e);
	color = graphColoring(g, v);
	viewList(g, v);
	viewColor(color, v);
	
	free(color);
	deleteGraph(g, v);
}

graph **createAdjList(int *v, int *e){
	/*insert code here for creating an adjacency list*/
	FILE *fileptr;
	fileptr = fopen("graph.in", "r");
	graph **g;
	graph *temp;
	int first;
	int second;

	if (fileptr == NULL)
	{
		printf("Error!");
		exit(1);
	}

	fscanf(fileptr, "%d", v);
	fscanf(fileptr, "%d", e);

	g = malloc(sizeof(graph *) * (*v));

	for(int i = 0; i < *e; i++) {
		fscanf(fileptr, "%d %d", &first, &second);
		temp = (graph *)malloc(sizeof(graph));
		temp->x = second;
		temp->next = g[first];
		g[first] = temp;

		temp = (graph *)malloc(sizeof(graph));
		temp->x = first;
		temp->next = g[second];
		g[second] = temp;
	}


	fclose(fileptr);

	return g;
}

void viewList(graph **g, int v){
	int i;
	graph *p;
	
	for(i = 0; i < v; i++){
		p = g[i];
		printf("%d: ", i);
		//traverse the list connected to vertex i
		while(p != NULL){
			printf("%3d", p->x);
			p = p->next;
		}
		printf("\n");
	}
}

int * graphColoring(graph **g, int v){
	int *color, availCol, i;
	
	//colors are represented as integers starting from 0
	color = (int *)malloc(sizeof(int)*v);
	for(i = 0; i < v; i++)
		color[i] = -1;
	
	color[0] = 0;	//assign first vertex with the first color
	for(i = 1; i < v; i++){
		availCol = getAvailableColor(g, color, v, i);
		color[i] = availCol;
	}
	return color;
}

int getAvailableColor(graph **g, int *color, int v, int curr){
	graph *p;
	int *available, i, availCol;
	
	//keeps track of the colors used on any previously colored vertices adjacent to it
	available = (int *)malloc(sizeof(int)*(v));
	for(i = 0; i < v; i++)
		available[i] = 1;
	
	/*Insert code here for marking the colors that have been used 
	on any previously colored vertices adjacent to it.*/
	
	p = g[curr];
	while (p != NULL) {
		if(color[p->x] != -1) {
			available[color[p->x]] = 0;
		}

		p = p->next;
	}
	
	
	for(i = 0; i < v; i++){				//get the smallest color that is available
		if(available[i] == 1){
			availCol = i;
			break;
		}
	}
	
	free(available);
	return availCol;
}

void viewColor(int *color, int v){
	int i;
	
	for(i = 0; i < v; i++){
		printf("Vertex %d -> Color %d\n", i, color[i]);
	}
}

void deleteGraph(graph **g, int v){
	int i;
	graph *p;
	for(i = 0; i < v; i++){
		while(g[i] != NULL){
			p = g[i];
			g[i] = g[i]->next;
			free(p);
		}
	}
	free(g);
}