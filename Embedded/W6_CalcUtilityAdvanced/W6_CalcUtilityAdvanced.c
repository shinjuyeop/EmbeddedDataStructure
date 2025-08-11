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

int is_stack_empty() {
    return top == -1;
}

// 스택의 top에 있는 값을 반환 (비어있으면 -1 반환)
int get_stack_top()
{
    return (top < 0) ? -1 : stack[top];
}

// 주어진 문자가 연산자인지 확인
int is_op(int k)
{
    return (k == '+' || k == '-' || k == '*' || k == '/');
}

// 연산자의 우선순위를 반환
int precedence(int op)
{
    if (op == '(')
        return 0;
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    else
        return 3;
}

void postfix(char* dst, char* src)
{
    char c;
    init_stack();
    while (*src) {
        if (*src == '(') {
            push(*src);
            src++;
        }
        else if (*src == ')') {
            while (get_stack_top() != '(') {
                *dst++ = pop();
                *dst++ = ' ';
            }
            pop(); // ← 이 부분이 빈칸입니다! '(' 버리기
            src++;
        }
        else if (is_op(*src)) {
            while (!is_stack_empty() &&
                precedence(get_stack_top()) >= precedence(*src)) { // ← 이 부분이 빈칸입니다!
                *dst++ = pop();
                *dst++ = ' ';
            }
            push(*src); // ← 연산자 푸시 (빈칸)
            src++;
        }
        else if (*src >= '0' && *src <= '9') {
            do {
                *dst++ = *src++;
            } while (*src >= '0' && *src <= '9');
            *dst++ = ' ';
        }
        else {
            src++;
        }
    }

    while (!is_stack_empty()) {
        *dst++ = pop();
        *dst++ = ' ';
    }
    dst--;
    *dst = 0;
}

void main() {
    char exp[256];
    char src[256] = "(1*(2+3/4)+5)/6+7";
    postfix(exp, src);
    printf("Postfix representation : %s\n", exp);
}