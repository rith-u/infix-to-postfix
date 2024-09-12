#include <stdio.h>
#include <ctype.h>
#include <math.h>
#define MAX 100

int top = -1;
char stack[MAX];

void push(int x)
{
    if (top == MAX - 1)
    {
        printf("Stack Overflow\n");
    }
    else
    {
        top++;
        stack[top] = x;
    }
}

char pop()
{
    if (top == -1)
    {
        printf("Stack Underflow\n");
        return '\0';
    }
    else
    {
        int x = stack[top];
        top--;
        return x;
    }
}
int isOp(char x)
{
    return (x == '+' || x == '-' || x == '*' || x == '/' || x == '^');
}

int precedence(char op)
{
    if (op == '^')
        return 3;
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

int isLeftAssoc(char op)
{
    if (op == '^')
        return 0;
    return 1;
}

void infixToPostfix(char *exp)
{
    char postfix[MAX];
    int k = 0;
    for (int i = 0; exp[i] != '\0'; i++)
    {
        char ch = exp[i];
        if (isalnum(ch))
        {
            postfix[k++] = ch;
        }
        else if (ch == '(')
        {
            push(ch);
        }
        else if (ch == ')')
        {
            while (top != -1 && stack[top] != '(')
            {
                postfix[k++] = pop();
            }
            pop();
        }
        else if (isOp(ch))
        {
            while (top != -1 && (precedence(stack[top]) > precedence(ch) ||
                                 (precedence(stack[top]) == precedence(ch) && isLeftAssoc(ch))))
            {
                postfix[k++] = pop();
            }

            push(ch);
        }
    }
    while (top != -1)
    {
        postfix[k++] = pop();
    }
    postfix[k] = '\0';
    printf("%s\n", postfix);
}

int main()
{
    printf("Enter the infix expression: \n");
    char exp[MAX];
    scanf("%s", exp);
    infixToPostfix(exp);
    return 0;
}