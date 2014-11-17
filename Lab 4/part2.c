#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>

#define maxaline 256
int main() 
{
	char line[maxaline+1];
	char* instruct;
	FILE* fp;
	int file_len;
	fp=fopen("input2.txt","r");
	memset(line,0,maxaline+1);
	instruct = fgets(line,maxaline+1,fp);
	file_len = atoi(instruct);
	char ch[file_len][maxaline+1];
	int i=0;
	memset(line, 0, maxaline + 1);
	while((fgets(line,maxaline+1,fp))!=NULL)
	{
	    strcpy(ch[i],line);
	    i++;
	    memset(line, 0, maxaline + 1);
	}
	for (i = i-1; i >=0; i--)
	{
	    fprintf(stdout,"%s",ch[i-1]);
	}
}
