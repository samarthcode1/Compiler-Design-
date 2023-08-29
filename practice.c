#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char *str;
char stk[60];
int stk_top=0,l;
char recentProd[6];
char prec[9][9]={
    //       +    -    *    /    ^    it    (    )    $ 
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

char set_of_production[][5]={")E(","E*E","E+E","i","E^E"};
int it=0;
int position(char c){
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
void showStack(){
    for(int j=0;j<=stk_top;j++){
        printf("%c",stk[j]);
    }
}
void showString(){
    for(int j=0;j<l;j++){
        printf("%c",*(str+j));
    }
}
int push(){
    stk[++stk_top]=*(str+it++);
    stk[stk_top+1]='\0';
}
int reduce(){
    int size,matched,t;
    for(int it=0;it<5;it++){
        size=strlen(set_of_production[it]);
        if(stk[stk_top]==set_of_production[it][0]&& stk_top+1>=size){
            matched=1;
            for(t=0;t<size;t++){
                if(str[stk_top-t]!=set_of_production[it][t]){
                    matched=0;
                    break;
                }
            }
            if(matched==1){
                stk[stk_top-t+1]='E';
                stk_top=stk_top-t+1;
                strcpy(recentProd,set_of_production[it]);
                stk[stk_top+1]='\0';
                return 1;
            }
        }
    }
    return 0;
}

int main(){
    int j;
    str=(char *)malloc(60*sizeof(char));
    printf("Enter the Input String\n");
    scanf("%s",str);
    str=strcat(str,"$");
    l=strlen(str);
    strcpy(stk,"$");
    printf("Inside stack \t Input String \t Operation");
    while(it<=l){
        push();
        printf("\n");
        showStack();
        printf("\t");
        showString();
        printf("\tpush");
        if(prec[position(stk[stk_top])][position(stk[it])]=='>'){
            while(reduce())
        }
    }
}