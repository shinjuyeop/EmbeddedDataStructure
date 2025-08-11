#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define SIZE 10

int intcmp(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}

// 뒤를 다 보고 최솟값 변경 후 넘어가기
void gen_select_sort(void* base, int nelem, int width,
	int (*fcmp)(const void*, const void*))
{
	void* min;
	int min_idx;
	int x, y;
	min = malloc(width);
	for (y = 0; y < nelem - 1; y++)		//  마지막은 어차피 맞춰짐
	{
		min_idx = y;
		memcpy(min, (char*)base + y * width, width);
		for (x = y + 1; x < nelem; x++)
		{
			if (fcmp(min, (char*)base + x * width) > 0)
			{
				memcpy(min, (char*)base + x * width, width);
				min_idx = x;
			}
		}
		memcpy((char*)base + min_idx * width, (char*)base + y * width, width);
		memcpy((char*)base + y * width, min, width);
	}
	free(min);
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

	gen_select_sort(number, SIZE, sizeof(int), intcmp);

	for (i = 0; i < SIZE; i++) {
		printf("%4d ", number[i]);
	}
	printf("\n");
}

