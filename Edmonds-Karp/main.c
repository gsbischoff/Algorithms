// -----
//  main.c
//  	Tests an implementation of Edmonds-Karp from graphs.h
//
//			by Greg B

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

	// Graph will need 2*(l + m + c + g) + 2
	//	Each part will need an edge restricting it to be used only once, so
	//	2 node for each part; and 2 additional points for source & sink
	int size = 2*(l + m + c + g) + 2;

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
		Graph[i + 2*(l + m + c)][t] = 1;

	int flow = EdmondsKarp(size, Graph, s, t);

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
			char *token;

			// Get component number
			token = strtok(buf, " \t");
			int partnum = atoi(token);

			// Get number of compatible parts
			token = strtok(NULL, " \t");
			int compatibleParts = atoi(token);

			// Connect the two nodes representing this part together, making it only selectable once 
			Graph[2*offset + partnum][2*offset + partnum + num] = 1;

			// Read in values of compatible parts and connect them
			for(int j = 0; j < compatibleParts; ++j)
			{
				token = strtok(NULL, " \t");
				int p = atoi(token);

				// Connect this part's second vertex to all parts it is compatible with (p of the following group)
				Graph[2*offset + partnum + num][2*(offset + num) + p] = 1;
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