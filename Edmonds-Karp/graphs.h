#ifndef GRAPHS_H
#define GRAPHS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define DEBUG 0

// creating G^R is the same as transposing a graph's adjacency matix
#define reverse(a,b) transpose(a,b)
#define min(a,b) (a>b?b:a)

void transpose(int size, int matrix[size][size]);

void print(int size, int matrix[size][size]);

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

void push(queue *q, int item);

int pop(queue *q);

void printQueue(queue *q);

int EdmondsKarp(int size,
			int Graph[size][size],
			int s, int t);

#endif