#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
    int dir;
} Data;

typedef struct Node {
    Data data;
    struct Node* next;
} Node;

Node* top = NULL;

void init_stack(void) {
    top = NULL;
}

void push(Data new) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = new;
    newNode->next = top;
    top = newNode;
}

Data pop() {
    if (top == NULL) {
        printf("Stack underflow!\n");
        return (Data) { -1, -1, -1 };
    }
    Node* temp = top;
    Data popped = temp->data;
    top = top->next;
    free(temp);
    return popped;
}

int is_empty() {
    return top == NULL;
}

int dx[8] = { -1, -1,  0, 1, 1,  1,  0, -1 };
int dy[8] = { 0,  1,  1, 1, 0, -1, -1, -1 }; 

void find_1(int location[15][15]) {
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
                int cx = x, cy = y;

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

                while (!is_empty()) {
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
