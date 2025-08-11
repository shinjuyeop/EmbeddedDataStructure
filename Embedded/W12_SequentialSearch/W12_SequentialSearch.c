#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX 100
#define SIZE 100
#define BASE(i) ((char *)base + (i)*width)

typedef int (*FCMP)(const void*, const void*);

typedef struct _card {
    int no;
    char name[20];
}card;


int intcmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int card_cmp(const void* a, const void* b) {
    return ((card*)a)->no - ((card*)b)->no;
}

int card_cmp2(const void* a, const void* b) {
    return strcmp(((card*)a)->name, (const char*)b);
}


int lv_search(void* key, void* base, size_t* num, size_t width, FCMP fcmp) {
    int i = 0;
    while (fcmp(BASE(i), key) != 0 && i < *num) i++;
    return (i < *num ? i : -1);
}

int lv_insert(void* key, void* base, size_t* num, size_t width, FCMP fcmp) {
    memcpy(BASE((*num)++), key, width);
    return *num - 1;
}

int lv_delete(void* key, void* base, size_t* num, size_t width, FCMP fcmp) {
    int p, i;
    if (*num > 0) {
        if ((p = lv_search(key, base, num, width, fcmp)) < 0) return -1;
        for (i = p + 1; i < *num; i++)
            memcpy(BASE(i - 1), BASE(i), width);
        (*num)--;
        return p;
    }
    return -1;
}

int lfv_search(void* key, void* base, size_t* num, size_t width, FCMP fcmp) {
    int i = 0, j;
    void* v;
    while (fcmp(BASE(i), key) != 0 && i < *num) i++; // 같을 때 
    if (i >= *num) return -1;

    v = malloc(width);  // 원래 위치 값 백업
    memcpy(v, BASE(i), width);
    for (j = i - 1; j >= 0; j--)
        memcpy(BASE(j + 1), BASE(j), width);
    memcpy(BASE(0), v, width);
    free(v);
    return 0;
}

void print_array(int* data, size_t nitem) {
    printf("Current array:\n");
    for (size_t i = 0; i < nitem; i++) {
        printf("%4d ", data[i]);
        if ((i + 1) % 10 == 0) printf("\n");  // 10개씩 줄바꿈
    }
    printf("\n");
}

void print_cards(card* arr, size_t n) {
    printf("Current student records:\n");
    for (size_t i = 0; i < n; i++) {
        printf("No=%d, Name=%s\n", arr[i].no, arr[i].name);
    }
    printf("\n");
}

int main() {
    /*
    int data[SIZE];
    size_t nitem = 0;
    int key;

    srand((unsigned int)time(NULL));

    // 0~9999 사이의 랜덤값을 10,000개 삽입
    for (int i = 0; i < SIZE; i++) {
        int val = rand() % 100;
        lv_insert(&val, data, &nitem, sizeof(int), intcmp);
    }

    print_array(data, nitem);  // 전체 배열 출력

    // 사용자 입력으로 탐색 수행
    printf("Enter a number to search: ");
    scanf("%d", &key);

    int pos = lv_search(&key, data, &nitem, sizeof(int), intcmp);
    if (pos >= 0)
        printf("\nlv_search: Found %d at index %d\n", key, pos);
    else
        printf("\nlv_search: %d not found.\n", key);

    if (lfv_search(&key, data, &nitem, sizeof(int), intcmp) == 0) {
        printf("\nlfv_search: Moved %d to front.\n", key);
        print_array(data, nitem);  // 전체 배열 출력
    }

    if (lv_delete(&key, data, &nitem, sizeof(int), intcmp) >= 0) {
        printf("lv_delete: Deleted %d.\n", key);
        print_array(data, nitem);  // 전체 배열 출력
    }
    else
        printf("lv_delete: %d not found to delete.\n", key);
    */

    card table[MAX], key2;
    size_t nitem2 = 0;
    int pos2, FIND;

    // 초기 데이터 삽입
    table[nitem2++] = (card){ 1001, "Alice" };
    table[nitem2++] = (card){ 1002, "Bob" };
    table[nitem2++] = (card){ 1003, "Charlie" };

    printf("\n");
    print_cards(table, nitem2);

    // 검색
    printf("Enter student ID to find: ");
    scanf("%d", &FIND);
    key2.no = FIND;

    pos2 = lv_search(&key2, table, &nitem2, sizeof(card), card_cmp);
    if (pos2 >= 0)
        printf("lv_search: Found! No=%d, Name=%s\n", table[pos2].no, table[pos2].name);
    else
        printf("lv_search: Not found.\n");

    // 삽입
    printf("\nInsert new student (ID Name): ");
    scanf("%d %s", &key2.no, key2.name);
    lv_insert(&key2, table, &nitem2, sizeof(card), card_cmp);
    print_cards(table, nitem2);

    // 삭제
    printf("Enter student ID to delete: ");
    scanf("%d", &FIND);
    key2.no = FIND;

    if (lv_delete(&key2, table, &nitem2, sizeof(card), card_cmp) >= 0)
        printf("Deleted student with ID %d\n", FIND);
    else
        printf("Student ID %d not found to delete.\n", FIND);

    print_cards(table, nitem2);
   
    char FIND2[20];

    printf("Enter student Name to delete: ");
    scanf("%s", &FIND2);
    strcpy(key2.name, FIND2);

    if (lv_delete(FIND2, table, &nitem2, sizeof(card), card_cmp2) >= 0)
        printf("Deleted student with Name %s\n", FIND2);
    else
        printf("Student Name %s not found to delete.\n", FIND2);

    print_cards(table, nitem2);

    return 0;
}