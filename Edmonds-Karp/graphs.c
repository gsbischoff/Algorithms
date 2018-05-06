#include "graphs.h"

// All references to queues in this source names and 
// accesses start/end this manner, here we define a shorthand
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
			int s, int t)
{
	int pred[size];
	int flows[size][size];

	memset(flows, 0, size * size * sizeof(int));

	int flow = 0;

	do
	{
		memset(pred, 0, size * sizeof(int));

		for(int i = 0; i < size; ++i)
			pred[i] = -1;

		#if DEBUG
		for(int i = 0; i < size; ++i) printf("\tpred[%d] = %d\n", i, pred[i]);
		#endif
			
		// initialize queue of size of number of vertices
		queue Q = { size, 0, 0, 0 }; // size + 1
		queue *q = &Q;

		int temp[size];
		q->items = temp;

		push(q, s);

		// pred[v] - edge taken to get to vertex v (can use node taken to get there)
		// while q is not empty
		while(qStart != qEnd)
		{
			#if DEBUG
			printf("\t");
			printQueue(q);
			#endif

			int cur = pop(q);

			// for every neighbor to cur
			for (int i = 0; i < size; ++i)
			{
				if (Graph[cur][i] != 0 
					&& pred[i] == -1
					&& i != cur
					&& Graph[cur][i] > flows[cur][i]) // if such an edge exists
				{ //&& cap[cur][i] > flows[cur][i]
					pred[i] = cur;
					push(q, i);
				}
			}
		}
		#if DEBUG
		printf("Finished BFS!\n\n");
		for(int i = 0; i < size; ++i) printf("\tpred[%d] = %d\n", i, pred[i]);
		#endif

		if(pred[t] != -1)
		{
			int df = INT_MAX;
			int end = t;
			for(int e = pred[t]; e != -1; e = pred[e])
			{
				//df = min(df, cap[e][end] - flows[e][end]);
				df = min(df, Graph[e][end] - flows[e][end]);
				end = e;
			}

			end = t;
			for(int e = pred[t]; e != -1; e = pred[e])
			{
				flows[e][end] += df;
				flows[end][e] -= df; // reverse flows kept on opposite connections in same graph
			}

			flow += df;
			#if DEBUG
			printf("Flow: %d\n\n", flow);
			#endif
		}
	}
	while(pred[t] != -1);

	return flow;
}
