#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

void init_stack(void)
{
    top = -1;
}

void push(char c) {
    if (top < MAX - 1)
        stack[++top] = c;
}

char pop() {
    if (top == -1)
        return '\0';
    return stack[top--];
}

void postfix(char* dst, char* src)
{
    char c;
    init_stack();

    while (*src) {
        if (*src == ')')
        {
            *dst++ = pop();
            *dst++ = ' ';
            src++;  // move to next character
        }
        else if (*src == '+' || *src == '-' || *src == '*' || *src == '/')
        {
            push(*src);          // 연산자 스택에 저장
            src++;
        }
        else if (*src >= '0' && *src <= '9')
        {
            do {
                *dst++ = *src++; // 숫자를 복사
            } while (*src >= '0' && *src <= '9');
            *dst++ = ' ';        // 숫자 구분 공백
        }
        else
            src++;
    }
    *dst = 0;
}

void main() {
    char exp[256];
    char src[256] = "(1 + (2 * 3))";
    postfix(exp, src);
    printf("Postfix representation : % s\n", exp);
}