#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include "init.h"

int main() {       
    char str[1000];
    pstack ps;
    ostack os;
    init_os(&os, 10);
    init_ps(&ps, 10);
    int i = 0, n = 0, m=0, invalid = 0, obrac = 0, cbrac = 0;
    char c;
    list n1, n2, n3, result, zero;
    zero = (node*)malloc(sizeof(node));
    if (zero) {
        zero -> dig = 0;
        zero -> next = NULL;
        zero -> prev = NULL;
    }
    puts("😁️ Welcome to BC calulator ✍️");
    while(1) {
        printf(">>>");
        n1 = n2 = n3 = result = NULL;
        //init(&result);
        i = 0; n = 0 ; invalid = 0; obrac = 0; cbrac = 0;
        init_os(&os, 10);
        init_ps(&ps, 2);
        gets(str);
        whitespace(str);
        
        if(!strcmp(str,"exit"))                 //It breaks the entire while loop and programme stops
            break;
        else if(isdigit(str[i]) || str[i] == '(' || str[i]=='-') {
		
                push_os(&os, '#');            //Pushing # into the operator stack
                if(str[i]=='-'){
                	push_os(&os,'-');
                	i++;}
                while(str[i] != '\0') {
                    if(str[i] == '(') {
                        push_os(&os, '(');
                        obrac++;
                   
                        if(isdigit(str[i+1]) || str[i+1] == '('){           //check next is digit or not if yes then increment value of i
                            i++;
                        }
                        else {
                            printf(" 😯️ ‼️ Invalid Input‼️ 🤪️\n");
                            invalid = 1;
                            break;
                        }
                    }
                    else if(isdigit(str[i])) {
                    	n3=NULL;
                        do{ 
                            n = str[i] - '0';
                            insert_dig(&n3, n);       //It creates the doubly linked list 
                            i++;
                        }while(isdigit(str[i]));
                        push_op(&ps, n3);         //pushing the doubly linked list into the stack
                        if((str[i] == '(' || str[i]==')')&& (str[i+1]!='\0' ) ){ ///it executes if for example 34(+ it isinvalid input
                            printf(" 🙄️ ‼️ Invalid input‼️ 🤪️\n");
                            invalid = 1;                                               
                            break;
                        }
                    }
                    else if(str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*' ) {
                         if((isdigit(str[i+1]) || str[i+1] == '(')){
                            c = pop_os(&os);
                            if(precedence(str[i]) > precedence(c)) {
                                push_os(&os, c);
                                push_os(&os, str[i]);       //pushing higher precedence operator into the stack
                                i++;
                            }
                            else {
                                while(precedence(str[i]) <= precedence(c)) {
                                    n2 = pop_op(&ps);          //Pop the two doublly linked list ;
                                    n1 = pop_op(&ps);
                                    switch(c) {
                                        case '+' : result = add(n2, n1);
                                                push_op(&ps, result);         //Stores the result into the operator stack as doubly linked list
                                                break;
                                        case '-' : result = sub(n2, n1);
                                                push_op(&ps, result);
                                                break;
                                        case '*' : result = multi(n2, n1);
                                                push_op(&ps, result);
                                                break;
                                        case '/' : if(is_same(n2, zero)) {
                                                   // printf("Invalid input : zero division errror occured");
                                                    printf(" 😑️ invalid input.....🔴️ ");
                                                    break;
                                                }
                                                result = division(n2, n1);
                                                push_op(&ps, result);
                                                break;
                                        
                                        default : break;
                                    }
                                    c = pop_os(&os);                 //pop operator 
                                }
                                push_os(&os, c);			//push operator into the operator stack
                                push_os(&os, str[i]);		
                                i++;
                            }
                        }
                        else {
                            printf(" 🙄️‼️ Invalid input ‼️ 🤪️\n");
                            invalid = 1;
                            break;
                        }
                    }
                    else if(str[i] == ')') {
                        cbrac++;
                            c = pop_os(&os);
                            while(c != '(' && c != '#') {          //upto opening bracket the loop goes on
                                n2 = pop_op(&ps);
                                n1 = pop_op(&ps);
                                switch(c) {
                                    case '+' : result = add(n2, n1);
                                                push_op(&ps, result);
                                                break;
                                    case '-' : result = sub(n2, n1);
                                                push_op(&ps, result);
                                                break;
                                    case '*' : result = multi(n2, n1);
                                                push_op(&ps, result);
                                                break;
                                    case '/' :  if(is_same(n2, zero)) {
                                                   // printf("Invalid input : zero division errror occured");
                                                    printf(" 😑️ invalid input.....🔴️ ");
                                                    break;
                                                }
                                                result = division(n2, n1);
                                                push_op(&ps, result);
                                                break;
                                  
                                    default : break;
                                }
                                c = pop_os(&os);
                            }
                            if(c == '#') {
                                push_os(&os, '#');
                            }
                           i++;  //changes made here                                   
                            if(str[i] == '\0')
                                break;
                            i++;    
                    }
                }
                if(invalid == 1) {
                    continue;
                }
                c = pop_os(&os);
                while(c != '#'){
                    n2 = pop_op(&ps);
                    n1 = pop_op(&ps);
                    switch(c) {
                        case '+' :  result = add(n2, n1);
                                    push_op(&ps, result);
                                    break;
                        case '-' :  result = sub(n2, n1);
                                    push_op(&ps, result);
                                    break;
                        case '*' :  result = multi(n2, n1);
                                    push_op(&ps, result);
                                    break;
                        case '/' :  if(is_same(n2, zero)) {
                                        //printf("Invalid input : zero division errror occured");
                                        printf(" 😑️ invalid input.....🔴️ ");
                                        break;
                                    }
                                    result = division(n2, n1);
                                    push_op(&ps, result);
                                    break;
                      
                        default :   break;
                    }
                    c = pop_os(&os);
            }
        }
        if(obrac != cbrac) {
            printf(" ‼️ Error : brackets didn't match  😯️\n");
            invalid = 1;
        }
        if(invalid != 1) {
            display_stack(&ps);
        }
        distroy_stack(&ps);
        distroy_stack_o(&os);
    }
}
