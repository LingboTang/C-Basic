#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "parse.h"

char program_name[PROG_LEN + 1];
const char exec_name[] = "java -jar Sketchpad.jar -d";
int shiftX; 
int shiftY;

int main(int argc, char* argv[])
{
  FILE* input;
  FILE* executable;

  memset(program_name, 0, PROG_LEN + 1);
  strncpy(program_name, argv[0], PROG_LEN);

  if (argc != 4) {
    fprintf(stderr, "Usage: %s input-file shiftX shiftY\n", program_name);
    exit(1);
  }

  input = fopen(argv[1], "r");

  if (input == NULL) {
    fprintf(stderr, "Could not open input file %s\n", argv[1]);
    exit(1);
  }

  /*** Add code to extract the shift values from the command line ***/
  /*** arguments and set the shift values shiftX and shiftY ***/
  shiftX = strtol(argv[2],NULL,0);
  shiftY = strtol(argv[3],NULL,0);
  shiftX = atoi(argv[2]);
  shiftY = atoi(argv[3]);
  executable = popen(exec_name, "w");
  if (executable == NULL)
    fprintf(stderr, "Could not open pipe %s\n", exec_name);


  convert(input, executable);

  pclose(executable);
  fclose(input);

  return EXIT_SUCCESS;
}

// Read from input, convert and send the rows to executable 
void convert(FILE* input, FILE* executable)
{
  char command[LINE_LEN + 1];
  char line[LINE_LEN + 1];


  memset(line, 0, LINE_LEN + 1);
  memset(command, 0, LINE_LEN + 1);
  while (fgets(line, LINE_LEN + 1, input) != NULL)
  {
    if (strncmp(line, "drawSegment", 11) == 0) {
      fprintf(executable, "%s", line);  // print the original line

      /*** Add code to shift the X and Y coordinates respectively by shiftX
           and shiftY (i.e. add shiftX to X and shiftY to Y) and draw 
           the shifted line ***/
      long a,b,c,d,e,f,g,h;
      sscanf(line,"%s%ld%ld%ld%ld",command,&a,&b,&c,&d);
      //printf("%ld %ld %ld %ld\n",a,b,c,d);
      e = a + shiftX;
      f = b + shiftY;
      g = c + shiftX;
      h = d + shiftY;
      //printf("%ld %ld %ld %ld\n",e,f,g,h);
      fprintf(executable,"drawSegment %ld %ld %ld %ld\n",e,f,g,h);
    }
    else 
      fprintf(executable, "%s", line);

    memset(line, 0, LINE_LEN + 1);
    memset(command, 0, LINE_LEN + 1);
  }
}
