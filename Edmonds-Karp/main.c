// -----
//  main.c
//  	Tests an implementation of Edmonds-Karp from graphs.h

#include "graphs.h"

// Helper function to fill in edges between next 'num' components, 'offset' from start
void
parseComponentEdges(int size, 
					int Graph[size][size], 
					int num, int offset,
					FILE *input);

int
main(int argc, char const *argv[])
{
	if(argc != 2)
	{
		printf("Usage: %s file\n", argv[0]);
		return(1);
	}

	FILE *input = fopen(argv[1], "r");

	if(!input)
	{
		fprintf(stderr, "cannot open %s: %s\n", argv[1], strerror(errno));
		return(1);
	}

	char buf[30];
	int l, m, c, g;	

	if(fgets(buf, 30, input))
		sscanf(buf, "%d %d %d %d", &l, &m, &c, &g);

	// Graph will need l + m + c + g + 2 (for s & t) vetices
	int size = l + m + c + g + 2;

	int Graph[size][size];
	memset(Graph, 0, size * size * sizeof(int));

	int s = 0;
	int t = size - 1;

	// Get components and their connections with this overzealous helper function
	parseComponentEdges(size, Graph, l, 0, input);
	parseComponentEdges(size, Graph, m, l, input);
	parseComponentEdges(size, Graph, c, l + m, input);
	parseComponentEdges(size, Graph, g, l + m + c, input);

	// Connect component vertices to source and sink
	for(int i = 1; i <= l; ++i)
		Graph[s][i] = 1;

	for(int i = 1; i <= g; ++i)
		Graph[i + (l + m + c)][t] = 1;

	//print(size, Graph);

	//int flow = EdmondsKarp(size, Graph, s, t);

	//printf("Max Flow is %d.\n", flow);

	//int sz = 3;

	int ed[3][3] =
	{
		{ 0, 4, 2 },
		{ 0, 1, 0 },
		{ 0, 0, 0 }
	};

	int flow = EdmondsKarp(3, ed, 0, 2);

	printf("Max Flow is %d.\n", flow);

	return(0);
}

void
parseComponentEdges(int size, 
					int Graph[size][size], 
					int num, int offset,
					FILE *input)
{
	char buf[30];

	for(int i = 0; i < num; ++i)
	{
		if(fgets(buf, 30, input))
		{
			// Get component number
			char *token;
			token = strtok(buf, " \t");

			int partnum = atoi(token);

			// Get number of compatible parts
			token = strtok(NULL, " \t");

			int parts = atoi(token);

			// Read in those values and make them edges in the graph
			for(int j = 0; j < parts; ++j)
			{
				token = strtok(NULL, " \t");

				int p = atoi(token);

				Graph[offset + partnum][offset + num + p] = 1;
			}
		}
	}
}

// -----
//  NOTES
// int a[2][3];
//       ^  ^ contiguous, adjacents in a row [ incrementing this value goes to &a[x][y] + 1 ]
//    noncontiguous, going down a column as this number increases

/*
	{ [0][0] , [0][1] , [0][2] },
	{ [1][0] , [1][1] , [1][2] },
	{ [2][0] , [2][1] , [2][2] },
*/

// edge[i][j] = w; - edge of weight w > 0 exists from i to j

// if the nth column is 0, the nth node is a source
// if the nth row is 0, then the nth node is a sink
// to create reverse graph, transpose the matrix