#include<stdio.h>
#include<stdlib.h>
#include"stack.h"

int main()
{
	stack *s;
	create(&s);

	push(&s, 's');
	push(&s, 'f');
	printf("Element Pop: %c\n",pop(&s));
	printf("Element Peek: %c\n",peek(&s));

	printf("IsEmpty: %d\n", isempty(&s));

	printf("Getsize: %d\n", getsize(&s));
	printf("Hello From Driver.c");

}


