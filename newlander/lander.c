#define _POSIX_C_SOURCE 200112L
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
#include <stdbool.h>
#include <getopt.h>
#include "parse.h"
#define Linelen 20
#define PI acos(-1.0)

const char exec_name[] = "java -jar Sketchpad.jar";
FILE* executable;
double acceleration;
double thrust;
double angle;
double changeangle;
double totaltime;
int startengine;
int fire;
int i;
char line[Linelen+1];
int numberlines;
int score;
int crashed;
int crash;
int isparall;
int i_flag;
int command;
double fuels;
double changefuels;
double number_fuels;
double totaltimes;
int n;
struct cord {
	double x;
	double y;
};

sigset_t block_mask_g;

void opensketch();
void drawlandscape(FILE*landscape);
void drawline(struct cord P,struct cord Q);
void eraseline(struct cord P,struct cord Q);
void drawshuttle();
void eraseshuttle();
void handle_timeout(int signal);
double transfer_d_r(double angle);
void setup_curses();
void unset_curses();
double cord_min_x();
double cord_min_y();
double cord_max_x();
double cord_max_y();
//void findcenter();
void rotate();
void drawscaler();
//void closesketch();
void block_and_rotate();
int lineSegmentIntersection(double Ax, double Ay,double Bx, double By,double Cx, double Cy,double Dx, double Dy);
void drawfuelbar();
void erasefuelbar();
void zapper();
double X,Y;


struct cord shuttle[16];
struct cord center[1];
struct cord velocity[1];
struct cord joint[21];
struct cord fuelbar[201];
struct cord pieces[9];

