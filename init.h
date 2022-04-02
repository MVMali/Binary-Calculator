typedef struct node {
    int dig;
    struct node *next;
    struct node *prev; 
}node;

typedef node* list;

typedef struct ostack {   //operator stack
    int size; 
    int top;   
    char *a;
}ostack;

typedef struct pstack {  //operand stack
    int size;
    int top;
    node **arr;               //array of pointer of type node
}pstack;
typedef pstack *ptr_ps;


//operations on oparator stack
void init_os(ostack *s, int len);
int isFull_os(ostack s);
int isEmpty_os(ostack s);
void push_os(ostack *s, char d);
char pop_os(ostack *s);

//operations on the operand stack
void init_ps(pstack *s, int len);
int isEmpty_op(pstack ps);
int isFull_op(pstack ps);
void init_num(pstack *ps);
void push_op(pstack *s, node *p);
node* pop_op(pstack *s);
void insert_dig(list *n, int d);

//functions.
int precedence(char c);
node* add(list n2, list n1);
void display(pstack *ps);
node* sub(list n2, list n1);
node* multi(list n2, list n1);
node* division(list n2 , list n1);
void insert_beg(list *p, int d);
void print(node *p);
node* larger(list n1, list n2);
node* multii(list n2, list n1);
void distroy(list *n1);
int is_same(list n1, list n2);
void display_stack(pstack *p);
void distroy_stack(pstack *p);
void distory_list(list *n);
void distroy_stack_o(ostack *p);
char *whitespace( char *a);
node* remove_zeros(list mult);
