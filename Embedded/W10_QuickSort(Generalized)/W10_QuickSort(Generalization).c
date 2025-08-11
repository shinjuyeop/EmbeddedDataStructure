#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define SIZE 10
#define MAX 10

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


void gen_quick_sort(void* base, int N, int width, int (*fcmp)(const void*, const void*)) {
    int i, j;
    void* pivot, * t, * left, * right;

    if (N > 1) {
        pivot = malloc(width);
        t = malloc(width);
        memcpy(pivot, (char*)base + (N - 1) * width, width);  // pivot = a[N - 1]

        i = -1;
        j = N - 1;

        while (1) {
            do { i++; } while (fcmp((char*)base + i * width, pivot) < 0);
            do { j--; } while (fcmp((char*)base + j * width, pivot) > 0);

            if (i >= j) break;

            // swap a[i] <-> a[j]
            left = (char*)base + i * width;
            right = (char*)base + j * width;
            memcpy(t, left, width);
            memcpy(left, right, width);
            memcpy(right, t, width);
        }

        // swap a[i] <-> a[N - 1]
        left = (char*)base + i * width;
        right = (char*)base + (N - 1) * width;
        memcpy(t, left, width);
        memcpy(left, right, width);
        memcpy(right, t, width);

        // recursive calls
        gen_quick_sort(base, i, width, fcmp);
        gen_quick_sort((char*)base + (i + 1) * width, N - i - 1, width, fcmp);

        free(pivot);
        free(t);
    }
}

int stack[MAX];
int top;

void init_stack(void)
{
    top = -1;
}

int push(int t)
{
    if (top >= MAX - 1)
    {
        printf("Stack overflow !!!\n");
        return -1;
    }

    stack[++top] = t;
    return t;
}

int pop()
{
    if (top < 0)
    {
        printf("Stack underflow !!\n");
        return -1;
    }

    return stack[top--];
}

int is_stack_empty() {
    return (top == -1);
}

void gen_nr_quick_sort(void* base, int N, int width, int (*fcmp)(const void*, const void*)) {
    void* pivot = malloc(width);
    void* temp = malloc(width);
    int i, j;
    int l, r;

    init_stack();           // 사용자 정의 정수형 스택
    push(N - 1);            // r
    push(0);                // l

    while (!is_stack_empty()) {
        l = pop();
        r = pop();

        if (r - l + 1 > 1) {
            void* vr = (char*)base + r * width;
            memcpy(pivot, vr, width);  // pivot = a[r]

            i = l - 1;
            j = r;

            while (1) {
                do { i++; } while (fcmp((char*)base + i * width, pivot) < 0);
                do { j--; } while (fcmp((char*)base + j * width, pivot) > 0);
                if (i >= j) break;

                void* pi = (char*)base + i * width;
                void* pj = (char*)base + j * width;
                memcpy(temp, pi, width);
                memcpy(pi, pj, width);
                memcpy(pj, temp, width);
            }

            void* pi = (char*)base + i * width;
            memcpy(temp, pi, width);
            memcpy(pi, vr, width);
            memcpy(vr, temp, width);

            // push right and left subarray
            push(i - 1); // right index of left subarray
            push(l);     // left index of left subarray

            push(r);     // right index of right subarray
            push(i + 1); // left index of right subarray
        }
    }

    free(pivot);
    free(temp);
}

void gen_insert_sort(void* base, size_t nelem, size_t width,
    int (*fcmp)(const void*, const void*))
{
    int i, j;
    void* t = malloc(width);
    char* b = (char*)base;

    for (i = 1; i < nelem; i++) {
        memcpy(t, b + i * width, width);
        j = i;

        while (j > 0 && fcmp(b + (j - 1) * width, t) > 0) {
            memcpy(b + j * width, b + (j - 1) * width, width);
            j--;
        }

        memcpy(b + j * width, t, width);
    }

    free(t);
}

