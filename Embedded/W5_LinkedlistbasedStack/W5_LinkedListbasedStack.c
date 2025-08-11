#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int key;
	struct _node* next;
} node;

node *head, *tail;

void init_stack()
{
	head = (node*)calloc(1, sizeof(node));
	tail = (node*)calloc(1, sizeof(node));
	head->next = tail;
	tail->next = tail;
}

int push(int k)
{
	node* t;
	if ((t = (node*)malloc(sizeof(node))) == NULL)
	{
		printf("Out of memory !\n");
		return -1;
	}

	t->key = k;
	t->next = head->next;
	head->next = t;

	return k;
}

int pop()
{
	node* t;
	int k;
	if (head->next == tail)
	{
		printf("Stack underflow !\n");
		return -1;
	}
	t = head->next;
	k = t->key;
	head->next = t->next;
	free(t);

	return k;
}

void clear()
{
	node* t, * s;
	t = head->next;

	while (t != tail)
	{
		s = t;
		t = t->next;
		free(s);
	}

	head->next = tail;
}

void print_stack()
{
	node* t;
	t = head->next;
	printf("Stack (top to bottom): ");
	while (t != tail) {
		printf("%d ", t->key);
		t = t->next;
	}
	printf("\n");
}

int main()
{
	int k;
	init_stack();

	// 1. Push 3, 6, 9, 1, 6, 3 and print
	push(3); push(6); push(9); push(1); push(6); push(3);
	printf("After pushing 3 6 9 1 6 3:\n");
	print_stack();

	// 2. Pop one element and print
	k = pop();
	printf("Popped: %d\n", k);
	print_stack();

	// 3. Push 4, 8, 7, 2, 0 and print
	push(4); push(8); push(7); push(2); push(0);
	printf("After pushing 4 8 7 2 0:\n");
	print_stack();

	// 4. Initialize (clear) your stack
	clear();
	printf("After clearing the stack:\n");
	print_stack();

	// 5. Pop after clear
	k = pop();
	printf("Popped after reset: %d\n", k);

	return 0;
}
