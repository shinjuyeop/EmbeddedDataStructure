#include <stdio.h>

#define MAX 10

int stack[MAX];
int top;

void init_stack(void)
{
    top = -1;
}

int push(int t)
{
    if (top >= MAX - 1)
    {
        printf("Stack overflow !!!\n");
        return -1;
    }

    stack[++top] = t;
    return t;
}

int pop()
{
    if (top < 0)
    {
        printf("Stack underflow !!\n");
        return -1;
    }

    return stack[top--];
}

void print_stack()
{
    if (top < 0)
    {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack (top to bottom): ");
    for (int i = top; i >= 0; i--)
    {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

void main()
{
    int k;
    init_stack();

    // 1. Push 3, 6, 9, 1, 6, 3 and print
    push(3);
    push(6);
    push(9);
    push(1);
    push(6);
    push(3);
    printf("After pushing 3,6,9,1,6,3:\n");
    print_stack();

    // 2. Conduct pop and print
    k = pop();
    printf("Popped: %d\n", k);
    print_stack();

    // 3. Push 4, 8, 7, 2, 0 (may cause overflow)
    push(4);
    push(8);
    push(7);
    push(2);
    push(0); // 최대 한도를 넘으면 overflow 발생
    printf("After pushing 4,8,7,2,0:\n");
    print_stack();

    // 4. Initialize your stack
    init_stack();
    printf("After reinitializing the stack:\n");
    print_stack();

    // 5. Conduct pop (should cause underflow)
    k = pop();
    printf("Popped after reset: %d\n", k);
}
