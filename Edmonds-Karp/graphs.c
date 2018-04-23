#include "graphs.h"

#define qStart q->startpos
#define qEnd q->endpos 
#define qSize q->size

// -----
//  Transpose
//		Takes a square matrix and it's size as inputs
//			and transposes the matrix in-place

void
transpose(int size, int matrix[size][size]) //(int **matrix, int size)
{
	int i, j;

	for (i = 0; i < size; ++i)
	{
		for (j = i; j < size; ++j)
		{
			// swap the values [i][j] and [j][i]
			int t = matrix[i][j];
			matrix[i][j] = matrix[j][i];
			matrix[j][i] = t;
		}
	}
}

void
print(int size, int matrix[size][size])
{
	int i, j;

	for (i = 0; i < size; ++i)
	{
		printf("\n");
		for (j = 0; j < size; ++j)
			printf("%d ", matrix[i][j]);
	}
}

/*
typedef struct
{
	int size;
	int *items;
	int startpos;
	int endpos;
} queue;
*/
void
push(queue *q, int item)
{
	if ((qStart + qSize - 1) % qSize != qEnd % qSize)
	{
		q->items[qEnd] = item;

		qEnd++;
		qEnd = qEnd % qSize;
	}
}

int
pop(queue *q)
{
	// can't pop anything if nothing is there
	if (qStart == qEnd)
		return -1;

	int t = q->items[qStart];

	// now we must say how we've freed up space on the front
	qStart++;
	qStart = qStart % qSize;
	
	return t;
}

void
printQueue(queue *q)
{
	printf("Elements in queue: ");
	int i;
	for (i = qStart; i != qEnd; i = (i + 1) % qSize)
	{
		printf("%d ", q->items[i]);
	}
	printf("\n");
}



// -----
//  Edmonds-Karp max flow algorithm
//
// 		Implementing from this description:
// 		https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm

int
EdmondsKarp(int size,
			int Graph[size][size],
			int cap[size][size],
			int s, int t)
{
	int pred[size];
	int flows[size][size];

	memset(pred, 0, size * sizeof(int));
	memset(flows, 0, size * size * sizeof(int));

	for(int i = 0; i < size; ++i)
		pred[i] = -1;

	int flow = 0;
	do
	{
		// initialize queue of size of number of vertices
		queue Q = { size, 0, 0, 0 }; // size + 1
		queue *q = &Q;

		int temp[size];
		q->items = temp;

		//memset(temp, 0, sizeof(int) * size);

		push(q, s);

	/*	struct edges
		{
			int s = -1;
			int t = -1;
		} pred[size];*/


		//memset(pred, 0, sizeof(struct edges) * size);

		// pred[v] - edge taken to get to vertex v (can use node taken to get there)
		// while q is not empty
		while(qStart != qEnd)
		{
			printQueue(q);

			int cur = pop(q);

			// for every neighbor to cur
			for (int i = 0; i < size; ++i)
			{
				if (Graph[cur][i] != 0 
					&& pred[i] == -1
					&& i != cur
					&& cap[cur][i] > flows[cur][i]) // if such an edge exists
				{
					pred[i] = cur;
					push(q, i);
				}
			}
		}

		printf("HERE\n");

		if(pred[t] != -1)
		{
			int df = INT_MAX;
			int end = t;
			for(int e = pred[t]; e != -1; e = pred[e])
			{
				df = min(df, cap[e][end] - flows[e][end]);
				end = e;
			}

			end = t;
			for(int e = pred[t]; e != -1; e = pred[e])
			{
				flows[e][end] += df;
				flows[end][e] -= df; // reverse flows kept on opposite connections in same graph

			}

			flow += df;
		}
	}
	while(pred[t] != -1);

	return flow;
}
