#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>  // INT_MAX 사용을 위해
#include <string.h>  // memcpy 사용 위해 추가

#define SIZE 10

void upheap(int* a, int k)
{
	int v;
	v = a[k];
	a[0] = INT_MAX;
	while (a[k / 2] <= v) {
		a[k] = a[k / 2];
		k /= 2;
	}
	a[k] = v;
}

void downheap(int* a, int N, int k)
{
	int i, v;
	v = a[k];
	while (k <= N / 2) {
		i = k << 1;
		if (i < N && a[i] < a[i + 1]) i++;
		if (v >= a[i]) break;
		a[k] = a[i];
		k = i;
	}
	a[k] = v;
}

void insert(int* a, int* N, int v)
{
	a[++(*N)] = v;
	upheap(a, *N);
}

int extract(int* a, int* N)
{
	int v = a[1];
	a[1] = a[(*N)--];
	downheap(a, *N, 1);

	return v;
}

void heap_sort(int* a, int N)
{
	int i;
	int hn = 0; // # of heap nodes

	for (i = 1; i <= N; i++)
		insert(a, &hn, a[i]);

	for (i = hn; i >= 1; i--)
		a[i] = extract(a, &hn);
}

void main()
{
	int number[SIZE + 1];
	int sorted[SIZE + 1];  // 복사본
	srand(time(NULL));

	for (int i = 1; i <= SIZE; i++) {
		number[i] = rand() % 100;
	}

	// 복사
	memcpy(sorted, number, sizeof(int) * (SIZE + 1));

	printf("Before sort (original number[]):\n");
	for (int i = 1; i <= SIZE; i++) {
		printf("%4d ", number[i]);
	}
	printf("\n");

	heap_sort(sorted, SIZE);  // 복사본에 대해 힙 정렬

	printf("After sort (sorted[]):\n");
	for (int i = 1; i <= SIZE; i++) {
		printf("%4d ", sorted[i]);
	}
	printf("\n");

	// number[]는 여전히 원본 상태 그대로 유지됨
}
