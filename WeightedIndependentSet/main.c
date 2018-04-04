#include <stdio.h>
#define MAX(a,b) a>b?a:b

struct graph
{
	int size;
	int **v;
	int *w;
};
// Leaves are nodes whose row is all zero
// the constant checks of thee algorithm
// assuming the subproblems are solved would be O(|V|)
// But finding all leaves in adjacency matrix is O(|V|^2)
int
IS(int vertex, struct graph *G, int *s)
{
	if(s[vertex] != 0)
		return s[vertex];

	int ISChildren = 0;
	int ISGrandChildren = 0;

	int children[G->size];

	for(int i = 0; i < G->size; ++i)
		if(G->v[vertex][i])
			ISChildren += IS(i, G, s);

	for(int i = 0; i < G->size; ++i)
		if(children[i])
			ISGrandChildren += IS(children[i], G, s);

	return MAX(ISChildren, ISGrandChildren + G->w[vertex]);
}

int
main(void)
{
	int v;	/* Size of graph */
	//int G[v][v];	/* Directed towards children */
	//int W[v];		/* Weights of vertices */

	v = 4;
	int G[4][4] = 
	{
		{ 0 , 1 , 0 , 0 },
		{ 0 , 0 , 1 , 0 },
		{ 0 , 0 , 0 , 1 },
		{ 0 , 0 , 0 , 0 }
	};
	int W[] = { 8 , 1 , 1 , 3 };

	int S[v]; /* Answers to subproblems */

	for(int i = 0; i < v; ++i)	/* Zero out subproblem array */
		S[i] = 0;

	int lastLeaf = -1;

	/* Add weights of leaves to Subproblem array
	   Leaves are nodes in G where the row is empty */
	for(int i = 0; i < v; ++i)
	{
		int isZero = 1;

		for(int j = 0; j < v; ++j)
			isZero &= (G[i][j] == 0);

		if(isZero)
		{
			S[i] = W[i];
			lastLeaf = i;
		}	
	}

	struct graph Graph = 
	{
		.size = v,
		.v = G,
		.w = W
	};

	int result = IS(0, &Graph, S);

	printf("Result is %d. LL was %d\n", result, lastLeaf);

	return(0);
}