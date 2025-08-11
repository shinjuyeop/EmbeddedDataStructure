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

// Insert (not balanced)
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

// Inorder Traversal to Sort Tree into Array 배열에 저장
void bti_sort(node* p, int* a, int* index) { // p : 원래 트리, a : 새 배열
    if (p != NULL) {
        bti_sort(p->left, a, index);
        a[(*index)++] = p->key;
        bti_sort(p->right, a, index);
    }
}

// -----------------------------
// Construct Balanced Tree from Sorted Array
node* _balance(int N, int* a, int* index) {
    int nl, nr;
    node* p;
    if (N > 0) {
        nl = (N - 1) / 2;
        nr = N - nl - 1;
        p = (node*)malloc(sizeof(node));
        p->left = _balance(nl, a, index);
        p->key = a[(*index)++];
        p->right = _balance(nr, a, index);
        return p;
    }
    return NULL;
}

int main() {
    int i = 0;
    int index = 0; // array의 index
    int num = 0; // 노드의 개수
    int input[] = { 'C', 'A', 'E', 'B', 'D', 'F' }; // 비균형 트리용 입력
    int size = sizeof(input) / sizeof(int);
    int* sorted = (int*)malloc(sizeof(int) * size);

    node base;               // dummy 노드
    init_tree(&base);       // 트리 초기화

    for (int i = 0; i < size; ++i)
        bti_insert(input[i], &base, &num); // 트리 세팅

    // 원래 트리 출력
    printf("Inorder of original (unbalanced) tree:\n");
    inorder_traverse(base.left);
    printf("\n");

    // 정렬
    index = 0;
    bti_sort(base.left, sorted, &index);

    // 균형 트리 생성
    index = 0;
    node* balanced = _balance(size, sorted, &index);

    // 균형 트리 출력
    printf("Inorder of balanced tree:\n");
    inorder_traverse(balanced);
    printf("\n");

    free(sorted);
    return 0;
}
