// -----
//  main.c
//  	Tests an implementation of Edmonds-Karp from graphs.h

#include "graphs.h"

int
main(int argc, char const *argv[])
{
	// int a[2][3];
	//       ^  ^ contiguous, adjacents in a row [ incrementing this value goes to &a[x][y] + 1 ]
	//    noncontiguous, going down a column as this number increases

	/*
		{ [0][0] , [0][1] , [0][2] },
		{ [1][0] , [1][1] , [1][2] },
		{ [2][0] , [2][1] , [2][2] },
	*/

	// edge[i][j] = w; - edge of weight w > 0 exists from i to j

	int V = 4;	// just the number of vertices

	// if the nth column is 0, the nth node is a source
	// if the nth row is 0, then the nth node is a sink
	// to create reverse graph, transpose the matrix
	
	int edge[4][4] = 
	{
		{ 0 , 1 , 1 , 0 },
		{ 0 , 0 , 0 , 1 },
		{ 0 , 0 , 0 , 1 },
		{ 0 , 0 , 0 , 0 }
	};

	int caps[4][4] = 
	{
		{ 0 , 2 , 1 , 0 },
		{ 0 , 0 , 0 , 2 },
		{ 0 , 0 , 0 , 1 },
		{ 0 , 0 , 0 , 0 }
	};

	int e[2][2] =
	{
		{ 0, 1 },
		{ 0, 0 }
	};

	int c[2][2] =
	{
		{ 0, 2 },
		{ 0, 0 }
	};

	print(4, edge);

/*	transpose(4, edge);

	print(4, edge);

	transpose(4, edge);
*/
	int flow = EdmondsKarp(2, e, c, 0, 1);

	printf("Flow is %d\n", flow);
/*
	queue q = 
	{
		.size = 4,
		.items = { 0, 0, 0, 0 },
		.startpos = 0,
		.endpos = 0
	};*/
	int temp[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

	queue q;
	q.size = 8;
	q.items = temp;
	q.startpos = 0;
	q.endpos = 0;



	// printf("edge[0][0] = %d\n", edge[2][1]);

	return 0;
}