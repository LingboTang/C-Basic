#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <strings.h>
#include "parse.h"
//#include "lander.h"
#include <signal.h>
#include <sys/time.h>
#include <curses.h>
//#include <time.h>
#define Linelen 100
#define PI acos(-1.0)
const char exec_name[] = "java -jar Sketchpad.jar";
void drawlandscape(FILE*landscape,FILE*executable);
struct cord{
  double x;
  double y;
};

sigset_t block_mask_g;
void drawshuttle(FILE*executable,struct cord shuttle[]);
void handle_timeout(FILE*executable,double acceleration,struct cord shuttle[],int signal,struct cord velocity[]);

void setup_curses();
void unset_curses();


//void masseffect(FILE*executable,double acceleration,struct cord shuttle[]);



int main(int argc, char*argv[])
{	
	
	FILE*executable;
	double acceleration;
	double thrust;
	int m;
	FILE* landscape;
	long time_sent = 10;
	int isleft = 0;
	int isright = 0;
	int isthrust = 0;
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
			}
			else if (strlen((argv[m]))>2)
			{
				switch (argv[m][1])

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

	struct cord velocity[1];
	velocity[0].x = 0;
	velocity[0].y = 0;
	
	
	struct center[1];
	center[0].x = 0;
	center[0].y = 0;

	struct cord shuttle[5];

	shuttle[0].x = 310;
	shuttle[0].y = 20;
	shuttle[1].x = 300;
	shuttle[1].y = 40;
	shuttle[2].x = 340;
	shuttle[2].y = 40;
	shuttle[3].x = 330;
	shuttle[3].y = 20;
	
	setup_curses();
	executable = popen(exec_name,"w");
	if (executable == NULL)
		fprintf(stderr,"Could not open pipe %s\n",exec_name);
  	move(5, 10);
  	printw("Press any key to start.\n");
	printw("          (Then press arrow keys to rotate,space of thrust,'q' to quit.)");
	
	
  	refresh();
  	int c = getch();
	
  	nodelay(stdscr, true);
  	erase();
	drawlandscape(landscape,executable);
	fflush(executable);	
	move(5, 10);
  	printw("Press arrow keys, 'q' to quit.\n");
  	printw("          Leftarrow key to rotate counter-clockwise,rightarrow key to rotate clockwise,'q' to quit.");
	

	
	
	
	sigemptyset(&block_mask_g); 
  	sigaddset(&block_mask_g, SIGALRM); 
  	
  	
  	struct itimerval timer;
    		struct timeval time_delay;
    			time_delay.tv_sec = 1;
    			time_delay.tv_usec = 0;
    			time_delay.tv_usec = 50000;
    			timer.it_interval = time_delay;
    		struct timeval start;
    			start.tv_sec = 3;
    			start.tv_usec = 0;
    			start.tv_usec = 50000;
    			timer.it_value = start;
  	if (setitimer(ITIMER_REAL, &timer, NULL) == -1)
    		exit(EXIT_FAILURE);
	struct sigaction handler;
  	handler.sa_handler = handle_timeout;
  	sigemptyset(&handler.sa_mask);
  	handler.sa_flags = 0;
	if (sigaction(SIGALRM, &handler, NULL) == -1)
    		exit(EXIT_FAILURE);
	while(1)
  	{	
		c = getch();
		handle_timeout(executable,acceleration,shuttle,signal,velocity);
    		if (c != ERR)
    		{
      			erase();
      			move(5,10);
      			printw("left arrow key rotates counter-clockwise,right clockwise,space for thrust,'q' to quit");
      			move(6, 10);
      			if (c == KEY_DOWN)
        			printw("down key pressed");
     			else if (c == KEY_LEFT)
        			printw("left key pressed");
				//isleft = 1;
				//rotate_cc(executable, )
      			else if (c == KEY_RIGHT) 
        			printw("right key pressed");
      			else if (c == KEY_UP)
        			printw("up key pressed");
      			else if (c == 'q')
				fprintf(executable,"pause %ld\n",time_sent);
        			break;

    		}
  	}
	
	unset_curses();
	fprintf(executable,"end\n");
	pclose(executable);
	fclose(landscape);
	exit(EXIT_SUCCESS);
}

