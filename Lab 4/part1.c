#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>


#define maxaline 256
int main()
{
	char ch[100][maxaline+1];
	char line[maxaline+1];
	FILE* fp;
	fp = fopen("gasses.txt","r");
	int i=0;
	memset(line, 0, maxaline + 1);
	while((fgets(line,maxaline+1,fp))!=NULL)
	{
	    strcpy(ch[i],line);
	    i++;
	    memset(line, 0, maxaline + 1);
	}
	for (i = i-1; i-1>=0; i--)
	{
		fprintf(stdout,"%s",ch[i-1]);
	}
}