int main(int argc, char*argv[])
{
	FILE* landscape;
	i_flag = 0;
	char * filename = NULL;
	extern char * optarg;
	extern int optopt;
	while ((command  = getopt(argc,argv,"-t:g:f:i")) != -1)
	{
		switch (command)
		{
			case 'g':
				acceleration = atof(optarg);
				break;
			case 't':
				thrust = atof(optarg);
				break;
			case 'f':
				filename = optarg;
				break;
			case 'i':
				i_flag = 1;
				break;
			case '?':
				if (optopt == 'f')
				{
					fprintf(stderr,"Option -%c requires an argument.\n", optopt);
				}
				else if (isprint(optopt))
				{
					fprintf(stderr, "unknown option ---%c.\n", optopt);
				}
				else
				{
					fprintf(stderr, "unknown option charactar make no sense '\\x%x'.\n",optopt);
				}
				return 1;
			default:
				abort();
		}
		if (acceleration < 0) 
		{
			printf("Acceleration should be a positive number \n");
			exit(1);
		}
		if (thrust<-20 || thrust > 0)
		{
			printf("Thrust should be in the interval of (-20,0) \n");
			exit(1);
		}
	}
	landscape = fopen(filename,"r");
	velocity[0].x = 0;
	velocity[0].y = 0;
		
	shuttle[0].x = 320;
	shuttle[0].y = 0;
	shuttle[1].x = 315;
	shuttle[1].y = 20;
	shuttle[2].x = 305;
	shuttle[2].y = 30;
	shuttle[3].x = 315;
	shuttle[3].y = 40;
	shuttle[4].x = 325;
	shuttle[4].y = 40;
	shuttle[5].x = 335;
	shuttle[5].y = 30;
	shuttle[6].x = 325;
	shuttle[6].y = 20;
	shuttle[7].x = 320;
	shuttle[7].y = 55;
	shuttle[8].x = 310;
	shuttle[8].y = 40;
	shuttle[9].x = 310;
	shuttle[9].y = 50;
	shuttle[10].x = 330;
	shuttle[10].y = 40;
	shuttle[11].x = 330;
	shuttle[11].y = 50;
	shuttle[12].x = 305;
	shuttle[12].y = 35;
	shuttle[13].x = 310;
	shuttle[13].y = 35;
	shuttle[14].x = 335;
	shuttle[14].y = 35;
	shuttle[15].x = 330;
	shuttle[15].y = 35;

	angle = 90.0;
	score = 0;
	startengine = 0;
	numberlines = 0;
	number_fuels = 0;
	crash = 0;
	crashed = 0;
	isparall = 0;
	fuels =2000.0;
	
	i = 0;
	changefuels = (-thrust);
	totaltime = fuels/changefuels;
	opensketch();
	
	setup_curses();
  	move(5, 10);
  	printw("Press any key to start.\n");
	printw("          (Then press arrow keys to rotate,space of thrust,'q' to quit.)");
  	refresh();
  	int c = getch();

	drawlandscape(landscape);
	fflush(executable);
	drawshuttle();
	fflush(executable);
	if (i_flag == 1)
	{
		drawfuelbar();
		fflush(executable);
		drawscaler();
		fflush(executable);
	}

  	nodelay(stdscr, true);
  	erase();

  	refresh();
  	//c = getch();

	sigemptyset(&block_mask_g); 
  	sigaddset(&block_mask_g, SIGALRM); 

  	struct sigaction handler;
  	handler.sa_handler = handle_timeout;
  	sigemptyset(&handler.sa_mask);
  	handler.sa_flags = 0;

 	if (sigaction(SIGALRM, &handler, NULL) == -1)
    		exit(EXIT_FAILURE);

  	struct itimerval timer;
    		struct timeval time_delay;
    		time_delay.tv_sec = 0;
    		time_delay.tv_usec = 0;
    		time_delay.tv_usec = 50000;

    		timer.it_interval = time_delay;

    
    		struct timeval start;
    		start.tv_sec = 0;
    		start.tv_usec = 0;
    		start.tv_usec = 50000;

    		timer.it_value = start;

  
  	if (setitimer(ITIMER_REAL, &timer, NULL) == -1)
    		exit(EXIT_FAILURE);

  	while(1)
  	{	
		sigset_t old_mask;
		if (sigprocmask(SIG_BLOCK, &block_mask_g, &old_mask) < 0)
		{
    			exit(EXIT_FAILURE);
		}
		
    		if (c != ERR)
    		{
      			erase();
      			move(5,10);
      			printw("\n      left arrow key rotates counter-clockwise,right clockwise,space for thrust,'q' to quit");
			if (crash == 0)
			{
      				if (c == KEY_LEFT)
				{
					changeangle = -10.0;
					angle += changeangle;
					score += 10;
					block_and_rotate();
				}

      				else if (c == KEY_RIGHT)
				{
					changeangle = 10.0;
					angle += changeangle;
					score += 10;
					block_and_rotate();
				}
      				else if (c == ' ')
				{	
					startengine =1;
					fire = 1;
					if (i_flag == 1)
					{
						if(number_fuels < totaltime -1)
						{
							number_fuels++;
						}
						else
						{
							thrust =0;
							startengine =0;
							fire = 0;
							fprintf(executable,"setColor %ld %ld %ld\n", lround(0.0),lround(0.0),lround(0.0));
							fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(610.0),lround(120.0),lround(620.0),lround(120.0));
							fflush(executable);
						}
					}
				}
      				else if (c == 'q')
				{	
        				break;
				}
					
      				refresh();
			}
			else
			{
				if (c == 'q')
				{
					break;
				}
			}
    		}
		if (sigprocmask(SIG_SETMASK, &old_mask, NULL) < 0)
    		{	
			exit(EXIT_FAILURE);
		}
    		c = getch();
  	}
	fprintf(executable, "end\n");
  	unset_curses();
	pclose(executable);
	fclose(landscape);
  	exit(EXIT_SUCCESS);
}	

//The coordinators are really different from the catitian coordinators
void drawlandscape(FILE*landscape)
{	
	if (i_flag == 1)
	{
		fprintf(executable, "setColor %ld %ld %ld\n",lround(0.0),lround(0.0),lround(255.0));
	}
	memset(line,0,Linelen+1);
	long x_cord1,y_cord1;
	while (fgets(line,Linelen+1,landscape) != NULL)
	{
		sscanf(line,"%ld %ld",&x_cord1,&y_cord1);

		joint[numberlines].x = (double)x_cord1;
		joint[numberlines].y = (double)y_cord1; 
		memset(line,0,Linelen+1);
		numberlines+=1;
	}
	int k = 0;	
	for (k=0;k<numberlines-1;k++)
	{
		fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(joint[k].x),lround(joint[k].y),lround(joint[k+1].x),lround(joint[k+1].y));
	}
	int m=0;
	k = 0;
	while (m< numberlines)
	{
		for (k=m;k<(int)joint[m+1].x;k++)
		{
			fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(joint[m].x+k-m),lround(480),lround(joint[m].x+k-m),lround(joint[m].y-((joint[m].y-joint[m+1].y))/(joint[m+1].x-joint[m].x)*k));
		}
		m++;
	}
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

