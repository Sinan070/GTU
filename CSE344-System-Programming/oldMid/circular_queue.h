#ifndef __CIRCULAR_QUEUE_H
#define __CIRCULAR_QUEUE_H

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#endif

typedef struct{
	int rear;
	int front;
	unsigned size;
	long int *array;
}Queue;

Queue *queueInitialize(unsigned);
void enqueue(Queue * queue, int item);
long int dequeue(Queue * queue);
void display(Queue *);
int is_empty(Queue *queue);