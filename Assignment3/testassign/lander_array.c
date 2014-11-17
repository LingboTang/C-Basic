#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <strings.h>
#include "parse.h"
#include "lander.h"
//#include <signal.h>
//#include <sys/time.h>
/*#define linelen 10
#define filelen 10

#define Linelen 100
//extern FILE* executable;
const char exec_name[] = "java -jar Sketchpad.jar";

void drawlandscape(FILE*landscape,FILE*executable);
void drawshuttle(FILE*executable);*/






int main(int argc, char*argv[])
{	
	FILE*executable;
	double acceleration;
	double thrust;
	int m;
	FILE* landscape;
	//char** commandtext;
	//int filecontainer = filelen;
	//int linecontainer = linelen;
	//int file_i = 0;
	//int line_i = 0;
	long time_sent = 10;
	/*commandtext = malloc(filecontainer*sizeof(char*));
	assert(commandtext);
	memset(commandtext, 0, filecontainer+1);
	commandtext[file_i] = malloc(linecontainer*sizeof(char));
	assert(commandtext[file_i]);
	memset(commandtext[file_i],0,linelen+1);*/
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
	executable = popen(exec_name,"w");
	if (executable == NULL)
		fprintf(stderr,"Could not open pipe %s\n",exec_name);

	printf("%f\n",acceleration);
	printf("%f\n",thrust);
	//char ch;
	//int i =0;
	/*while ((ch = fgetc(landscape)) !=EOF)
	{
		//printf("%c",ch);
		if(ch != '\n')
		{
			commandtext[file_i][line_i] = ch;
			line_i++;
			//printf("%c\n",command[file_i][line_i]);
			if (line_i == linecontainer -1)
			{
				linecontainer *=2;
				commandtext[file_i] = realloc(commandtext[file_i],linecontainer*sizeof(char));
				assert(commandtext[file_i]);
				memset(commandtext[file_i]+linecontainer/2-1,0,linecontainer/2+1);
			}
		}
		if (ch == '\n')
		{
			file_i++;
			if(file_i == filecontainer-1)
			{
				filecontainer *= 2;
				commandtext = realloc(commandtext,filecontainer*sizeof(char*));
				assert(commandtext);
				memset(commandtext[file_i]+filecontainer/2-1,0,filecontainer/2+1);
			}
			linecontainer = linelen;
			commandtext[file_i] = malloc(linecontainer*sizeof(char));
			assert(commandtext[file_i]);
			memset(commandtext[file_i],0,linecontainer+1);
			line_i = 0;
		}	
	}*/
	//for(int t = 0; t<file_i; t++)
	//{
		//printf("%s\n",commandtext[t]);
	//}
	drawlandscape(landscape,executable);
	//drawshuttle(executable);
	//gravity(executable,gravity);
	fprintf(executable,"pause %ld\n",time_sent);
	fprintf(executable,"end\n");
	pclose(executable);
	fclose(landscape);
	return EXIT_SUCCESS;
}

		
void drawlandscape(FILE*landscape,FILE*executable)
{	
	printf("abcd\n");
	char line[Linelen+1];
	memset(line,0,Linelen+1);
	long joint[Linelen+1];
	int i = 0;
	long x_cord1,y_cord1;
	while (fgets(line,Linelen+1,landscape) != NULL)
	{
		printf("abcd\n");
		sscanf(line,"%ld %ld",&x_cord1,&y_cord1);
		joint[i] = x_cord1;
		joint[i+1] = y_cord1; 
		memset(line,0,Linelen+1);
		i+=2;
	}
	int k = 0;	
	while ( k < i-2)
	{
		fprintf(executable,"drawSegment %ld %ld %ld %ld\n",joint[k],joint[k+1],joint[k+2],joint[k+3]);
		k+=2;
	}
}

