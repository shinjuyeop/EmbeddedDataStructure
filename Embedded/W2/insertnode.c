/*
#include <stdio.h>
#include <stdlib.h>

// 구조체 정의
struct Node {
    int val;
    struct Node* next;
};

// 노드 삽입 함수: 현재 노드(t) 뒤에 값이 k인 새 노드를 삽입
struct Node* insert_after(int k, struct Node* t) {
    // 1. 새 노드 동적 할당
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    // 2. 값 설정
    new_node->val = k;
    // 3. 연결: 새 노드의 next는 t의 next가 가리키던 걸 가리키게 함
    new_node->next = t->next;
    // 4. t->next가 새 노드를 가리키게 함
    t->next = new_node;
    // 5. 삽입된 새 노드를 반환 (선택 사항)
    return new_node;
}

int main() {
    // 첫 번째 노드 s1 생성
    struct Node* s1 = (struct Node*)malloc(sizeof(struct Node));
    s1->val = 3;
    s1->next = NULL;

    // s1 뒤에 새 노드 삽입 (값: 9)
    struct Node* p = insert_after(9, s1);

    // 리스트 출력: 3 9
    struct Node* curr = s1;
    while (curr != NULL) {
        printf("%d ", curr->val);
        curr = curr->next;
    }

    // 메모리 해제 (선택적으로 추가 가능)
    free(p);
    free(s1);

    return 0;
}
*/