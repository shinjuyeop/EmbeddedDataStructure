#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10
int queue[MAX];
int front, rear;

void init_queue()
{
	front = 0;
	rear = 0;
}
void clear_queue()
{
	front = rear;
}

int put(int k)
{
	if ((rear + 1) % MAX == front)
	{
		printf("Queue overflow !!!\n");
		return -1;
	}
	queue[rear] = k;
	rear = ++rear % MAX;
	return k;
}

int get()
{
	int j;
	if (front == rear)
	{
		printf("Queue underflow !!!\n");
		return -1;
	}
	j = queue[front];
	front = ++front % MAX;  
	return j;
}

void print_queue()
{
	int k;
	for (k = front; k != rear; k = ++k % MAX)
		printf("% -6d", queue[k]);
	printf("\n");
}

void main()
{
	int k;
	init_queue();

	put(3);
	put(6);
	put(9);
	put(1);
	put(6);
	put(3);
	print_queue();

	get();
	print_queue();

	put(4);
	put(8);
	put(7);
	put(2);
	put(0);
	print_queue();

	init_queue();
	print_queue();

	get();
	print_queue();
}