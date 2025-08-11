#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000
#define MAX 1000

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

void insert_sort(int* a, int N)
{
    int i, j, t;
    for (i = 1; i < N; i++)
    {
        t = a[i];
        j = i;
        while (j > 0 && a[j - 1] > t)
        {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = t;
    }
}

void im_quick_sort(int* a, int N)
{
    int v, t;
    int i, j;
    int l, r;
    init_stack();
    l = 0;
    r = N - 1;
    push(r);
    push(l);

    while (!is_stack_empty()) {
        l = pop();
        r = pop();
        if (r - l + 1 > 200) // quick sort
        {
            t = rand() % N;
            v = a[t];
            a[t] = a[r];
            a[r] = v;

            i = l - 1;
            j = r;
            while (1) {
                while (a[++i] < v);
                while (a[--j] > v);
                if (i >= j) break;
                t = a[i];
                a[i] = a[j];
                a[j] = t;
            }

            t = a[i];
            a[i] = a[r];
            a[r] = t;

            // Push (four statements)
            push(i - 1); // 오른쪽 인덱스 of 왼쪽 영역
            push(l);     // 왼쪽 인덱스 of 왼쪽 영역
            push(r);     // 오른쪽 인덱스 of 오른쪽 영역
            push(i + 1); // 왼쪽 인덱스 of 오른쪽 영역
        }
        else
            insert_sort(a + l, r - l + 1);  // 작은 영역 → 삽입 정렬
    }
}

void main()
{
    int number[SIZE];
    int i;

    srand(time(NULL));  // 현재 시간으로 시드 설정

    // 0부터 99 사이의 무작위 수 생성
    for (i = 0; i < SIZE; i++) {
        number[i] = rand() % 1000;
    }

    im_quick_sort(number, SIZE);

    for (i = 0; i < SIZE; i++) {
        printf("%4d ", number[i]);
    }
    printf("\n");
}