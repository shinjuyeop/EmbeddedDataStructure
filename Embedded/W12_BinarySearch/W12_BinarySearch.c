/*
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

int bi_search(int key, int* a, int N)
{
	int mid;
	int left = 0;
	int right = N - 1;
	while (right >= left) {
		mid = (right + left) / 2;
		if (key == a[mid]) return mid;
		if (key < a[mid])
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1;
}

int bi_insert(int key, int* a, int* N)
{
	int p = 0;
	int i;
	while (key > a[p] && p < *N)
		p++;
	for (i = *N; i > p; i--)
		a[i] = a[i - 1];
	a[p] = key;
	(*N)++;
	return p;
}

int bi_delete(int key, int* a, int* N)
{
	int p;
	int i;
	if (*N > 0) {
		if ((p = bi_search(key, a, *N)) < 0)
			return -1;
		for (i = p + 1; i < *N; i++)
			a[i - 1] = a[i];
		(*N)--;
		return p;
	}
	return -1;
}

void main() {
	char str[20] = "TOSORTALGORITHM";
	int size = 15;

	// Conduct sorting a str array (e.g., quick / heap sort)
	heap_sort(str, size);

	// Find a specific character using binary search
	int p = bi_search('S', str, size);
	printf("Find your key at %d(value %c)\n", p, str[p]);

	// Insert and delete a specific character
	p = bi_insert('Z', str, &size); // or p = bi_delete('A', str, &size);
	printf("%s\n", str);
}
*/

#include <stdio.h>
#include <string.h>

#define SIZE 32

void swap(char* a, char* b) {
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

void upheap(char* a, int k) {
	char v = a[k];
	a[0] = 127; // 최대 char값
	while (a[k / 2] <= v) {
		a[k] = a[k / 2];
		k /= 2;
	}
	a[k] = v;
}

void downheap(char* a, int N, int k) {
	int i;
	char v = a[k];
	while (k <= N / 2) {
		i = k << 1;
		if (i < N && a[i] < a[i + 1]) i++;
		if (v >= a[i]) break;
		a[k] = a[i];
		k = i;
	}
	a[k] = v;
}

void insert(char* a, int* N, char v) {
	a[++(*N)] = v;
	upheap(a, *N);
}

char extract(char* a, int* N) {
	char v = a[1];
	a[1] = a[(*N)--];
	downheap(a, *N, 1);
	return v;
}

void heap_sort(char* a, int N) {
	char heap[SIZE];
	int hn = 0;
	int i;

	for (i = 0; i < N; i++)
		insert(heap, &hn, a[i]);

	for (i = N - 1; i >= 0; i--)
		a[i] = extract(heap, &hn);
}

int bi_search(char key, char* a, int N) {
	int left = 0, right = N - 1, mid;
	while (left <= right) {
		mid = (left + right) / 2;
		if (a[mid] == key) return mid;
		if (key < a[mid]) right = mid - 1;
		else left = mid + 1;
	}
	return -1;
}

int bi_insert(char key, char* a, int* N) {
	if (*N >= SIZE - 1) return -1; // overflow 방지
	int p = 0, i;
	while (p < *N && key > a[p]) p++;
	for (i = *N; i > p; i--) a[i] = a[i - 1];
	a[p] = key;
	(*N)++;
	return p;
}

int bi_delete(char key, char* a, int* N) {
	int p = bi_search(key, a, *N);
	if (p < 0) return -1;
	for (int i = p + 1; i < *N; i++)
		a[i - 1] = a[i];
	(*N)--;
	return p;
}

int main() {
	char str[SIZE] = "TOSORTALGORITHM";
	int size = strlen(str);

	heap_sort(str, size);

	int p = bi_search('S', str, size);
	if (p != -1)
		printf("Find your key at %d (value %c)\n", p, str[p]);
	else
		printf("Key not found\n");

	bi_insert('Z', str, &size);
	printf("After insert: %.*s\n", size, str);

	bi_delete('A', str, &size);
	printf("After delete: %.*s\n", size, str);

	return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*FCMP)(const void*, const void*);

int gen_bi_search(void* key, void* base, int N, size_t width, FCMP cmp) {
	int left = 0, right = N - 1, mid;
	char* arr = (char*)base;

	while (left <= right) {
		mid = (left + right) / 2;
		void* elem = arr + mid * width;
		int result = cmp(key, elem);
		if (result == 0) return mid;
		if (result < 0) right = mid - 1;
		else left = mid + 1;
	}
	return -1;
}

int intcmp(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}

int charcmp(const void* a, const void* b) {
	return (*(char*)a - *(char*)b);
}

int main() {
	// 예제 1: int 배열
	int arr[] = { 10, 20, 30, 40, 50 };
	int key = 30;
	int idx = gen_bi_search(&key, arr, 5, sizeof(int), intcmp);
	if (idx != -1)
		printf("int: Found %d at index %d\n", key, idx);
	else
		printf("int: %d not found\n", key);

	// 예제 2: char 배열
	char str[] = "ACDEFG";
	char ch = 'E';
	idx = gen_bi_search(&ch, str, strlen(str), sizeof(char), charcmp);
	if (idx != -1)
		printf("char: Found %c at index %d\n", ch, idx);
	else
		printf("char: %c not found\n", ch);

	return 0;
}
*/