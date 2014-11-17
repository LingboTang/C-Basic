#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>

int len(const char *a)
{
	int i;
	for(i = 0; a[i] != 0; i ++);
	return i;
}

#define maxfile 20000
#define maxline 200
void get_target_term(char*targetterm, char* term)
{
	char ch; 				//to get every character one by one
	int term_len = len(term);		//get the term length and the new line is counted in the length
	int targetterm_len = len(targetterm);
	int samepart = 0;			//the length of the same part in the two comparing words
	int isterm = 0;				//if it is a term then we should count, otherwise.
	long charOffset=0,*termOffset,comparedchar=0;		//How many chars we have already compared in the terms.
	int defrange = 5;
	char filelist[maxfile][maxline];
	while ((ch = getchar()) != EOF)
	{
		comparedchar++;			//Count the chars
		if (isalnum(ch) && isterm == 0)	// if it is a term then count, otherwise
		{
			*termOffset++;
			isterm = 1;
		}
		if (!isalnum(ch))
		{
			isterm = 0;
		}
		if (samepart != term_len)
		{
			if (lower_case(ch) == lower_case(term[samepart]))
			{			//Compared the term and store each "match" point.
				charOffset = comparedchar;
				samepart++;
			}
			else
			{
				charOffset = 0;
				samepart = 0;
			}
		}
		else
		{	
			if ( )
			charOffset = comparedchar - term_len;
          		fprintf(stdout,"%ld,%ld,%s\n", charOffset,*termOffset,term);
          		samepart = 0; 
		}
	}
}




int main(int argc, char * argv[])
{
	if(argc< 4 || argc >9) //They are not the only possible permutations
	{
		fprintf(stderr, "Could not open input file %s\n",argv[1]);
	}
	if(argc == 4)
	{	
		char* targetterm;
		if((strcmp(argv[1],"-b")) == 0)
		{
			targetterm = argv[2];
			term = argv[3];
		}
		if((strcmp(argv[2],"-b")) == 0)
		{
			targetterm = argv[3];
			term = argv[2];
		}
		get_target_term(targetterm,term);
			
  	}
	return 0;
}

