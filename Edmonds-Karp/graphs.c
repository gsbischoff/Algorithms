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
			// swipe the values [i][j] and [j][i]
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

// -----
//  Simple messy queue
//  	Uses an array, keeps track of start and end to know where 
//				to add/pop allows for (size - 1) elements

typedef struct
{
	int size;
	int *items;
	int startpos;
	int endpos;
} queue;

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
	int flow = 0;

	// initialize queue of size of number of vertices
	queue Q = { size + 1, 0, 0, 0 }, 
	*q = &Q;

	int temp[size];
	q->items = temp;

	push(q, s);

	struct edges
	{
		int s;
		int t;
	} pred[size];

	while(qStart != qEnd)
	{
		int cur = pop(q);

		// for every neighbor
		int i;
		for (i = 0; i < size; ++i)
		{
			if (Graph[cur][i] != 0 
				&& pred[]) // if such an edge exists
			{
				


				push(q, e.t)
			}
		}
	}



	return flow;
}
