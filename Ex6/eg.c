/*********************************************************
*	"eg.c"
*
* A program used to illustrate pointers, memory allocation and arrays.
*
* Does not necessarily contain the quality or style required by 201
* Assignments
*
**********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

size_t strnlen(const char *s, size_t len);

#define ARR_LEN 5
#define STR_LEN 9

int main()
{
	int* intptr;
	int intarr[ARR_LEN] = {10,20,30,40,50};
	int i;

#ifdef MAKECOPY
	//printf("%p\n",intptr);
	intptr = malloc(5 * sizeof(int));
	if (intptr ==  NULL) {
		fprintf(stderr, "not enough memory, bailing out");
		exit(-1);
	}
	//printf("%p\n",intptr);
	memset(intptr, 0, ARR_LEN*sizeof(int));
	//printf("%p\n",intptr);

#else
	intptr = intarr;
#endif
	//printf("%p\n",intptr);
	for (i=0; i<ARR_LEN; i++)
	{
#ifdef MAKECOPY
		intptr[i] = intarr[i];
#endif
	}
	//printf("%p\n",intptr);

	printf("intarr[3] = %d, intarr+3 = %8p, *(intarr+3)= %d\n",
		intarr[3], intarr+3, *(intarr+3));
	printf("intptr[3] = %d, intptr+3 = %8p, *(intptr+3)= %d\n",
		intptr[3], intptr+3, *(intptr+3));
    
	intarr[3] = 99;

	printf("intarr[3] = %d, intarr+3 = %8p, *(intarr+3)= %d\n",
		intarr[3], intarr+3, *(intarr+3));
	printf("intptr[3] = %d, intptr+3 = %8p, *(intptr+3)= %d\n",
		intptr[3], intptr+3, *(intptr+3));

	printf("*(intarr+3) = %d, *intarr+3 = %d\n", *(intarr+3), *intarr+3);

	printf("sizeof(intarr) = %d, sizeof(intptr) = %d\n",
		sizeof(intarr), sizeof(intptr));
	
	//printf("%p\n",intptr);
	char string1[STR_LEN+1];
	char* string2_ptr;
	printf("%p\n",&string1);
	printf("%p\n",string2_ptr);
	string2_ptr = malloc((STR_LEN+1) * sizeof(char));
	printf("%p\n",string2_ptr);
	if (string2_ptr == NULL) {
		fprintf(stderr, "not enough memory, bailing out");
		exit(-1);
	}
	printf("%p\n",string2_ptr);
  
	memset(string1, 0, STR_LEN+1);
	strncpy(string1, "123456789", STR_LEN);
	memset(string2_ptr, 0, STR_LEN+1);
	strncpy(string2_ptr, string1, STR_LEN);
	printf("%p\n",string2_ptr);
	printf("string1 = %s, string2_ptr = %s\n", string1, string2_ptr);
	printf("strnlen(string1, STR_LEN+1) = %d,  strnlen(string2_ptr, STR_LEN+1) = %d\n",
		strnlen(string1, STR_LEN+1), strnlen(string2_ptr, STR_LEN+1));
	printf("sizeof(string1) = %d sizeof(string2_ptr) = %d\n",
		sizeof(string1), sizeof(string2_ptr));


	/* Arrays and pointers are different. We can do this... */

	string2_ptr = string1;
	intptr = intarr;
	string1[0] = 'A';
	printf("%c\n",*string2_ptr);
	printf("%s\n",string1);
	printf("%p\n",&string1);	
	printf("%p\n",string2_ptr);



	/*
	* ... but we can't do things like this..
	* (Try uncommenting the next two lines)
	*/

	/*string1 = string2_ptr;*/
	/*intarr = intptr;*/

  return 0;
}
