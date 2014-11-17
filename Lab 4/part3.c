#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>

#define maxaline 256
#define initial 10
int main() 
{
	char line[maxaline+1];
	FILE* fp;
	fp=fopen("input3.txt","r");
	int i=0;
	char* ch;
	int onthego = initial;
	ch = malloc(onthego*sizeof(line));
	memset(line, 0, maxaline + 1);
	while((fgets(line,maxaline+1,fp))!=NULL)
	{
	    strncpy(&ch[i],line,maxaline+1);
	    i += maxaline+1;
	    if (i == onthego)
	    {
		onthego *= 2;
		ch = realloc(ch,onthego*sizeof(line));
	    }
	    memset(line, 0, maxaline + 1);
	}
	for (i = i-maxaline-1; i >=0; i -= maxaline+1)
	{
	    fprintf(stdout,"%s",&ch[i-maxaline-1]);
	}
}
