#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int key;
    struct _node* next;
} node;

node* head;

void insert_nodes(int k) {
    // make a list from 1 to k
    node* t;
    int i;
    t = (node*)calloc(1, sizeof(node));
    t->key = 1;
    head = t;
    for (i = 2; i <= k; i++) {
        t->next = (node*)calloc(1, sizeof(node));
        t = t->next;
        t->key = i;
    }
    t->next = head;
}

void delete_after(node* t) {
    node* s;
    s = t->next;
    t->next = t->next->next;
    free(s);
}

void josephus(int n, int m) {
    node* t;
    int i;
    insert_nodes(n);
    t = head;
    printf("\nAnswer : ");
    while (t != t->next) {
        for (i = 0; i < m - 1; i++)
            t = t->next;
        printf(" %c", (t->next->key)+'A'-1);
        delete_after(t);
    }
    printf(" %c", (t->key)+'A'-1); // last node
}

void main() {
    int n, m;

    printf("Enter N and M :");
    scanf("%d %d", &n, &m);

    josephus(n, m);
}
