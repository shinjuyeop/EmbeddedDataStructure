#include <stdio.h>
#include <stdlib.h>

#define MAX 225

typedef struct {
    int x, y;
    int dir;
} Data;

Data stack[MAX];
int top = -1;

void init_stack(void)
{
    top = -1;
}

void push(Data new)
{
    if (top >= MAX - 1)
    {
        printf("Stack overflow !!!\n");
    }
    stack[++top] = new;
}

Data pop()
{
    if (top < 0)
    {
        printf("Stack underflow !!\n");
        return (Data) { -1, -1, -1 };
    }
    return stack[top--];
}

int dx[8] = { -1, -1,  0, 1, 1,  1,  0, -1 };  // x축(세로) 방향: 위에서 아래로
int dy[8] = { 0,  1,  1, 1, 0, -1, -1, -1 };  // y축(가로) 방향: 왼쪽에서 오른쪽으로

void find_1(int location[15][15])
{
    int label = 2;

    for (int x = 0; x < 15; x++) {
        for (int y = 0; y < 15; y++) {
            int found_1 = 0;
            for (int d = 0; d < 8; d++) {
                int nx = x + dx[d];
                int ny = y + dy[d];

                if (nx >= 0 && nx < 15 && ny >= 0 && ny < 15 && location[nx][ny] == 1) {
                    found_1 = 1;
                    break;
                }
            }
            if (found_1) {
                int cx = x;
                int cy = y;

                for (int d = 0; d < 8; d++) {
                    int nx = cx + dx[d];
                    int ny = cy + dy[d];

                    if (nx >= 0 && nx < 15 && ny >= 0 && ny < 15 && location[nx][ny] == 1) {
                        push((Data) { cx, cy, d });
                        location[nx][ny] = label;
                        cx = nx;
                        cy = ny;
                        break;
                    }
                }
                while (top >= 0) {
                    int found = 0;

                    for (int d = 0; d < 8; d++) {
                        int nx = cx + dx[d];
                        int ny = cy + dy[d];

                        if (nx >= 0 && nx < 15 && ny >= 0 && ny < 15 && location[nx][ny] == 1) {
                            push((Data) { cx, cy, d });
                            location[nx][ny] = label;
                            cx = nx;
                            cy = ny;
                            found = 1;
                            break;
                        }
                    }
                    if (!found) {
                        Data before = pop();
                        cx = before.x;
                        cy = before.y;
                    }
                }
                label++;
            }
        }
    }
}

int input_map[15][15] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0},
        {0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

void main(void) {
    
    find_1(input_map);

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            printf("%2d ", input_map[i][j]);
        }
        printf("\n");
    }
}
