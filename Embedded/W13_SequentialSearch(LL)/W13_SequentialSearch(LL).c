#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct _node {struct _node* next;} node;
typedef int (*FCMP)(const void*, const void*);

int intcmp(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}

void init_list(node** p) {
	*p = (node*)malloc(sizeof(node));  // 더미 헤드 노드생성 
	(*p)->next = NULL;
}

void* llv_search(void* key, node* base, int* num, size_t width, FCMP fcmp)
{
	node* t = base->next;
	while (t != NULL && fcmp(t + 1, key) != 0) {
		t = t->next;
	}
	return (t == NULL ? NULL : t + 1);
}

void* llv_insert(void* key, node* base, int* num, size_t width, FCMP fcmp)
{
	node* t;
	t = (node*)malloc(sizeof(node) + width);
	memcpy(t+1, key, width);
	t->next = base->next;
	base->next = t;
	(*num)++;
	return t;
}

void* llv_delete(void* key, node* base, int* num, size_t width, FCMP fcmp)
{
	node* prev = base;
	node* curr = base->next;

	while (curr != NULL && fcmp(curr + 1, key) != 0) {
		prev = curr;
		curr = curr->next;
	}

	if (curr == NULL) return NULL; // 못 찾음

	prev->next = curr->next; // 연결 끊기
	void* data_ptr = curr + 1;
	free(curr);
	(*num)--;
	return data_ptr;
}

void* llfv_search(void* key, node* base, int* num, size_t width, FCMP fcmp)
{
	node* prev = base;
	node* curr = base->next;

	while (curr != NULL && fcmp(curr + 1, key) != 0) {
		prev = curr;
		curr = curr->next;
	}

	if (curr == NULL) return NULL; // not found

	// 이미 맨 앞이면 이동할 필요 없음
	if (prev == base) return curr + 1;

	// Move-to-front: 연결 위치 재조정
	prev->next = curr->next;
	curr->next = base->next;
	base->next = curr;

	return curr + 1;
}

void print_list(node* head) {
	node* curr = head->next;
	while (curr != NULL) {
		int* val = (int*)(curr + 1);
		printf("%d ", *val);
		curr = curr->next;
	}
	printf("\n\n");
}

#define LEN 5

void main() {
	void* p;
	node* t;
	node* head;
	int num = 0, key = 9;
	int data[LEN] = { 3, 1, 9, 7, 5 };
	init_list(&t); // using the pointer t
	head = t;

	for (int i = 0; i < LEN; i++) {
		p = llv_insert(data + i, head, &num, sizeof(int), intcmp);
	}

    printf("Linked list contents:\n");
    node* curr = head->next;	
	print_list(head);

	p = llv_search(&key, head, &num, sizeof(int), intcmp);
	if (p != NULL) {
		node* curr = head->next;
		int index = 0;
		while ((curr + 1) != p) {
			curr = curr->next;
			index++;
		}
		printf("Found key %d at index %d in the linked list.\n", key, index);
	}
	else {
		printf("Key %d not found.\n", key);
	}

	p = llfv_search(&key, head, &num, sizeof(int), intcmp);
	if (p != NULL) {
		printf("Key %d found and moved to front.\n", key);
	}
	else {
		printf("Key %d not found.\n", key);
	}
	printf("Linked list after search:\n");
	print_list(head);


	// Delete key
	printf("Deleting key %d...\n", key);
	void* deleted = llv_delete(&key, head, &num, sizeof(int), intcmp);
	if (deleted != NULL) {
		printf("Key %d deleted successfully.\n", key);
	}
	else {
		printf("Key %d not found for deletion.\n", key);
	}

	// Print again
	printf("Linked list after deletion:\n");
	print_list(head);

}