void drawline(struct cord P,struct cord Q)
{
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n", lround(P.x),lround(P.y),lround(Q.x),lround(Q.y));
}

void eraseline(struct cord P,struct cord Q)
{
	fprintf(executable,"eraseSegment %ld %ld %ld %ld\n", lround(P.x),lround(P.y),lround(Q.x),lround(Q.y));
}

void drawshuttle()
{	
	if (i_flag == 1)
	{
		fprintf(executable, "setColor %ld %ld %ld\n",lround(150.0),lround(100.0),lround(200.0));
	}
	if (fire ==0)
	{
		drawline(shuttle[0],shuttle[1]);
		drawline(shuttle[1],shuttle[2]);
		drawline(shuttle[2],shuttle[3]);
		drawline(shuttle[3],shuttle[4]);
		drawline(shuttle[4],shuttle[5]);
		drawline(shuttle[5],shuttle[6]);
		drawline(shuttle[6],shuttle[1]);
		drawline(shuttle[0],shuttle[6]);
		drawline(shuttle[2],shuttle[5]);
		drawline(shuttle[8],shuttle[3]);
		drawline(shuttle[8],shuttle[9]);
		drawline(shuttle[4],shuttle[10]);
		drawline(shuttle[10],shuttle[11]);
		drawline(shuttle[2],shuttle[12]);
		drawline(shuttle[12],shuttle[13]);
		drawline(shuttle[5],shuttle[14]);
		drawline(shuttle[14],shuttle[15]);
		
	}
	if (fire == 1)
	{
		drawline(shuttle[0],shuttle[1]);
		drawline(shuttle[1],shuttle[2]);
		drawline(shuttle[2],shuttle[3]);
		drawline(shuttle[3],shuttle[4]);
		drawline(shuttle[4],shuttle[5]);
		drawline(shuttle[5],shuttle[6]);
		drawline(shuttle[6],shuttle[1]);
		drawline(shuttle[0],shuttle[6]);
		drawline(shuttle[2],shuttle[5]);
		drawline(shuttle[8],shuttle[3]);
		drawline(shuttle[8],shuttle[9]);
		drawline(shuttle[4],shuttle[10]);
		drawline(shuttle[10],shuttle[11]);
		drawline(shuttle[2],shuttle[12]);
		drawline(shuttle[12],shuttle[13]);
		drawline(shuttle[5],shuttle[14]);
		drawline(shuttle[14],shuttle[15]);
		if (i_flag == 1)
		{
			fprintf(executable, "setColor %ld %ld %ld\n",lround(255.0),lround(0.0),lround(0.0));
		}
		drawline(shuttle[3],shuttle[7]);
		drawline(shuttle[7],shuttle[4]);
	}
}

void eraseshuttle()
{
	eraseline(shuttle[0],shuttle[1]);
	eraseline(shuttle[1],shuttle[2]);
	eraseline(shuttle[2],shuttle[3]);
	eraseline(shuttle[3],shuttle[4]);
	eraseline(shuttle[4],shuttle[5]);
	eraseline(shuttle[5],shuttle[6]);
	eraseline(shuttle[6],shuttle[1]);
	eraseline(shuttle[0],shuttle[6]);
	eraseline(shuttle[2],shuttle[5]);
	eraseline(shuttle[8],shuttle[3]);
	eraseline(shuttle[8],shuttle[9]);
	eraseline(shuttle[4],shuttle[10]);
	eraseline(shuttle[10],shuttle[11]);
	eraseline(shuttle[2],shuttle[12]);
	eraseline(shuttle[12],shuttle[13]);
	eraseline(shuttle[5],shuttle[14]);
	eraseline(shuttle[14],shuttle[15]);
	eraseline(shuttle[3],shuttle[7]);
	eraseline(shuttle[7],shuttle[4]);
}

