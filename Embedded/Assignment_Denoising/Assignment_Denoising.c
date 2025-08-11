#include <stdio.h>
#include <stdlib.h>
#define W 7 // any odd number

void read_file(int* input, int height, int width, char filename[])
{
	int x, y;
	FILE* fp;
	fp = fopen(filename, "r");
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			fscanf(fp, "%d", &input[y * width + x]);
		}
		fscanf(fp, "\n");
	}
	fclose(fp);
}

void insertion_sort(int* a, int N)
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

/*
void median_filtering(int *input, int *output, int height, int width)
{
	int half = W / 2;
	int window[W * W];

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (i < half || i >= height - half || j < half || j >= width - half) {
				output[i * width + j] = input[i * width + j]; // Out of Boundary 처리(현재 값 그대로 적용)
				continue;
			}
			for (int y = 0; y < W; y++) {
				for (int x = 0; x < W; x++) {
					window[y * W + x] = input[(i + y - half) * width + (j + x - half)];
				}
			}
			insertion_sort(window, W * W);
			output[i * width + j] = window[W * W / 2]; // 중앙 값으로 대체
		}
	}
}
*/

void median_filtering(int* input, int* output, int height, int width)
{
	int half = W / 2;
	int window[W * W];

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {

			int k = 0;
			for (int y = -half; y <= half; y++) {
				for (int x = -half; x <= half; x++) {
					int ny = i + y;
					int nx = j + x;
					if (ny < 0 || ny >= height || nx < 0 || nx >= width) {
						window[k++] = 0; //  zero padding
					}
					else {
						window[k++] = input[ny * width + nx];
					}
				}
			}

			insertion_sort(window, W * W);
			output[i * width + j] = window[W * W / 2];
		}
	}
}


void main()
{
	int height = 44, width = 45; // image width and height
	int* source;
	int* result;

	source = malloc(sizeof(int) * height * width);
	result = malloc(sizeof(int) * height * width);

	read_file(source, height, width,
		"C:\\Users\\shinj\\Desktop\\3-1\\EmbeddedDataStructure\\noisy_data.txt");

	median_filtering(source, result, height, width);

	printf("Source\n");
	for (int i = 0; i < height * width; i++) {
		if (i % width == 0) printf("\n");
		printf("%3d ", source[i]);
	}
	printf("\n\n");

	printf("Result\n");
	for (int i = 0; i < height * width; i++) {
		if (i % width == 0) printf("\n");
		printf("%3d ", result[i]);
	}
	printf("\n\n");

	free(source);
	free(result);
}

