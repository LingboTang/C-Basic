
#define _POSIX_C_SOURCE 200112L


#include <signal.h>
#include <sys/time.h>

#include <stdio.h>
#include <stdlib.h>


void handle_timeout(int signal);


sigset_t block_mask_g;


int main()
{
  
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

  
  for ( ; ; )
    ;

 
  exit(EXIT_SUCCESS);
}



void handle_timeout(int signal)
{
  static int called = 0;

  called++;

  
  if (signal == SIGALRM)
  {

    
    struct itimerval timer;
    if (getitimer(ITIMER_REAL, &timer) == -1)
      exit(EXIT_FAILURE);

    printf("called: %d\n", called);

    
    if (called == 5)
    {
      timer.it_interval.tv_sec = 0;
      timer.it_value.tv_sec = 0;
      exit(EXIT_SUCCESS);
    }

    if (setitimer(ITIMER_REAL, &timer, NULL) == -1)
      exit(EXIT_FAILURE);
  }

}


void example_of_blocking_a_signal()
{
  
  sigset_t old_mask;
  
  if (sigprocmask(SIG_BLOCK, &block_mask_g, &old_mask) < 0)
    exit(EXIT_FAILURE);

 
  if (sigprocmask(SIG_SETMASK, &old_mask, NULL) < 0)
    exit(EXIT_FAILURE);
}
