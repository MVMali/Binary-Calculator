#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include "init.h"
node* remove_zeros(list n){
	list temp1,q;
	 temp1 = n;
    	while(temp1) {
    		//removing the leading zeros
    		if(temp1->dig==0 && temp1->next!=NULL ){
       			 q = temp1;
       			 temp1 = temp1 -> next;
       			 temp1 -> prev = NULL;
      			 n=temp1;
       			 free(q);
       			 }
       		else{
       			return n;}
    }
}

int precedence(char c){
    if(c == '+')
        return 10;  
    else if(c == '-')
        return 10;
    else if(c == '*')
        return 20;
    else if(c == '/')
        return 20;
    else if(c == '%')
        return 20;
    else if(c == '^')
        return 30;
    else if(c == '(')
        return 5;
    else if(c == '#')
        return 0;
    return 0;
}

node* add(list n2, list n1) {
    node *p1, *p2, *n = NULL;
    p1 = n1;
    p2 = n2;
    int  c = 0;
    node *a1 = n1, *a2 = n2;
    a2=remove_zeros(a2);
    a1=remove_zeros(a1);
    while(a1 -> next != NULL) {
        a1 = a1 -> next;
    }
    while(a2 -> next != NULL) {
        a2 = a2 ->next;
    }

    int d1= 0, d2 = 0, d;
    while(a1 && a2) {
        d1 = (a1 -> dig) + (a2 -> dig) + c;
        d2 = d1 % 10;
        c = d1 / 10;
        insert_beg(&n, d2);
        a1 = a1 -> prev;
        a2 = a2 -> prev;
    }

    while(a1) {
        d1 = (a1 -> dig) + c;
        d2 = d1 % 10;
        c = d1 / 10;
        insert_beg(&n, d2);
        a1 = a1 -> prev;
    }

    while(a2) {
        d1 = (a2 -> dig) + c;
        d2 = d1 % 10;
        c = d1 / 10;
        insert_beg(&n, d2);
        a2 = a2 -> prev;
    }
    if(c > 0) {
        insert_beg(&n, c);
    }
    
    return n;
}
void insert_beg(list *p, int d) {
    node *n = *p, *new = NULL, *a = NULL;

    new = (node*)malloc(sizeof(node));
    if(new) {
        new -> dig = d;
        new -> prev = NULL;
        new -> next = NULL;
    }
    else return;
    if((*p) == NULL) {
        (*p) = new;
        return;
    }
    else {
        a = (*p);
        new -> next = a;
        a -> prev = new;
        (*p) = new;
        return; 
    }

}

void display(pstack *ps) {         //printing the linked list 
    node *p = NULL, *q = NULL;
    p = pop_op(ps);     //one linked list is poped
    
    while(p) {
        printf("%d", p -> dig);
        q = p;
        p = p -> next;
        free(q);
    }
    printf("\n");
    return;
}

void print(node *p) {         
    node *n;
    n==NULL;
    n = p;
    while(n) {
        printf("%d", n ->dig);
        n = n ->next;
    }
    return;
}
																	 
node* larger(list n1, list n2) {
    list a = n1, b = n2;
    int c1 = 0, c2 = 0;
    b=remove_zeros(b);
    a=remove_zeros(a);
    while(a) {
        a = a->next;
        c1++;
    } 
    while(b) {
        b = b->next;
        c2++;
    }
    if(c1 > c2) 
        return n1;
    else if(c2 > c1)
        return n2;
    else {
        node *p = n1, *q = n2;
        while(p && q) {
            if(p -> dig > q ->dig) 
                return n1;
            else if(p->dig < q->dig)
                return n2;
            else {
                p = p->next;
                q = q->next;
            }
        }
        return n1;

    }
}


node* sub(list n2, list n1) {
    list a1 = n1, a2 = n2, p1 = n1, p2 = n2, temp = NULL, n3 = NULL, temp2 = NULL,new=NULL;
    list temp1 = n3, q = NULL, x = NULL, y = NULL;
    int r=0;
    a2=remove_zeros(a2);
    a1=remove_zeros(a1);
    q = NULL;
    int  b = 0, d1 = 0, d = 0;
    if(is_same(a1, a2)) {                  
        insert_dig(&temp1, 0);
        return temp1;
    }
   while(a1->next != NULL) {
        insert_dig(&x, a1 ->dig);
        a1 = a1 -> next;
    }
    insert_dig(&x, a1 ->dig);
    while(a2 -> next != NULL) {
        insert_dig(&y, a2 -> dig);
        a2 = a2 ->next;
    }
    insert_dig(&y, a2 ->dig);
    temp = larger(x, y);
    if(!is_same(x,temp)){                       //if a1<a2 then swap it
    			r=-1;
    			new=a1;
    			a1=a2;
    			a2=new;
    			}			
    
   while(a1 && a2) {
            if((a1 -> dig) >= (a2->dig + b)) {
                d1 = (a1 -> dig - (a2 -> dig + b));
                b = 0;
            }
            else {
                d1 = 10 + (a1 ->dig) - (a2->dig + b);         //Here b is working as borrow
                b = 1; 
            }
            insert_beg(&n3, d1);
            a1 = a1 -> prev;
            a2 = a2 -> prev;
        }
    while(a1) {
            if(a1->dig >= b){
                d = a1->dig - b;
                d1 = d % 10;
                insert_beg(&n3, d1);
                a1 = a1 -> prev;
                b = 0;
            }
            else {
                d = 10 + a1->dig - b;
                b = 1;
                d1 = d % 10;
                insert_beg(&n3, d1);
                a1 = a1 -> prev; 
            }
        }
        temp1 = n3;
	temp1=remove_zeros(temp1);
        if(r==-1){
        temp1 -> dig = -(temp1->dig);           //if second number is bigger than first then it gives negative sign to the first number 
        }
    return temp1;
}

