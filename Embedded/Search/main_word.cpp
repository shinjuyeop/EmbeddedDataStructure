#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BTSlibrary.h"

typedef struct _wcount {
    int count;
    char word[20];
} wcount;

node* head;
const char delim[] = " \t\r\n,.-";

// 비교 함수
int wcount_cmp(const void* a, const void* b) {
    return strcmp(((wcount*)a)->word, ((wcount*)b)->word);
}
// 출력 함수
void print_wcount(void* a) {
    printf("%s : %d\n", ((wcount*)a)->word, ((wcount*)a)->count);
}

// 그래픽 출력용 문자열 생성 함수
void make_str(void* a, char* s) {
    strcpy(s, ((wcount*)a)->word);
}

void main() {
    int num = 0;
    char str[256], * tok;
    wcount wc, * wcp;

    init_tree(&head);

    FILE* fp;
    fp = fopen("C:\\Users\\shinj\\Desktop\\3-1\\EmbeddedDataStructure\\test.txt", "r");

    fgets(str, 256, fp); // read one line
    while (!feof(fp)) {
        tok = strtok(str, delim);
        while (tok) {
            strcpy(wc.word, tok);
            wcp = (wcount*)btv_search(&wc, head, &num, sizeof(wcount), wcount_cmp);
            if (wcp == NULL) {
                wc.count = 1;
                btv_insert(&wc, head, &num, sizeof(wcount), wcount_cmp);
            }
            else {
                wcp->count++;
            }
            tok = strtok(NULL, delim);
        }
        fgets(str, 256, fp);
    }
    fclose(fp);

    printf("\n▶ 현재 트리 구조 (텍스트 출력)\n");
    btv_list(head->left, print_wcount);

    printf("\n▶ 단어 빈도 (오름차순 출력)\n");
    btv_sort_list(head->left, print_wcount);

    printf("\n▶ 트리 균형화 후 (텍스트 출력)\n");
    btv_balance(head, &num, sizeof(wcount));
    btv_list(head->left, print_wcount);

    printf("\n▶ 그래픽 출력 (btv_draw)\n");
    btv_draw(head->left, make_str, LINK | NODE | TAIL);
    system("PAUSE");
}
