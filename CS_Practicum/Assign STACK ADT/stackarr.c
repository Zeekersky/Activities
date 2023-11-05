#include<stdio.h>
#include"stack.h"
#include<stdlib.h>

void create(stack** s)
{
*s = (stack *) malloc(sizeof(stack));
if (!(*s))
{
printf("Memory Error");
exit(1);
}

(*s)->arr = (char *) malloc(sizeof(char)*100);
if(!(*s)->arr)
{
printf("Memory Error");
exit(1);
}
(*s)->top = -1;
//st->head= NULL;
}

void push(stack **s, char c)
{
(*s)->arr[++(*s)->top]=c;
}

char pop(stack **s)
{
return (*s)->arr[((*s)->top)--];
}

char peek(stack **s)
{
return (*s)->arr[(*s)->top];
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
















