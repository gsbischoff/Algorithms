#ifndef GRAPHS_H
#define GRAPHS_H

#include <stdio.h>

// creating G^R is the same as transposing a graph's adjacency matix
#define reverse(a,b) transpose(a,b)

void transpose(int size, int matrix[size][size]);

void print(int size, int matrix[size][size]);

typedef struct
{
	int size;
	int *items;
	int startpos;
	int endpos;
} queue;

void push(queue *q, int item);

int pop(queue *q);

void printQueue(queue *q);

int EdmondsKarp(int size,
			int Graph[size][size],
			int s, int t);

#endif