node* multi(list n2, list n1) {

    list a1 = n1, a2 = n2, n3 = NULL, mult = NULL, q = NULL, temp=NULL, temp1=NULL;
    mult = (node*)malloc(sizeof(node));
    if(mult) {              //initializing the node
        mult ->dig = 0;
        mult -> next = NULL;
        mult -> prev = NULL;
    }
    a2=remove_zeros(a2);
    a1=remove_zeros(a1);
   
    if(a1->dig==0 || a2->dig==0)                           //returns null if anyone of them is zero
    	return mult;
    if(a2 -> dig == 1 && a2 -> next == NULL)
        return a1;							//if a2 contains only 1 then it returns a1

    while(a2 -> next != NULL) {
        a2 = a2 -> next;
    }								//Pointing to the last digits
    while(a1 -> next != NULL) {
        a1 = a1 -> next;
    }
    temp = a1, temp1= NULL;
    int c = 0, d = 0, t = 0;
    while(a2) {						
        a1 = temp;
        c = 0;
        n3=NULL;
        while(a1) {
            d = (a1->dig) * (a2->dig) + c;        
            insert_beg(&n3, d%10);
            c = d / 10;      
            a1 = a1 -> prev;
        }
        if(c > 0) {
            insert_beg(&n3, c);        //inserting at begining
        }
        int i = 0;
        while(i < t) {
            insert_dig(&n3, 0);     //inserting zero at end of list
            i++;
        }
        mult = add(n3, mult);            //this is the result of multiplication
        a2 = a2 -> prev;
        t++;                                                                                                                                                                   
    }
    //temp1 = mult;
    mult=remove_zeros(mult);
    return mult;

}

void distroy(list *n1) {
    list n = *n1, q = *n1;
    while(n != NULL) {
        q = n;
        n = n -> next;
        n -> prev = NULL;
        q -> next = NULL;
        free(q);
    }
    return;
}

int is_same(list n1, list n2) {         //It is used for the division and substraction
    list a1 = n1, a2 = n2;
    while(a1 && a2) {
        if(a1 -> dig == a2 -> dig){ 
            a1 = a1 -> next;
            a2 = a2 -> next;
            continue;
        }
        else{
            return 0;
        }
    }
    while(a1) {
        return 0;
    }
    while(a2) {
        return 0;
    }
    return 1;
}

node* division(list n2 , list n1) {
    list a1 = n1, a2 = n2, n3 = NULL, temp = NULL, q = NULL;
    int count=0, d=0;
    a2=remove_zeros(a2);
    a1=remove_zeros(a1);
    if(a2 -> dig == 0 ) {
        printf(" 😑️ invalid input.....🔴️ ");
       return NULL;
    }

    if(is_same(a1,a2)) {
        insert_dig(&n3, 1);
        return n3;
    }
    if(is_same(a2,larger(a1,a2))) {  //checks the denominator is bigger or not if yes then return null
        insert_dig(&n3, 0);		
        return n3;
    }

    while(a1) {
        insert_dig(&temp, a1 ->dig);          //new doubly linked list is created
        a1 = a1 -> next;
    }
    while(is_same(temp,larger(temp,a2))) {       //if numerator greater than denominator
        temp = sub(a2, temp);                           //substracting temp-a2 until a2>temp
        count++;
    }
    if(is_same(temp,a2)) {		
        count++;
    }

    while(count > 0) {
        d = count % 10;
        count = count / 10;
        insert_beg(&n3, d);               //inserting d at the begining of the linked list
    }
    return n3;
}

void display_stack(pstack *p) {
    int i = p->top;
    pstack *s = p;
    while(s ->top !=-1) {
        print(s->arr[s->top]);
        printf("\t");
        s ->top--;
    }
    printf("\n");
    s->top = i;
    return;
}

void distroy_stack(pstack *p) {        //distroying the stack 
    pstack *s = p;
    list n =NULL;
    while((s->top) != -1) {
        n = pop_op(p);
        distory_list(&n);
    }
    s->top = s->size - 1;
    while(s->top != -1) {
        s->arr[s->top] = NULL;
        s->top--;
    }
    free(s->arr);
    return;
}

void distory_list(list *n) {
    list l = (*n), m = NULL;
    while(l -> next != NULL) {
        m = l;
        l = l->next;
        l -> prev = NULL;
        m -> next = NULL;
        free(m);
    }
    l ->next = NULL;
    l ->prev = NULL;
    free(l);
    return;
}

void distroy_stack_o(ostack *p) {
    free(p->a);
    return;
}




