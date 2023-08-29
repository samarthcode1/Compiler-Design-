#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
#define Max_String 5
int height_of_tree;

typedef struct AST
{
    char symbol[Max_String];
    struct AST *lchild;
    struct AST *rchild;
} AST;

bool checkOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

AST *ASTNode(char symbol[])
{
    AST *node = (AST *)malloc(sizeof(AST));
    strcpy(node->symbol, symbol);
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

AST *ExpTree(char *expression, int first, int last)
{
    char symbol[Max_String];
    strcpy(symbol, "\0");
    if (first > last)
        return NULL;
    int precedenceIndex = -1;
    int leastPrecedence = 999;
    for (int i = first; i <= last; i++)
    {
        if (checkOperator(expression[i]))
        {
            int precedence;
            if (expression[i] == '+' || expression[i] == '-')
                precedence = 1;
            else
                precedence = 2;
            if (precedence <= leastPrecedence)
            {
                leastPrecedence = precedence;
                precedenceIndex = i;
            }
        }
    }
    if (precedenceIndex != -1)
    {
        symbol[0] = expression[precedenceIndex];
        symbol[1] = '\0';
        AST *root = ASTNode(symbol);
        root->lchild = ExpTree(expression, first, precedenceIndex - 1);
        root->rchild = ExpTree(expression, precedenceIndex + 1, last);
        return root;
    }
    int value = 0;
    for (int i = first; i <= last; i++)
    {
        if (expression[i] >= '0' && expression[i] <= '9')
        {
            value = value * 10 + (expression[i] - '0');
        }
    }
    sprintf(symbol, "%d", value);
    return ASTNode(symbol);
}

int calculateHeight(AST *root)
{
    if (root == NULL){
        return 0;
    }
    return max(calculateHeight(root->lchild), calculateHeight(root->rchild)) + 1;
}

void presentLevel(AST *root, int level)
{
    if (root == NULL)
    {
        cout << "\b";
        return;
    }
    if (level == 1)
    {
        cout << " ";
        cout << root->symbol;
    }
    else if (level > 1)
    {
        presentLevel(root->lchild, level - 1);
        for (int j = height_of_tree; j > level; j--)
            cout << " ";
        presentLevel(root->rchild, level - 1);
        for (int j = height_of_tree; j > level + 1; j--)
            cout << " ";
    }
}

void levelOrder(AST *root)
{
    height_of_tree = calculateHeight(root);
    for (int i = 1; i <= height_of_tree; i++)
    {
        for (int j = 0; j < height_of_tree - i; j++)
            cout << " ";
        presentLevel(root, i);
            cout << "\n";
    }
}

void threeAC(char expr[])
{
    char code[100][100];
    int tempCount = 1;
    int f = 0, e, j, k = 0;
    char num[5];
    int i = 0;
    while (strchr(expr, '*') != NULL || strchr(expr, '/') != NULL)
    {
        if (expr[i] == '*' || expr[i] == '/')
        {
            for (j = i - 1; j >= 0; j--)
            {
                if (checkOperator(expr[j]))
                    break;
            }
            if (j != -1)
                f = j + 1;
            else
                f = 0;
            for (j = i + 1; j < strlen(expr); j++)
            {
                if (checkOperator(expr[j]))
                    break;
            }
            if (j != strlen(expr))
                e = j - 1;
            else
                e = strlen(expr) - 1;
            code[k][0] = 't';
            sprintf(num, "%d", tempCount);
            tempCount++;
            strcat(code[k], num);
            code[k][strlen(num) + 1] = '=';
            for (j = 0; j < e - f + 1; j++)
                code[k][strlen(num) + 2 + j] = expr[f + j];
            cout << code[k] << "\n";

            expr[f] = 't';
            for (j = 0; j < strlen(num); j++)
                expr[f + j + 1] = num[j];
            for (j = e + 1; j < strlen(expr); j++)
                expr[f + (j - e) + strlen(num)] = expr[j];
            expr[f + (j - e) + strlen(num)] = '\0';
            i = f;
            k++;
        }
        i++;
    }
    i = 0;
    while (strchr(expr, '+') != NULL || strchr(expr, '-') != NULL)
    {
        if (expr[i] == '+' || expr[i] == '-')
        {
            for (j = i - 1; j >= 0; j--)
            {
                if (checkOperator(expr[j]))
                    break;
            }
            if (j != -1)
                f = j + 1;
            else
                f = 0;
            for (j = i + 1; j < strlen(expr); j++)
            {
                if (checkOperator(expr[j]))
                    break;
            }
            if (j != strlen(expr))
                e = j - 1;
            else
                e = strlen(expr) - 1;
            code[k][0] = 't';
            sprintf(num, "%d", tempCount);
            tempCount++;
            strcat(code[k], num);
            code[k][strlen(num) + 1] = '=';
            for (j = 0; j < e - f + 1; j++)
                code[k][strlen(num) + 2 + j] = expr[f + j];
            cout << code[k] << "\n";
            expr[f] = 't';
            for (j = 0; j < strlen(num); j++)
                expr[f + j + 1] = num[j];
            for (j = e + 1; j < strlen(expr); j++)
                expr[f + (j - e) + strlen(num)] = expr[j];
            expr[f + (j - e) + strlen(num)] = '\0';
            i = f;
            k++;
        }
        i++;
    }
}

int main()
{
    char expression[1000];
    int n;
    cout << "Enter the length of the expression\n";
    cin >> n;
    cout << "Enter the Expression(Infix): ";
    for (int i = 0; i < n; i++)
    {
        cin >> expression[i];
    }
    expression[strcspn(expression, "\n")] = '\0';
    AST *root = ExpTree(expression, 0, strlen(expression) - 1);
    cout << "Abstract Syntax tree\n ";
    levelOrder(root);
    cout << "Three Address Code for the Given Expression\n";
    threeAC(expression);
    cout<<"21BCT0157";
    return 0;
}