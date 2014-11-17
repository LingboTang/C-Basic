#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#define linelen 10
#define filelen 10


void drawlandscape(char**command)

int main(int argc, char*argv[])
{	
	
	double acceleration;
	double thrust;
	int m;
	FILE* landscape;
	char** command;
	int filecontainer = filelen;
	int linecontainer = linelen;
	int file_i = 0;
	int line_i = 0;
	command = malloc(filecontainer*sizeof(char*));
	assert(command);
	memset(command, 0, filecontainer+1);
	command[file_i] = malloc(linecontainer*sizeof(char));
	assert(command[file_i]);
	memset(command[file_i],0,linelen+1);
	for (m = 0; m<argc; m++)
	{
		if (argv[m][0] == '-')
		{
			if(strlen(argv[m])==2)
			{
				switch (argv[m][1])
				{
					case 'g':
						acceleration = atof(argv[m+1]);
					case 't':
						thrust = atof(argv[m+1]);
					case 'f':
						landscape = fopen(argv[m+1],"r");
				}
				/*if (thrust < (double)(-20) || thrust > (double)(0))
				{
					printf("Thrust should not be less than -20 or over 0.\n");
					exit(1);
				}*/
			}
			else if (strlen((argv[m]))>2)
			{
				switch(argv[m][1])
				{
					case 'g':
						acceleration = atof(argv[m]+2);
					case 't':
						thrust = atof(argv[m]+2);
					case 'f':
						landscape = fopen(argv[m]+2,"r");
				}
				if (thrust < (double)(-20) && thrust > (double)(0))
				{
					printf("Thrust should not be less than -20 or over 0.\n");
					exit(1);
				}
			}
		}
	}
	printf("%f\n",acceleration);
	printf("%f\n",thrust);
	char ch;
	//int i =0;
	while ((ch = fgetc(landscape)) !=EOF)
	{
		printf("%c",ch);
		if(ch != '\n')
		{
			command[file_i][line_i] = ch;
			line_i++;
			//printf("%c\n",command[file_i][line_i]);
			if (line_i == linecontainer -1)
			{
				linecontainer *=2;
				command[file_i] = realloc(command[file_i],linecontainer*sizeof(char));
				assert(command[file_i]);
				memset(command[file_i]+linecontainer/2-1,0,linecontainer/2+1);
			}
		}
		if (ch == '\n')
		{
			file_i++;
			if(file_i == filecontainer-1)
			{
				filecontainer *= 2;
				command = realloc(command,filecontainer*sizeof(char*));
				assert(command);
				memset(command[file_i]+filecontainer/2-1,0,filecontainer/2+1);
			}
			linecontainer = linelen;
			command[file_i] = malloc(linecontainer*sizeof(char));
			assert(command[file_i]);
			memset(command[file_i],0,linecontainer+1);
			line_i = 0;
		}	
	}
	for(int t = 0; t<file_i; t++)
	{
		printf("%s\n",command[t]);
	}
	return 0;
}
		
void drawlandscape(char**command)
{
	fprintf	
