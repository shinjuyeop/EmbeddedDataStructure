#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) {
    if (top < MAX - 1)
        stack[++top] = c;
}

char pop() {
    if (top == -1)
        return '\0';
    return stack[top--];
}

char peek() {
    if (top == -1)
        return '\0';
    return stack[top];
}

int precedence(char op) {
    if (op == '(') return 0;
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return -1;
}

void infix_to_postfix(const char *expr) {
    char c;
    for (int i = 0; (c = expr[i]) != '\0'; i++) {
        if (isspace(c)) continue;

        if (isalpha(c)) {
            printf("%c", c);  // 피연산자는 바로 출력
        }
        else if (c == '(') {
            push(c);
        }
        else if (c == ')') {
            while (peek() != '(') {
                printf("%c", pop());
            }
            pop(); // '(' 버림
        }
        else { // 연산자 처리
            while (precedence(peek()) >= precedence(c)) {
                printf("%c", pop());
            }
            push(c);
        }
    }

    // 남은 연산자 출력
    while (top != -1) {
        printf("%c", pop());
    }

    printf("\n");
}

int main() {
    const char *expr = "A+((B+C)/(D-E))";
    printf("Infix:   %s\n", expr);
    printf("Postfix: ");
    infix_to_postfix(expr);  // 결과: ABC+DE-/+
    return 0;
}
