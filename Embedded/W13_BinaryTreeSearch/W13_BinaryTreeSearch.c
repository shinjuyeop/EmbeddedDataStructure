#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int key;
    struct _node* left;
    struct _node* right;
} node;

void init_tree(node* base) {
    base->key = 0;       // dummy key
    base->left = NULL;   // real root
    base->right = NULL;  // not used
}

void visit(node* t) {
    printf("%c ", t->key);
}

void inorder_traverse(node* t) {
    if (t != NULL) {
        inorder_traverse(t->left);
        visit(t);
        inorder_traverse(t->right);
    }
}

// Search
node* bti_search(int key, node* base, int* num) {
    node* s = base->left; // root node
    while (s != NULL && key != s->key) {
        if (key < s->key) s = s->left;
        else s = s->right;
    }
    if (s == NULL)return NULL;
    return s;
}

// Insert
node* bti_insert(int key, node* base, int* num) {
    node* p = base, * s = base->left;
    while (s != NULL) {
        p = s;
        if (key < s->key) s = s->left;
        else s = s->right;
    }
    s = (node*)malloc(sizeof(node));
    s->key = key;
    s->left = NULL;
    s->right = NULL;

    if (key < p->key || p == base) p->left = s;
    else p->right = s;
    (*num)++;
    return s;
}

// Delete
node* bti_delete1(int key, node* base, int* num)
{
    node* parent = base, * del = base->left;
    node* son, * nexth;

    while (del != NULL && key != del->key) {
        parent = del;
        if (key < del->key) del = del->left;
        else del = del->right;
    }

    if (del == NULL) return NULL;

    if (del->left == NULL && del->right == NULL) {
        son = NULL;
    }
    else if (del->left != NULL && del->right != NULL) {
        nexth = del->right;
        if (nexth->left != NULL) {
            while (nexth->left->left != NULL) nexth = nexth->left;
            son = nexth->left;
            nexth->left = son->right;
            son->left = del->left;
            son->right = del->right;
        }
        else {
            son = nexth;
            son->left = del->left;
        }
    }
    else {
        if (del->left != NULL) son = del->left;
        else son = del->right;
    }

    if (key < parent->key || parent == base) parent->left = son;
    else parent->right = son;

    free(del);
    (*num)--;
    return parent;
}

// 예시: main()만 수정
int main() {
    node base;
    int num = 0;
    init_tree(&base);

    char keys[] = { 'F', 'B', 'A', 'D', 'C', 'O', 'L', 'G', 'H', 'K', 'M', 'N' };
    int size = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < size; ++i)
        bti_insert(keys[i], &base, &num);

    printf("In-order Traversal before Deletion: ");
    inorder_traverse(base.left);
    printf("\n");

    bti_delete1('F', &base, &num);

    printf("In-order Traversal after Deleting 'F': ");
    inorder_traverse(base.left);
    printf("\n");

    return 0;
}