void handle_timeout(int signal)
{
	//static int called = 0;
	static int pointid= 0;
	static int snum = 0;
	static int lnum = 0;

	if (crashed == 1)
	{		
		if ((velocity[0].x < 20)&&(isparall != 0)&&(sin(transfer_d_r(angle)) == 1.0))
		{	
			move(8,10);
			printw("Landed! \n");
			refresh();
			return;
		}
		else 
		{
			move(8,10);
			printw("Crashed! \n");
			refresh();
			return;
		}
	}

	
	if (i_flag == 1)
	{
		if (cord_max_x() <= 0.0)
		{
			eraseshuttle();
			fflush(executable);
			while (pointid <16)
			{
				shuttle[pointid].x = shuttle[pointid].x+640;
				pointid++;
			}
			pointid =0;
			drawshuttle();
			fflush(executable);
		}
		if (cord_min_x() >= 640.0)
		{	
			eraseshuttle();
			fflush(executable);
			while (pointid < 16)
			{
				shuttle[pointid].x = shuttle[pointid].x - 640;
				pointid ++;
			}
			pointid = 0;
			drawshuttle();
			fflush(executable);
		}
		if (cord_max_y() <= 0)
		{
			eraseshuttle();
			fflush(executable);
			while (pointid < 16)
			{
				shuttle[pointid].y = shuttle[pointid].y + 40;
				pointid++;
			}
			drawshuttle();
			fflush(executable);
		}
		
	}
		
		
	if (startengine == 0)
	{	
		eraseshuttle();
		fflush(executable);
		while (pointid < 16)
		{
			shuttle[pointid].x = shuttle[pointid].x + velocity[0].x * 0.05;
			shuttle[pointid].y = shuttle[pointid].y+ velocity[0].y * 0.05 + 1/2*acceleration* 0.05*0.05;
			pointid++;
		}
		pointid = 0;
		velocity[0].y = velocity[0].y + acceleration * 0.05;
		drawshuttle();
		fflush(executable);
	}

	if (startengine == 1)
	{	
		eraseshuttle();
		fflush(executable);
		fuels -= changefuels;
		erasefuelbar();
		if (fuels <= 0)
		{
			thrust = 0;
		}
		while (pointid<16)
		{
			shuttle[pointid].x = shuttle[pointid].x + velocity[0].x*0.05 + 1/2*(thrust*cos(transfer_d_r(angle)))*0.05*0.05;
			shuttle[pointid].y = shuttle[pointid].y + velocity[0].y*0.05 + 1/2*(acceleration+thrust*sin(transfer_d_r(angle)))*0.05*0.05;
			pointid++;
		}
		pointid = 0;
		velocity[0].y = velocity[0].y + (acceleration+ thrust*sin(transfer_d_r(angle)))*0.05;
		velocity[0].x = velocity[0].x + (thrust * cos(transfer_d_r(angle)))*0.05;
		drawshuttle();
		fflush(executable);
		fire = 0;
		startengine = 0;
	}
	
	for (snum =0; snum< 16; snum++)
	{
		for (lnum =0; lnum < numberlines-1; lnum++)
		{
			crash = lineSegmentIntersection(shuttle[snum].x,shuttle[snum].y,shuttle[snum+1].x,shuttle[snum+1].y,joint[lnum].x,joint[lnum].y,joint[lnum+1].x,joint[lnum+1].y);
			if (crash == 1)
			{
				crashed = 1;
				if(joint[lnum+1].y == joint[lnum].y)
				{
					isparall = 1;
				}
				break;
			}
		}
		if (crashed == 1)
		{
			break;
		}
	}
	
  	if (signal == SIGALRM)
  	{
    		struct itimerval timer;
		
		if (getitimer(ITIMER_REAL, &timer) == -1)
      			exit(EXIT_FAILURE);
		
		
		
    		if (setitimer(ITIMER_REAL, &timer, NULL) == -1)
      			exit(EXIT_FAILURE);
		
	}
	
	
}