void gen_im_quick_sort(void* base, int N, int width, int (*fcmp)(const void*, const void*)) {
    void* pivot = malloc(width);
    void* temp = malloc(width);
    int i, j;
    int l, r;

    init_stack();           // 너가 제공하는 스택 구현 사용
    push(N - 1);            // r
    push(0);                // l

    while (!is_stack_empty()) {
        l = pop();
        r = pop();

        if (r - l + 1 > 200) {
            // 랜덤 피벗 설정
            int t_index = rand() % N;
            void* t_ptr = (char*)base + t_index * width;
            void* r_ptr = (char*)base + r * width;
            memcpy(pivot, t_ptr, width);
            memcpy(t_ptr, r_ptr, width);
            memcpy(r_ptr, pivot, width);

            i = l - 1;
            j = r;

            while (1) {
                do { i++; } while (fcmp((char*)base + i * width, pivot) < 0);
                do { j--; } while (fcmp((char*)base + j * width, pivot) > 0);
                if (i >= j) break;

                void* pi = (char*)base + i * width;
                void* pj = (char*)base + j * width;

                memcpy(temp, pi, width);
                memcpy(pi, pj, width);
                memcpy(pj, temp, width);
            }

            void* pi = (char*)base + i * width;
            void* pr = (char*)base + r * width;

            memcpy(temp, pi, width);
            memcpy(pi, pr, width);
            memcpy(pr, temp, width);

            // Push: right & left 영역
            push(i - 1);  // 오른쪽 index of 왼쪽 영역
            push(l);      // 왼쪽 index of 왼쪽 영역
            push(r);      // 오른쪽 index of 오른쪽 영역
            push(i + 1);  // 왼쪽 index of 오른쪽 영역
        }
        else {
            gen_insert_sort((char*)base + l * width, r - l + 1, width, fcmp);
        }
    }

    free(pivot);
    free(temp);
}

void print_int_array(int* arr, int size) {
    for (int i = 0; i < size; i++) printf("%4d ", arr[i]);
    printf("\n");
}

void print_float_array(float* arr, int size) {
    for (int i = 0; i < size; i++) printf("%6.2f ", arr[i]);
    printf("\n");
}

int main()
{
    srand((unsigned int)time(NULL));  // 시드 설정

    int number[SIZE];
    float fnumber[SIZE];
    int i;

    // --------------------------------
    // gen_quick_sort 테스트
    // --------------------------------
    for (i = 0; i < SIZE; i++) number[i] = rand() % 1000;
    printf("[gen_quick_sort] Original integers:\n");
    print_int_array(number, SIZE);
    gen_quick_sort(number, SIZE, sizeof(int), intcmp);
    printf("[gen_quick_sort] Sorted integers:\n");
    print_int_array(number, SIZE);

    for (i = 0; i < SIZE; i++) fnumber[i] = (float)(rand() % 10000) / 100.0f;
    printf("[gen_quick_sort] Original floats:\n");
    print_float_array(fnumber, SIZE);
    gen_quick_sort(fnumber, SIZE, sizeof(float), floatcmp);
    printf("[gen_quick_sort] Sorted floats:\n");
    print_float_array(fnumber, SIZE);

    // --------------------------------
    // gen_nr_quick_sort 테스트
    // --------------------------------
    for (i = 0; i < SIZE; i++) number[i] = rand() % 1000;
    printf("[gen_nr_quick_sort] Original integers:\n");
    print_int_array(number, SIZE);
    gen_nr_quick_sort(number, SIZE, sizeof(int), intcmp);
    printf("[gen_nr_quick_sort] Sorted integers:\n");
    print_int_array(number, SIZE);

    for (i = 0; i < SIZE; i++) fnumber[i] = (float)(rand() % 10000) / 100.0f;
    printf("[gen_nr_quick_sort] Original floats:\n");
    print_float_array(fnumber, SIZE);
    gen_nr_quick_sort(fnumber, SIZE, sizeof(float), floatcmp);
    printf("[gen_nr_quick_sort] Sorted floats:\n");
    print_float_array(fnumber, SIZE);

    // --------------------------------
    // gen_im_quick_sort 테스트
    // --------------------------------
    for (i = 0; i < SIZE; i++) number[i] = rand() % 1000;
    printf("[gen_im_quick_sort] Original integers:\n");
    print_int_array(number, SIZE);
    gen_im_quick_sort(number, SIZE, sizeof(int), intcmp);
    printf("[gen_im_quick_sort] Sorted integers:\n");
    print_int_array(number, SIZE);

    for (i = 0; i < SIZE; i++) fnumber[i] = (float)(rand() % 10000) / 100.0f;
    printf("[gen_im_quick_sort] Original floats:\n");
    print_float_array(fnumber, SIZE);
    gen_im_quick_sort(fnumber, SIZE, sizeof(float), floatcmp);
    printf("[gen_im_quick_sort] Sorted floats:\n");
    print_float_array(fnumber, SIZE);

    return 0;
}
