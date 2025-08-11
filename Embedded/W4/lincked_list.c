#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int key;
    struct _node* next;
} node;

node* head, * tail;

void init_list() {
    head = (node*)calloc(1, sizeof(node));
    tail = (node*)calloc(1, sizeof(node));
    head->next = tail;
    tail->next = NULL;
}

node* ordered_insert(int k) {
    node* s, * p, * r;
    p = head;
    s = p->next;

    while (s != tail && s->key <= k) {
        p = p->next;
        s = p->next;
    }

    r = (node*)calloc(1, sizeof(node));
    if (!r) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    r->key = k;
    p->next = r;
    r->next = s;
    return r;
}

void print_list() {
    node* p = head->next;
    while (p != NULL && p != tail) {
        printf("%d -> ", p->key);
        p = p->next;
    }
    printf("NULL\n");
}

node* find_node(int k) {
    node* p = head->next;
    while (p != tail) {
        if (p->key == k) return p;
        p = p->next;
    }
    return NULL;
}

void insert_after(node* target, int k) {
    if (!target) return;
    node* r = (node*)calloc(1, sizeof(node));
    if (!r) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    r->key = k;
    r->next = target->next;
    target->next = r;
}

void delete_node(int k) {
    node* p = head, * s = head->next;

    while (s != tail && s->key != k) {
        p = p->next;
        s = p->next;
    }

    if (s != tail) {
        p->next = s->next;
        free(s);
    }
}

void free_list() {
    node* p = head, * temp;

    while (p != NULL) {
        temp = p;
        p = p->next;
        free(temp);
    }
}

int main() {
    init_list();

    ordered_insert(9);
    ordered_insert(3);
    ordered_insert(5);
    ordered_insert(1);
    ordered_insert(7);

    printf("Initial List: ");
    print_list();

    node* found = find_node(5);
    if (found) {
        insert_after(found, 6);
    }

    printf("After inserting 6 after 5: ");
    print_list();

    delete_node(5);

    printf("After deleting node 5: ");
    print_list();

    free_list();
    return 0;
}