double transfer_d_r(double angle)
{
	double r;
	r = angle* PI/180.0;
	return r;
}

double cord_min_x()
{ 
	double minvalue;
	minvalue = shuttle[0].x;
	for(int k = 0;k < 16; k++)
	{
		if (minvalue > shuttle[k].x)
		{
			minvalue = shuttle[k].x;
		}
	}
	return minvalue;
}

double cord_min_y()
{
	double minvalue;
	minvalue = shuttle[0].y;
	for(int k = 0;k < 16; k++)
	{
		if (minvalue > shuttle[k].y)
		{
			minvalue = shuttle[k].y;
		}
	}
	return minvalue;
}


double cord_max_x()
{
	double maxvalue;
	maxvalue = shuttle[0].x;
	for(int k = 0;k < 16; k++)
	{
		if (maxvalue < shuttle[k].x)
		{
			maxvalue = shuttle[k].x;
		}
	}
	return maxvalue;
}

double cord_max_y()
{
	double maxvalue;
	maxvalue = shuttle[0].y;
	for(int k = 0;k < 16; k++)
	{
		if (maxvalue < shuttle[k].y)
		{
			maxvalue = shuttle[k].y;
		}
	}
	return maxvalue;
}

void rotate()
{	
	double min_x;
	double min_y;
	double max_x;
	double max_y;
	double xo;
	double yo;
	min_x = cord_min_x();
	min_y = cord_min_y();
	max_x = cord_max_x();
	max_y = cord_max_y();
	center[0].x = (min_x+max_x)/2;
	center[0].y = (min_y+max_y)/2;
	double radius;
	radius = transfer_d_r(changeangle);
	struct cord temp[16];
	eraseshuttle();
	fflush(executable);
	int t = 0;
	for (t = 0; t<16;t++)
	{	
		temp[t].x = shuttle[t].x - center[0].x;
		temp[t].y = shuttle[t].y - center[0].y;
		xo = temp[t].x;
		yo = temp[t].y;
		temp[t].x = (xo * cos(radius))- (yo * sin(radius));
		temp[t].y = (xo * sin(radius))+ (yo * cos(radius));
		shuttle[t].x = temp[t].x+center[0].x;
		shuttle[t].y = temp[t].y+center[0].y;
	}
	drawshuttle();
	fflush(executable);
}


void block_and_rotate()
{
	rotate();
}

void opensketch()
{
	executable = popen(exec_name,"w");
	if (executable == NULL)
	{
		fprintf(stderr,"Could not open pipe %s\n",exec_name);
	}
}

