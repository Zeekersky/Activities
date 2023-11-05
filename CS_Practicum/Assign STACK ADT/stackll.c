#include<stdio.h>
#include"stack.h"
#include<stdlib.h>

void create(stack **s)
{
*s = (stack *) malloc(sizeof(stack));
if (!(*s))
{
printf("Memory Error");
exit(1);
}

(*s)->head = NULL;
(*s)->tops = NULL;
(*s)->top = -1;
}

void push(stack **s, char c)
{
node* nnode = (node* ) malloc(sizeof(node));
if(!nnode)
{
	printf("Memory Error.");
	exit(1);
}

nnode->data = c;
nnode->next = NULL;

if((*s)->head == NULL)
{
	(*s)->head = nnode;
	(*s)->tops = nnode;
}
else
{
	(*s)->tops->next = nnode;
	(*s)->tops = nnode;
}
(*s)->top++;

}

char pop(stack **s)
{
printf("Not Properly Working");
/*
char ch;
if((*s)->head == NULL)
	printf("Stack Underflow");
else
{

	ch = (*s)->tops->data;
	node* temp = (*s)->head;
	if((*s)->head->next == NULL) 
		(*s)->head = NULL;
	else
	{

		while(temp->next != (*s)->tops )
		{
			temp = temp->next;
		}
		temp->next = NULL;
		(*s)->tops = temp;
	}

	free(temp);
	return ch;

}
(*s)->top--;
*/
}

char peek(stack **s)
{
return ((*s)->tops->data);
}

int isempty(stack **s)
{

if((*s)->top == -1)
       return 1;
else return 0;

}

int getsize(stack **s)
{
return ((*s)->top + 1);
}
