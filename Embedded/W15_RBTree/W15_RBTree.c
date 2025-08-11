#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int key;
    struct _node* left, * right;
    int red;  // 1이면 빨강, 0이면 검정
} node;

// 🔁 회전 함수: key를 기준으로 pivot의 아래에서 회전해 균형 맞춤
node* rotate(int key, node* pivot, node* base) {
    node* child, * gchild;

    // key가 pivot보다 작거나, pivot이 루트(dummynode)라면 왼쪽 자식 선택
    if (key < pivot->key || pivot == base)
        child = pivot->left;
    else
        child = pivot->right;

    // 회전 방향 결정
    if (key < child->key) {
        // LL 회전
        gchild = child->left;
        child->left = gchild->right;
        gchild->right = child;
    }
    else {
        // RR 회전
        gchild = child->right;
        child->right = gchild->left;
        gchild->left = child;
    }

    // 회전 결과를 pivot의 자식 위치에 연결
    if (key < pivot->key || pivot == base)
        pivot->left = gchild;
    else
        pivot->right = gchild;

    return gchild;  // 회전 후 서브트리의 새 루트 반환
}

// 🔺 Red-Black Tree 삽입 함수
node* rbti_insert(int key, node* base, int* num) {
    node* t, * parent, * gparent, * ggparent;

    // 모든 조상 포인터 초기화
    ggparent = gparent = parent = base;
    t = base->left;  // 진짜 트리의 루트

    // 트리 탐색 (BST 삽입과 동일)
    while (t != NULL) {
        if (key == t->key) return NULL;  // 중복 키는 삽입 안 함

        // 🔄 색깔 뒤집기 필요 조건: 현재 노드의 양 자식이 모두 빨간색
        if (t->left && t->right && t->left->red && t->right->red) {
            t->red = 1;                  // 현재 노드는 빨강으로
            t->left->red = 0;           // 자식 둘은 검정으로
            t->right->red = 0;

            // 🔁 red-red 충돌일 경우 회전으로 해결
            if (parent->red) {
                gparent->red = 1;  // 조부모는 빨강으로 올림

                // 삽입 방향이 바뀌었을 경우(zigzag 구조) 먼저 회전
                if ((key < gparent->key) != (key < parent->key))
                    parent = rotate(key, gparent, base);  // 먼저 작은 회전
                t = rotate(key, ggparent, base);          // 큰 회전
                t->red = 0;  // 새로 올라온 루트는 항상 검정
            }
        }

        // 조상 포인터 한 단계씩 아래로 갱신
        ggparent = gparent;
        gparent = parent;
        parent = t;
        t = (key < t->key) ? t->left : t->right;
    }

    // 새로운 노드 생성
    t = (node*)malloc(sizeof(node));
    t->key = key;
    t->left = t->right = NULL;
    t->red = 1;  // 삽입되는 새 노드는 항상 빨강

    // 새 노드를 parent의 적절한 위치에 붙임
    if (key < parent->key || parent == base)
        parent->left = t;
    else
        parent->right = t;

    (*num)++;  // 삽입된 노드 수 증가

    // 🔁 삽입 후 red-red 충돌일 경우 회전 처리
    if (parent->red) {
        gparent->red = 1;
        if ((key < gparent->key) != (key < parent->key))
            parent = rotate(key, gparent, base);
        t = rotate(key, ggparent, base);
        t->red = 0;  // 회전 후 올라온 루트는 항상 검정
    }

    // 트리 전체 루트는 항상 검정
    base->left->red = 0;

    return t;
}


void inorder(node* t) {
    if (!t) return;
    inorder(t->left);
    printf("%c(%s) ", t->key, t->red ? "R" : "B");
    inorder(t->right);
}

int main() {
    char seq[] = { 'K', 'L', 'C', 'A', 'E', 'F', 'D', 'I', 'H', 'G' };
    int n = sizeof(seq) / sizeof(seq[0]);
    int num = 0;

    node* base = (node*)malloc(sizeof(node));
    base->left = NULL;
    base->right = NULL;
    base->key = -1;
    base->red = 0; // dummy black node

    for (int i = 0; i < n; i++) {
        rbti_insert(seq[i], base, &num);
    }

    printf("Inorder traversal (char, color):\n");
    inorder(base->left);
    printf("\n");

    return 0;
}
