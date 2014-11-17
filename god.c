#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <strings.h>

char string[20];
int length;
int size;
int main() 
{
	for (int i=0; i<7; i++)
	{
		string[i] = 'a';
	} 
	length = strnlen(string,20);
	size = sizeof(string);
	printf("%d\n",length);
	printf("%d\n",size);
	return  0;
}