void drawlandscape(FILE*landscape,FILE*executable)
{	

	char line[Linelen+1];
	memset(line,0,Linelen+1);

	long joint[Linelen+1];
	int i = 0;
	long x_cord1,y_cord1;
	while (fgets(line,Linelen+1,landscape) != NULL)
	{
		sscanf(line,"%ld %ld",&x_cord1,&y_cord1);
		joint[i] = x_cord1;
		joint[i+1] = y_cord1; 
		memset(line,0,Linelen+1);
		i+=2;
	}

	int k = 0;	
	for (k=0;k<i-2;k+=2)
	{
		fprintf(executable,"drawSegment %ld %ld %ld %ld\n",joint[k],joint[k+1],joint[k+2],joint[k+3]);
	}
}

double transfer_d_r(double angle)
{
	double r;
	r = angle* PI/180.0;
	return r;
}

void setup_curses()
{
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);
}

void unset_curses()
{
  keypad(stdscr, false);
  nodelay(stdscr, false);
  nocbreak();
  echo();
  endwin();
}

void drawline(struct cord P, struct  cord Q, FILE*executable)
{
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n", lround(P.x),lround(P.y),lround(Q.x),lround(Q.y));
}



void eraseline(struct cord P,struct cord Q, FILE*executable)
{
	fprintf(executable,"eraseSegment %ld %ld %ld %ld\n", lround(P.x),lround(P.y),lround(Q.x),lround(Q.y));
}

void drawshuttle(FILE*executable,struct cord shuttle[])
{
	drawline(shuttle[0],shuttle[1],executable);
	drawline(shuttle[1],shuttle[2],executable);
	drawline(shuttle[2],shuttle[3],executable);
	drawline(shuttle[3],shuttle[0],executable);
}

void eraseshuttle(FILE*executable, struct cord shuttle[])
{
	eraseline(shuttle[0],shuttle[1],executable);
	eraseline(shuttle[1],shuttle[2],executable);
	eraseline(shuttle[2],shuttle[3],executable);
	eraseline(shuttle[3],shuttle[0],executable);
}

void handle_timeout(FILE*executable,double acceleration,struct cord shuttle[],int signal,struct cord velocity[])
{	
	static int timelast = 0;
	sigemptyset(&block_mask_g); 
  	sigaddset(&block_mask_g, SIGALRM); 
	timelast ++;
	int unit_time = 0.05;
	int pointid= 0;
	if (signal == SIGALRM)
	{	
		struct itimerval timer;
			struct timeval time_delay;
    				time_delay.tv_sec = 1;
    				time_delay.tv_usec = 0;
    				time_delay.tv_usec = 50000;
    				timer.it_interval = time_delay;
    			struct timeval start;
    				start.tv_sec = 3;
    				start.tv_usec = 0;
    				start.tv_usec = 50000;
    				timer.it_value = start;

		if (getitimer(ITIMER_REAL,&timer) == -1)
		{
			exit(EXIT_FAILURE);
		}
		drawshuttle(executable,shuttle);
		eraseshuttle(executable,shuttle);
		fflush(executable);
		while (pointid < 5)
		{
			shuttle[pointid].y = shuttle[pointid].y+ velocity[0].y * unit_time + 1/2*acceleration* unit_time*unit_time;
			pointid++;
		}
		velocity[0].y = velocity[0].y + acceleration * unit_time;
		timelast = timelast + unit_time;
		drawshuttle(executable,shuttle);
		eraseshuttle(executable,shuttle);
		fflush(executable);
		if (timelast == 100)
		{
			timer.it_interval.tv_sec = 0;
			timer.it_value.tv_sec = 0;
			exit(EXIT_SUCCESS);
		}
			
		
		if (setitimer(ITIMER_REAL,&timer,NULL) == -1)
		{
			exit(EXIT_FAILURE);
		}
	}
}

/*(void handle_timeout(int signal)
{
  static int called = 0;

  called++;

  
  if (signal == SIGALRM)
  {

    
    struct itimerval timer;
    if (getitimer(ITIMER_REAL, &timer) == -1)
      exit(EXIT_FAILURE);

    printf("called: %d\n", called);

    
    if (called == 20)
    {
      timer.it_interval.tv_sec = 0;
      timer.it_value.tv_sec = 0;
      exit(EXIT_SUCCESS);
    }

    if (setitimer(ITIMER_REAL, &timer, NULL) == -1)
      exit(EXIT_FAILURE);
  }

}*/
double cord_min_x(struct cord shuttle[])
{
	double minvalue;
	for(int k = 0;k < 2; k++)
	{
		if (shuttle[k].x > shuttle[k+1].x)
		{
			minvalue = shuttle[k+1].x;
		}
		else if (shuttle[k].x < shuttle[k+1].x)
		{
			minivalue = shuttle[k].x;
		}
	}
	return minvalue;
}

