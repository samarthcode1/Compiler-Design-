// (i*i)+(i*i)+i
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *str;
char recentProd[6];
char stk[60];
int stk_top = 0, l;
char prec[9][9] ={
    //       +    -    *    /    ^    it    (    )   $ 
    /* + */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
    /* - */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
    /* * */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
    /* / */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
    /* ^ */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
    /* it */'>', '>', '>', '>', '>', 'e', 'e', '>', '>',
    /* ( */ '<', '<', '<', '<', '<', '<', '<', '>', 'e',
    /* ) */ '>', '>', '>', '>', '>', 'e', 'e', '>', '>',
    /* $ */ '<', '<', '<', '<', '<', '<', '<', '<', '>',
};
char set_of_production[][5] = {")E(", "E*E", "E+E", "i", "E^E"};
int it = 0;

int position(char c)
{
    if(c== '+')
        return 0;
    else if(c=='-')
        return 1;
    else if(c=='*')
        return 2;
    else if(c=='/')
        return 3;
    else if(c=='^')
        return 4;
    else if(c=='i')
        return 5;
    else if(c=='(')
        return 6;
    else if(c==')')
        return 7;
    else if(c=='$')
        return 8;
    else{
        return -1;
    }    
}

void showStack()
{
    for (int j = 0; j <= stk_top; j++){
        printf("%c", stk[j]);
    }
}

void showString()
{
    for (int j = it; j < l; j++){
        printf("%c", *(str + j));
    }
}

int push()
{
    stk[++stk_top] = *(str + it++);
    stk[stk_top + 1] = '\0';
}

int reduce()
{
    int size, matched, t;
    for (int it = 0; it < 5; it++)
    {
        size = strlen(set_of_production[it]);
        if (stk[stk_top] == set_of_production[it][0] && stk_top + 1 >= size)
        {
            matched = 1;
            for (t = 0; t < size; t++)
            {
                if (stk[stk_top - t] != set_of_production[it][t])
                {
                    matched = 0;
                    break;
                }
            }
            if (matched == 1)
            {
                stk[stk_top - t + 1] = 'E';
                stk_top = stk_top - t + 1;
                strcpy(recentProd, set_of_production[it]);
                stk[stk_top + 1] = '\0';
                return 1;
            }
        }
    }
    return 0;
}

int main()
{
    // int j;
    str = (char *)malloc(60 * sizeof(char));
    printf("Enter the Input String\n");
    scanf("%s", str);
    str = strcat(str, "$");
    l = strlen(str);
    strcpy(stk, "$");
    printf("Inside Stack \tInput String \tOperation");
    while (it <= l)
    {
        push();
        printf("\n");
        showStack();
        printf("\t");
        showString();
        printf("\tpush");
        if (prec[position(stk[stk_top])][position(str[it])] == '>')
        {
            while (reduce())
            {
                printf("\n");
                showStack();
                printf("\t");
                showString();
                printf("\tReduce: E->%s", recentProd);
            }
        }
    }
    if (strcmp(stk, "$E$") == 0){
        printf("\nHence the Given String is Accepted");
        printf("\n21BCT0157");
    }
    else{
        printf("\nHence the Given String is Not Accepted");
        printf("\n21BCT0157");
    }
    return 0;
}