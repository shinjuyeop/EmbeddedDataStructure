#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

void shell_sort(int *a, int N)
{
	int i, j, k, h, v;
	for (h = N / 2; h > 0; h /= 2) {
		for (i = 0; i < h; i++) {
			for (j = i + h; j < N; j += h) {
				v = a[j];
				k = j;
				while (k > h - 1 && a[k - h] > v) {
					a[k] = a[k - h];
					k -= h;
				}
				a[k] = v;
			}
		}
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

	shell_sort(number, SIZE);

	for (i = 0; i < SIZE; i++) {
		printf("%4d ", number[i]);
	}
	printf("\n");
}

