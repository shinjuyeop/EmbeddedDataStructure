#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

void select_sort(int* a, int N)
{
	int min;
	int min_idx;
	int x, y;
	for (y = 0; y < N - 1; y++) {
		min_idx = y;
		min = a[y];
		for (x = y + 1; x < N; x++) {
			if (min > a[x]) {
				min = a[x];
				min_idx = x;
			}
		}
		a[min_idx] = a[y];
		a[y] = min;
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

	select_sort(number, SIZE);

	for (i = 0; i < SIZE; i++) {
		printf("%4d ", number[i]);
	}
	printf("\n");
}