double cord_min_y(struct cord shuttle[])
{
	double minvalue;
	for(int k = 0;k < 2; k++)
	{
		if (shuttle[k].y > shuttle[k+1].y)
		{
			minvalue = shuttle[k+1].y;
		}
		else if (shuttle[k].y < shuttle[k+1].y)
		{
			minivalue = shuttle[k].y;
		}
	}
	return minvalue;
}


double cord_max_x(struct cord shuttle[])
{
	double maxvalue;
	for(int k = 0;k < 2; k++)
	{
		if (shuttle[k].x > shuttle[k+1].x)
		{
			maxvalue = shuttle[k].x;
		}
		else if (shuttle[k].x < shuttle[k+1].x)
		{
			maxivalue = shuttle[k+1].x;
		}
	}
	return maxvalue;
}

double cord_max_y(struct cord shuttle[])
{
	double maxvalue;
	for(int k = 0;k < 2; k++)
	{
		if (shuttle[k].y > shuttle[k+1].y)
		{
			maxvalue = shuttle[k+1].y;
		}
		else if (shuttle[k].y < shuttle[k+1].y)
		{
			maxivalue = shuttle[k].y;
		}
	}
	return maxvalue;
}


void rotate_cc(FILE*executable,const int c,struct cord center[])
{	
	double min_x = 0;
	double min_y = 0;
	double max_x = 0;
	double max_y = 0;
	double angle = 10.0;
	double radius;
	radius = transfer_d_r(10.0);
	//while
	min_x = cord_min_x(shuttle);
	max_x = cord_max_x(shuttle);
	min_y = cord_min_y(shuttle);
	max_y = cord_max_y(shuttle);
	center[0].x = (min_x+max_x)/2;
	center[0].y = (min_y+max_y)/2;
	eraseshuttle(executable,shuttle);
	fflush(executable);
	for (int k = 0;k< 4; k++)
	{
		shuttle[k].x = shuttle[k].x*cos(radius)- shuttle[k].y*cos(radius);
		shuttle[k].y = shuttle[k].y*cos(radius)+shuttle[k].y*cos(radius);
	}
	drawshuttle(executable,shuttle);
	fflush(executable);
	center[0].x = 0;
	center[0].y = 0;
}

void rotate_c(FILE*executable,const int c,struct cord center[])
{	
	double min_x = 0;
	double min_y = 0;
	double max_x = 0;
	double max_y = 0;
	double angle = -10.0;
	double radius;
	radius = transfer_d_r(-10.0);
	//while
	min_x = cord_min_x(shuttle);
	max_x = cord_max_x(shuttle);
	min_y = cord_min_y(shuttle);
	max_y = cord_max_y(shuttle);
	center[0].x = (min_x+max_x)/2;
	center[0].y = (min_y+max_y)/2;
	eraseshuttle(executable,shuttle);
	fflush(executable);
	for (int k = 0;k< 4; k++)
	{
		shuttle[k].x = shuttle[k].x*cos(radius)- shuttle[k].y*cos(radius);
		shuttle[k].y = shuttle[k].y*cos(radius)+shuttle[k].y*cos(radius);
	}
	drawshuttle(executable,shuttle);
	fflush(executable);
	center[0].x = 0;
	center[0].y = 0;
}


void rotate(FILE * executable, const int c,struct cord center[],struct cord shuttle[])
{
	if (c == KEY_LEFT)
	{
		rotate_cc(executable,c,center);
	}
	if (c == KEY_RIGHT)
	{
		rotate_c(executable,c,center);
	}
}

void drawthrust(FILE*executable,struct cord shuttle[])
{
	struct cord thrust[1];
	thrust[0].x = (shuttle[2].x+shuttle[3].x)/2;
	thrust[0].y = (shuttle[2].y+shuttle[3].y)/2;
		

void thrust(FILE * executable, double thrust,struct cord shuttle[],const int c)
{
	
