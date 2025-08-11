#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

void quick_sort(int* a, int N)
{
    int v, t;
    int i, j;
    if (N > 1) // termination
    {
        v = a[N - 1];  // pivot
        i = -1;
        j = N - 1;

        while (1)
        {
            while (a[++i] < v);
            while (a[--j] > v);
            if (i >= j) break;

            t = a[i];
            a[i] = a[j];
            a[j] = t;
        }

        t = a[i];
        a[i] = a[N - 1];
        a[N - 1] = t;

        quick_sort(a, i);                 // 왼쪽 부분 정렬
        quick_sort(a + i + 1, N - i - 1); // 오른쪽 부분 정렬
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

    quick_sort(number, SIZE);

    for (i = 0; i < SIZE; i++) {
        printf("%4d ", number[i]);
    }
    printf("\n");
}