void drawfuelbar()
{	
	fuelbar[0].x = 610; 
	fuelbar[0].y = 20;
	fuelbar[1].x = 620;
	fuelbar[1].y = 20;
	for (int k = 2; k < 200;k+=2)
	{
		fuelbar[k].x = 610;
		fuelbar[k+1].x = 620;
		fuelbar[k].y = fuelbar[0].y+1*(k/2);
		fuelbar[k+1].y = fuelbar[0].y+1*(k/2);
	}
	if (i_flag == 1)
	{
		fprintf(executable, "setColor %ld %ld %ld\n",lround(0.0),lround(255.0),lround(0.0));
	}
	for (int m = 0; m< 200; m+=2)
	{
	  	drawline(fuelbar[m],fuelbar[m+1]);
	}
	if (i_flag == 1)
	{
		fprintf(executable, "setColor %ld %ld %ld\n",lround(0.0),lround(0.0),lround(0.0));
	}
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(610.0),lround(120.0),lround(620.0),lround(120.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(620.0),lround(120.0),lround(620.0),lround(20.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(620.0),lround(20.0),lround(610.0),lround(20.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(610.0),lround(20.0),lround(610.0),lround(120.0));
}


void drawscaler()
{	
	fprintf(executable, "setColor %ld %ld %ld\n",lround(0.0),lround(0.0),lround(0.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(623.0),lround(16.0),lround(626.0),lround(16.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(626.0),lround(16.0),lround(626.0),lround(20.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(626.0),lround(20.0),lround(623.0),lround(20.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(623.0),lround(20.0),lround(623.0),lround(24.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(623.0),lround(24.0),lround(626.0),lround(24.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(627.0),lround(16.0),lround(630.0),lround(16.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(630.0),lround(16.0),lround(630.0),lround(24.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(630.0),lround(24.0),lround(627.0),lround(24.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(627.0),lround(24.0),lround(627.0),lround(16.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(631.0),lround(16.0),lround(634.0),lround(16.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(634.0),lround(16.0),lround(634.0),lround(24.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(634.0),lround(24.0),lround(631.0),lround(24.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(631.0),lround(24.0),lround(631.0),lround(16.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(635.0),lround(16.0),lround(638.0),lround(16.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(638.0),lround(16.0),lround(638.0),lround(24.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(638.0),lround(24.0),lround(635.0),lround(24.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(635.0),lround(24.0),lround(635.0),lround(16.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(623.0),lround(66.0),lround(623.0),lround(74.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(625.0),lround(66.0),lround(628.0),lround(66.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(628.0),lround(66.0),lround(628.0),lround(74.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(628.0),lround(74.0),lround(625.0),lround(74.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(625.0),lround(74.0),lround(625.0),lround(66.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(629.0),lround(66.0),lround(632.0),lround(66.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(632.0),lround(66.0),lround(632.0),lround(74.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(632.0),lround(74.0),lround(629.0),lround(74.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(629.0),lround(74.0),lround(629.0),lround(66.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(633.0),lround(66.0),lround(636.0),lround(66.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(636.0),lround(66.0),lround(636.0),lround(74.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(636.0),lround(74.0),lround(633.0),lround(74.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(633.0),lround(74.0),lround(633.0),lround(66.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(623.0),lround(116.0),lround(626.0),lround(116.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(626.0),lround(116.0),lround(626.0),lround(124.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(626.0),lround(124.0),lround(623.0),lround(124.0));
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(623.0),lround(124.0),lround(623.0),lround(116.0));
}

void erasefuelbar()
{
	fprintf(executable,"eraseSegment %ld %ld %ld %ld\n", lround(610.0),lround(20.0+number_fuels*100/totaltime),lround(620.0),lround(20.0+number_fuels*100/totaltime));
	fflush(executable);
}

void zapper()
{	
	fprintf(executable,"eraseSegment %ld %ld %ld %ld\n",lround(0.0),lround(200.0),lround(200.0),lround(400.0));
	fflush(executable);
	fprintf(executable,"drawSegment %ld %ld %ld %ld\n",lround(0.0),lround(200.0),lround(200.0),lround(400.0));
	fflush(executable);
}

int lineSegmentIntersection(
double Ax, double Ay,
double Bx, double By,
double Cx, double Cy,
double Dx, double Dy
) {

  double  distAB, theCos, theSin, newX, ABpos ;


  if ((Ax==Bx && Ay==By) || (Cx==Dx && Cy==Dy)) 
	return 0;

 
  if ((Ax==Cx && Ay==Cy) || (Bx==Cx && By==Cy)
  ||  (Ax==Dx && Ay==Dy) || (Bx==Dx && By==Dy)) 
  {
    return 0; 
  }

  Bx-=Ax; By-=Ay;
  Cx-=Ax; Cy-=Ay;
  Dx-=Ax; Dy-=Ay;


  distAB=sqrt(Bx*Bx+By*By);

 
  theCos=Bx/distAB;
  theSin=By/distAB;
  newX=Cx*theCos+Cy*theSin;
  Cy  =Cy*theCos-Cx*theSin; Cx=newX;
  newX=Dx*theCos+Dy*theSin;
  Dy  =Dy*theCos-Dx*theSin; Dx=newX;

  if ((Cy<0. && Dy<0.) || (Cy>=0. && Dy>=0.)) 
	return 0;

  ABpos=Dx+(Cx-Dx)*Dy/(Dy-Cy);

  if (ABpos<0. || ABpos>distAB)
  { 
     return 0;
  }
  X=Ax+ABpos*theCos;
  Y=Ay+ABpos*theSin;

  return 1; }



