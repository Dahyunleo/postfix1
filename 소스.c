#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STACK_SIZE 100

typedef struct {
    int top;
    int items[STACK_SIZE];
} Stack;

void push(Stack* s, int val) {
    if (s->top >= STACK_SIZE) {
        fprintf(stderr, "Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    s->items[++s->top] = val;
}

int pop(Stack* s) {
    if (s->top < 0) {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return s->items[s->top--];
}

int evaluate_postfix(char* postfix) {
    Stack s = { .top = -1 };

    for (int i = 0; postfix[i]; i++) {
        if (isdigit(postfix[i])) {
            push(&s, postfix[i] - '0');
        }
        else {
            int op2 = pop(&s);
            int op1 = pop(&s);
            int result;
            switch (postfix[i]) {
            case '+':
                result = op1 + op2;
                break;
            case '-':
                result = op1 - op2;
                break;
            case '*':
                result = op1 * op2;
                break;
            case '/':
                result = op1 / op2;
                break;
            default:
                fprintf(stderr, "Unknown operator %c\n", postfix[i]);
                exit(EXIT_FAILURE);
            }
            push(&s, result);
        }
    }

    if (s.top != 0) {
        fprintf(stderr, "Invalid expression\n");
        exit(EXIT_FAILURE);
    }

    return pop(&s);
}

int main() {
    char postfix[STACK_SIZE];
    printf("Postfix expression: ");
    fgets(postfix, STACK_SIZE, stdin);
    postfix[strcspn(postfix, "\n")] = 0;

    int result = evaluate_postfix(postfix);
    printf("Result: %d\n", result);

    return 0;
}
