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

int doublecmp(const void* a, const void* b)
{
    double x = *(double*)a;
    double y = *(double*)b;
    return (x > y) - (x < y);
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


void gen_shell_sort(void* base, size_t nelem, size_t width,
    int (*fcmp)(const void*, const void*))
{
    size_t i, j, k, h;
    void* temp = malloc(width);
    char* b = (char*)base;

    for (h = nelem / 2; h > 0; h /= 2) {
        for (i = 0; i < h; i++) {
            for (j = i + h; j < nelem; j += h) {
                memcpy(temp, b + j * width, width);
                k = j;
                while (k >= h && fcmp(b + (k - h) * width, temp) > 0) {
                    memcpy(b + k * width, b + (k - h) * width, width);
                    k -= h;
                }
                memcpy(b + k * width, temp, width);
            }
        }
    }

    free(temp);
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

    gen_shell_sort(number, SIZE, sizeof(int), intcmp);

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

    gen_shell_sort(fnumber, SIZE, sizeof(float), floatcmp);

    printf("Sorted floats:\n");
    for (i = 0; i < SIZE; i++) {
        printf("%6.2f ", fnumber[i]);
    }
    printf("\n");

}
