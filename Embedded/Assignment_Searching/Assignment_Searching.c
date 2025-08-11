#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct _node {
    struct _node* next;
} node;

typedef int (*FCMP)(const void*, const void*);

int starts_with_k_cmp(const void* a, const void* b) {
    const char* s = (const char*)a;
    (void)b;  // key를 사용하지 않음
    return (tolower(s[0]) == 'k') ? 0 : 1;
}

void init_list(node** p) {
    *p = (node*)malloc(sizeof(node));
    (*p)->next = NULL;
}

void* llv_insert(void* key, node* base, size_t* num, size_t width, FCMP fcmp) {
    node* t;
    t = (node*)malloc(sizeof(node) + width);
    memcpy(t + 1, key, width);
    t->next = base->next;
    base->next = t;
    (*num)++;
    return t;
}

void* llv_delete(void* key, node* base, size_t* num, size_t width, FCMP fcmp) {
    node* prev = base;
    node* cur = base->next;

    while (cur != NULL) {
        if (fcmp((void*)(cur + 1), key) == 0) {
            prev->next = cur->next;
            free(cur);
            (*num)--;
            return base;  // 삭제 성공
        }
        prev = cur;
        cur = cur->next;
    }
    return NULL;  // 삭제 실패
}

void* llv_search(void* key, node* base, size_t* num, size_t width, FCMP fcmp)
{
    node* t;
    t = base->next;
    while (fcmp(t + 1, key) != 0 && t != NULL) t = t->next;
    return (t == NULL ? NULL : t + 1);
}

void main() {
    FILE* fp = fopen("C:\\Users\\shinj\\Desktop\\3-1\\EmbeddedDataStructure\\name.txt", "r");

    node* head;
    int size = 0;
    init_list(&head);

    char buf[100];
    while (fgets(buf, sizeof(buf), fp)) {
        buf[strcspn(buf, "\n")] = 0; // 개행 제거
        llv_insert(buf, head, &size, strlen(buf) + 1, strcmp);
    }
    fclose(fp);

    printf("=== 'k'로 시작하는 이름 검색 ===\n");
    void* found;
    int count = 0;

    while ((found = llv_search(NULL, head, &size, sizeof(buf), starts_with_k_cmp)) != NULL) {
        printf("%2d. %s\n", ++count, (char*)found);
        llv_delete(found, head, &size, strlen((char*)found) + 1, strcmp);
    }

    if (count == 0)
        printf("조건에 맞는 항목이 없습니다.\n");
}