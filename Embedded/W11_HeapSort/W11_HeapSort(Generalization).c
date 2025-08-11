#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 10

int intcmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void gen_upheap(void* base, int k, size_t size, int (*cmp)(const void*, const void*)) {
    void* v = malloc(size);
    memcpy(v, (char*)base + k * size, size);
    while (k > 1 && cmp((char*)base + (k / 2) * size, v) < 0) {
        memcpy((char*)base + k * size, (char*)base + (k / 2) * size, size);
        k /= 2;
    }
    memcpy((char*)base + k * size, v, size);
    free(v);
}

void gen_downheap(void* base, int N, int k, size_t size, int (*cmp)(const void*, const void*)) {
    void* v = malloc(size);
    memcpy(v, (char*)base + k * size, size);
    int i;
    while (k <= N / 2) {
        i = 2 * k;
        if (i < N && cmp((char*)base + i * size, (char*)base + (i + 1) * size) < 0)
            i++;
        if (cmp(v, (char*)base + i * size) >= 0)
            break;
        memcpy((char*)base + k * size, (char*)base + i * size, size);
        k = i;
    }
    memcpy((char*)base + k * size, v, size);
    free(v);
}

void gen_insert(void* base, int* N, void* elem, size_t size, int (*cmp)(const void*, const void*)) {
    memcpy((char*)base + (++(*N)) * size, elem, size);
    gen_upheap(base, *N, size, cmp);
}

int gen_extract(void* base, int* N, void* out, size_t size, int (*cmp)(const void*, const void*)) {
    if (*N < 1) return -1;
    memcpy(out, (char*)base + 1 * size, size);
    memcpy((char*)base + 1 * size, (char*)base + (*N) * size, size);
    (*N)--;
    gen_downheap(base, *N, 1, size, cmp);
    return 0;
}

void gen_heap_sort_topdown(void* base, int N, size_t size, int (*cmp)(const void*, const void*)) {
    void* heap = malloc(size * (N + 1));  // heap[1]~heap[N]
    int heap_size = 0;

    for (int i = 1; i <= N; i++)
        gen_insert(heap, &heap_size, (char*)base + i * size, size, cmp);

    for (int i = N; i >= 1; i--)
        gen_extract(heap, &heap_size, (char*)base + i * size, size, cmp);

    free(heap);
}

void gen_heap_sort_bottomup(void* base, int N, size_t size, int (*cmp)(const void*, const void*)) {
    for (int k = N / 2; k >= 1; k--)
        gen_downheap(base, N, k, size, cmp);

    void* temp = malloc(size);
    while (N > 1) {
        memcpy(temp, (char*)base + 1 * size, size);
        memcpy((char*)base + 1 * size, (char*)base + N * size, size);
        memcpy((char*)base + N * size, temp, size);
        N--;
        gen_downheap(base, N, 1, size, cmp);
    }
    free(temp);
}

int main() {
    int number[SIZE + 1];
    int top_sorted[SIZE + 1];
    int bot_sorted[SIZE + 1];

    srand((unsigned)time(NULL));

    for (int i = 1; i <= SIZE; i++)
        number[i] = rand() % 100;

    memcpy(top_sorted, number, sizeof(number));
    memcpy(bot_sorted, number, sizeof(number));

    printf("Original array:\n");
    for (int i = 1; i <= SIZE; i++)
        printf("%3d ", number[i]);
    printf("\n");

    gen_heap_sort_topdown(top_sorted, SIZE, sizeof(int), intcmp);
    printf("After Top-Down Heap Sort:\n");
    for (int i = 1; i <= SIZE; i++)
        printf("%3d ", top_sorted[i]);
    printf("\n");

    gen_heap_sort_bottomup(bot_sorted, SIZE, sizeof(int), intcmp);
    printf("After Bottom-Up Heap Sort:\n");
    for (int i = 1; i <= SIZE; i++)
        printf("%3d ", bot_sorted[i]);
    printf("\n");

    return 0;
}