/*void drawshuttle(FILE*executable)
{
	printf("This is the start of ship\n");
	long vertices[8];
	long midpoint[4];
	long head[6];
	long wings[12];
	vertices[0] = 300;vertices[1]=20;vertices[2] =300;vertices[3]=50;vertices[4]=340;vertices[5]=50;vertices[6]=340;vertices[7]=20;
	midpoint[0] = 320;midpoint[1]=20;midpoint[2] =320;midpoint[3]=50;
	head[0]=300;head[1]=20;head[2]=320;head[3]=5;head[4]=340;head[5]=20;
	wings[0]= 300;wings[1]=25;wings[2]=280;wings[3]=35;wings[4]=300;wings[5]=35;wings[6]=340;wings[7]=25;wings[8]=360;wings[9]=35;wings[10]=340;wings[11]=35;
	int k =0;
	while(k<8-2)
	{
			fprintf(executable,"drawSegment %ld %ld %ld %ld\n",vertices[k],vertices[k+1],vertices[k+2],vertices[k+3]);
			k+=2;
	}
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",vertices[k],vertices[k+1],vertices[0],vertices[1]);
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",midpoint[0],midpoint[1],midpoint[2],midpoint[3]);
	k =0;
	while (k<6-2)
	{
		fprintf(executable,"drawSegment %ld %ld %ld %ld\n",head[k],head[k+1],head[k+2],head[k+3]);
		k+=2;
	}
	k =0;
	while (k<12-2)
	{
		fprintf(executable,"drawSegment %ld %ld %ld %ld\n",wings[k],wings[k+1],wings[k+2],wings[k+3]);
		k+=2;
	}
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",wings[k],wings[k+1],wings[0],wings[1]);
}*/

/*void gravity(FILE*executable, double gravity,long vertices[],long midpoint[],long head[],long wings[])
{
	int time_delay.tv_usec = 50000;
	int unit_time = 1;
	int velocity = 0;
	while (time_delay.tv_usec > 0);
	{
		vertices[1] = vertices[1] + velocity*unit_time + 1/2*gravity*unit_time*unit_time;
		vertices[3] = vertices[3] + velocity*unit_time + 1/2*gravity*unit_time*unit_time;
		vertices[5] = vertices[5] + velocity*unit_time + 1/2*gravity*unit_time*unit_time;
		vertices[7] = vertices[7] + velocity*unit_time + 1/2*gravity*unit_time*unit_time;
		midpoint[1] = midpoint[1] + velocity*unit_time + 1/2*gravity*unit_time*unit_time;
		midpoint[3] = midpoint[3] + velocity*unit_time + 1/2*gravity*unit_time*unit_time;
		head[1] = head[1] + velocity*unit_time + 1/2*gravity*unit_time*unit_time;
		head[3] = head[3] + velocity*unit_time + 1/2*gravity*unit_time*unit_time;
		head[5] = head[5] + velocity*unit_time + 1/2*gravity*unit_time*unit_time;
		wings[1] = wings[1] + velocity*unit_time + 1/2*gravity*unit_time*unit_time;
		wings[3] = wings[3] + velocity*unit_time + 1/2*gravity*unit_time*unit_time;
		wings[5] = wings[5] + velocity*unit_time + 1/2*gravity*unit_time*unit_time;
		wings[7] = wings[7] + velocity*unit_time + 1/2*gravity*unit_time*unit_time;
		wings[9] = wings[9] + velocity*unit_time + 1/2*gravity*unit_time*unit_time;
		wings[11] = wings[11] + velocity*unit_time + 1/2*gravity*unit_time*unit_time;
		int k = 0;
		while (k<8-2)
		{
			fprintf(executable,"drawSegment %ld %ld %ld %ld\n",vertices[k],vertices[k+1],vertices[k+2],vertices[k+3]);
			k+=2;
		}
		fprintf(executable,"drawSegment %ld %ld %ld %ld\n",vertices[k],vertices[k+1],vertices[0],vertices[1]);
		fprintf(executable,"drawSegment %ld %ld %ld %ld\n",midpoint[0],midpoint[1],midpoint[2],midpoint[3]);
		k =0;
		while (k < 6-2)
		{
			fprintf(executable,"drawSegment %ld %ld %ld %ld\n",head[k],head[k+1],head[k+2],head[k+3]);
			k+=2;
		}
		k =0;
		while (k<12-2)
		{
			fprintf(executable,"drawSegment %ld %ld %ld %ld\n",wings[k],wings[k+1],wings[k+2],wings[k+3]);
			k+=2;
		}
		fprintf(executable,"drawSegment %ld %ld %ld %ld\n",wings[k],wings[k+1],wings[0],wings[1]);
		unit_time ++;
		time_delay.tv_usec - unit_time;
	}
}*/

