#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

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

void indirect_insert_sort(int* a, int* index, int N)
{
    int i, j, t;
    for (i = 0; i < N; i++)
        index[i] = i;  // a[i]의 원래 위치를 저장 (초기 인덱스)

    for (i = 1; i < N; i++)
    {
        t = index[i];
        j = i;
        while (j > 0 && a[index[j - 1]] > a[t])  // a[index[]]를 기준으로 비교
        {
            index[j] = index[j - 1];  // 인덱스를 앞으로 당김 (값은 그대로)
            j--;
        }
        index[j] = t;  // 삽입 위치에 t를 배치
    }
}

void main() 
{
	int number_1[SIZE];
	int number_2[SIZE];
	int index[SIZE];
	int i;

	srand(time(NULL));  // 랜덤 시드 설정

	// 무작위 숫자 생성 (0~99)
	for (i = 0; i < SIZE; i++) {
		number_1[i] = rand() % 100;
		number_2[i] = number_1[i];  // 같은 데이터 복사
	}

	printf("Original:       ");
	for (i = 0; i < SIZE; i++) {
		printf("%2d ", number_1[i]);
	}
	printf("\n");

	insert_sort(number_1, SIZE);
	printf("Direct Sorted:  ");
	for (i = 0; i < SIZE; i++) {
		printf("%2d ", number_1[i]);
	}
	printf("\n");

	indirect_insert_sort(number_2, index, SIZE);
	printf("Indirect Sorted:");
	for (i = 0; i < SIZE; i++) {
		printf("%2d ", number_2[index[i]]);
	}
	printf("\n");
}