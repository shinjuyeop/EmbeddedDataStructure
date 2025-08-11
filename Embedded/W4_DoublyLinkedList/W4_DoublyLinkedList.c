#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _dnode
{
	int key;
	struct _dnode *prev;
	struct _dnode *next;
}dnode;

dnode *head, *tail;

void init_dlist()
{
	head = (dnode*)calloc(1, sizeof(dnode));
	tail = (dnode*)calloc(1, sizeof(dnode));
	head->next = tail;
	head->prev = head;
	tail->next = tail;
	tail->prev = head;
}

dnode* find_dnode(int k)
{
	dnode* s;
	s = head->next;
	while (s->key != k && s != tail)
		s = s->next;
	return s;
}

int delete_dnode(int k)
{
	dnode* s;
	s = find_dnode(k);
	if (s != tail)
	{
		s->prev->next = s->next;
		s->next->prev = s->prev;
		free(s);
		return 1;
	}
	return 0;
}

dnode* insert_dnode(int k, int t)
{
	dnode* s;
	dnode* i = NULL;
	s = find_dnode(t);
	if (s != tail)
	{
		i = (dnode*)calloc(1, sizeof(dnode));
		i->key = k;
		s->prev->next = i;
		i->prev = s->prev;
		s->prev = i;
		i->next = s;
	}
	return i;
}

dnode* ordered_insert(int k)
{
	dnode* s;
	dnode* i;
	s = head->next;
	while (s->key <= k && s != tail)
		s = s->next;
	i = (dnode*)calloc(1, sizeof(dnode));
	i->key = k;
	s->prev->next = i;
	i->prev = s->prev;
	s->prev = i;
	i->next = s;
	return i;
}

void printf_dlist(dnode *p)
{
	printf("\n");
	while (p != tail)
	{
		printf("% -8d", p->key);
		p = p->next;
	}
}

void main()
{
	dnode *t;

	init_dlist();
	
	ordered_insert(9);
	ordered_insert(3);
	ordered_insert(5);
	ordered_insert(1);
	ordered_insert(7);
	ordered_insert(2);
	ordered_insert(4);
	
	printf_dlist(head->next);
	
	t = find_dnode(5);
	printf("\nFinding 5 is %s successful", t == tail ? "un" : "");

	insert_dnode(5, 4);
	insert_dnode(9, 2);
	delete_dnode(4);

	printf_dlist(head->next);

}

