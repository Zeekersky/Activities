typedef struct node{
char data;
struct node* next;
} node;

typedef struct stack{
char *arr;
struct node* head;
int top;
struct node* tops;
} stack;

void create(stack **s);
void push(stack **s, char c);
char pop(stack **s);
char peek(stack **s);
int isempty(stack **s);
int getsize(stack **s);

