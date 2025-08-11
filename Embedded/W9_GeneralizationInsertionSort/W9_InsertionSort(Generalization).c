#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define SIZE 10

int intcmp(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

int floatcmp(const void* a, const void* b)
{
    float x = *(float*)a;
    float y = *(float*)b;
    return (x > y) - (x < y);  // 부동소수점 비교는 이렇게
}

int strcmp_fn(const void* a, const void* b)
{
    const char* s1 = *(const char**)a;
    const char* s2 = *(const char**)b;
    return strcmp(s1, s2);
}

//구조체(ex : 점수)
typedef struct {
    char name[20];
    int score;
} Student;

int scorecmp(const void* a, const void* b)
{
    const Student* s1 = (const Student*)a;
    const Student* s2 = (const Student*)b;
    return (s1->score > s2->score) - (s1->score < s2->score);
}


void gen_insert_sort(void* base, size_t nelem, size_t width,
    int (*fcmp)(const void*, const void*))
{
    // base : array의 첫 번째 항 주소
    // nelem : array의 항의 개수 (요소)
    // width : 항의 바이트 길이
    // fcmp : 비교 함수

    int i, j;
    void* t = malloc(width);    //t에 메모리 할당
    char* b = (char*)base;      //b는 base(array)의 주소

    for (i = 1; i < nelem; i++) {
        memcpy(t, b + i * width, width); // base[1]부터 진행 base[nelem-1]까지
        j = i;

        while (j > 0 && fcmp(b + (j - 1) * width, t) > 0)       // base[t]가 바로 앞 숫자보다 작으면
        {
            memcpy(b + j * width, b + (j - 1) * width, width); // 뒷 숫자에 앞 숫자 넣음
            j--; //j를 줄이면서 앞으로 나아감
        }

        memcpy(b + j * width, t, width); //base[j] 자리에 base[t] 저장 
    }

    free(t);
}

void main()
{
    int number[SIZE];
    int i;

    srand(time(NULL));  // 현재 시간으로 시드 설정

    // 정수 정렬 테스트
    for (i = 0; i < SIZE; i++) {
        number[i] = rand() % 1000;
    }

    gen_insert_sort(number, SIZE, sizeof(int), intcmp);

    printf("Sorted integers:\n");
    for (i = 0; i < SIZE; i++) {
        printf("%4d ", number[i]);
    }
    printf("\n");

    // 실수 정렬 테스트
    float fnumber[SIZE];
    for (i = 0; i < SIZE; i++) {
        fnumber[i] = (float)(rand() % 10000) / 100.0f;  // 0.00 ~ 99.99
    }

    gen_insert_sort(fnumber, SIZE, sizeof(float), floatcmp);

    printf("Sorted floats:\n");
    for (i = 0; i < SIZE; i++) {
        printf("%6.2f ", fnumber[i]);
    }
    printf("\n");

}
