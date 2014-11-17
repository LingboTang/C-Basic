// Starter file for 201 lab exam 

// You may add other includes here.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <strings.h>

#define textini 40
#define lineini 10
// definitions, struct type definitions, macros or function declarations
// here

//e.g.
//#define MAXBUF 80

void do_section1();
void do_section2();
void do_section3();
void do_section4();

// do not modify this main function in any way ... don't touch it.
// main checks for some errors, for your convenience - it may make 
// debugging easier.
int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    fprintf(stderr, "error: required argument not given\n");
    fprintf(stderr, 
            "       usage example: ./labexam 1 < input_file > output_file\n"); 
    exit(EXIT_FAILURE);
  }

  int which_section;
  int ret_val = sscanf(argv[1], "%d", &which_section); 
  if (ret_val != 1)
  {
    fprintf(stderr, "error: argument is not a number, %s\n",
                    argv[1]);
    exit(EXIT_FAILURE);
  }
 
  switch(which_section)
  {
    case 1:
      do_section1();
      break;
    case 2:
      do_section2();
      break;
    case 3:
      do_section3();
      break;
    case 4:
      do_section4();
      break;
    default:
      fprintf(stderr, "error: argument is not between 1 and 4, %s\n",
                      argv[1]);
      exit(EXIT_FAILURE);
  }
  
}
 
// Add your code below this line.  If needed, create other helper functions.
//============================================================================

/*void remove_punct(char *text)
{
    char *final = text, *temp = text;

    while (*final)
    {
       if (ispunct((unsigned char)*final))
       {
          final++;
       }
       else if (final == temp)
       {
          final++;
          temp++;
       }
       else
       {
          *temp++ = *final++;
       }
    }
    *temp = 0;
}*/
void remove_punct(char*text, int totalchar)
{	
	int detect_i = 0;
	while (detect_i<totalchar)
	{
		if(!ispunct(text[detect_i]))
		{
			putchar(text[detect_i]);
		}
		detect_i++;
	}
}
		

void do_section1()
{
  char* text;
  int container = textini;
  text = malloc(container*sizeof(char));
  assert(text);
  memset(text,0,container+1);
  char ch;
  int countchar;
  while ((ch=getchar()) != EOF)
  {
	text[countchar] = tolower(ch);
	countchar++;
	if (countchar == container)
	{
		container *= 2;
		text = realloc (text, container*sizeof(char));
		assert(text);
		memset(text+container/2-1,0,container/2+1);
	}
  }
  int totalchar =countchar;
  for(int k = 0;k<totalchar;k++)
  {
    printf("%c",text[k]);
  }
  remove_punct(text,totalchar);	
  free(text);
}
 

void do_section2()
{
	char**text;
	int container=textini;
	int linecontainer = lineini;
	int text_i= 0,line_i=0;
	char ch;
	text = malloc(container*sizeof(char*));
	assert(text);
	memset(text,0,countainer+1);
	text[text_i] = malloc(linecontainer*sizeof(char));
	assert(text[text_i]);
	memset(text[text_i],0,linecontainer+1);
	while ((ch = getchar()) !=EOF)
	{
		if(ch != '\n')
		{
			text[text_i][line_i] = ch;
			line_i++;
			if (line_i == linecontainer-1)
			{
				text[text_i] =realloc(text[text_i],linecontainer*sizeof(char));
				assert(text[text_i]);
				memset(text[text_i]+linecontainer/2-1,0,linecontainer/2+1);
		}
		if(ch == '\n')
		{
			text_i++;
			if(text_i == container-1)
			{
				container *=2;
				text = realloc(text,container*sizeof(char*));
				assert(text);
				memset(text+container/2-1,0,countainer/2+1);
			}
			linecontainer = lineini;
			text[text_i] = malloc(linecontainer*sizeof(char));
			assert(text[text_i]);
			memset(text[text_i],0,linecontainer+1);
		}
	}
	int totalline = text_i;
	for(int k = 0;k<totalline;k++)
	{
		printf("%s\n",text[text_i]);
	}
	free(text[text_i]);
	free(text);
}
  
struct people
{
	char* name;
	int phone;
	int age;
};

void do_section3()
{
  
}

void do_section4()
{
  // Add code here that does what is needed for Section 4.  Free up all
  // memory allocated (if you have allocated memory).  You may call
  // other functions you create.
}


