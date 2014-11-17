#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <strings.h>
#include <signal.h>
#include <sys/time.h>
#include <curses.h>
#include "parse.h"
#define _POSIX_C_SOURCE 200112
#define PI acos(-1.0)
#define Linelen 100

const char exec_name[] = "java -jar Sketchpad.jar";
FILE* executable;
double acceleration;
double thrust;

void opensketch()
{
	executable = popen(exec_name,"w");
	if (executable == NULL)
	{
		fprintf(stderr,"Could not open pipe %s\n",exec_name);
	}
}

void closesketch()
{
	pclose(exec_name);
}

typedef struct {
  double x;
  double y;
} cord;

void drawlandscape(FILE*landscape);

void drawshuttle();

sigset_t block_mask_g;





