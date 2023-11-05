

#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "helper.h"
#include <stdio.h>

char* helper(char* instr) {

	int len;
	int extra;

	// output string
	char *outstr = NULL;
	// for length string
	char *lenstr = NULL;


	// get length
	len = strlen(instr);
	// for string representing the length
	extra = (int)(ceil(log10(len))+1);
	// lenstr now has the "5"
	lenstr = (char *) malloc(sizeof(char)*extra);
	sprintf(lenstr,"%d",len);

	// allocate space for instr and length string
	outstr = malloc(sizeof(char)*(len+extra));

	// now copy and concatnate
	strcpy(outstr,instr);
	strcat(outstr,lenstr);
	printf("DEBUG: outstr = %s\n",outstr);
	return(outstr);
}
