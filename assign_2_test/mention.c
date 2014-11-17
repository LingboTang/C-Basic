#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
int len(const char *a)
{
	int i;
	for(i = 0; a[i] != 0; i ++);
	return i;
}

char lower_case(const char a)
{
	if(a >= 'A' && a <= 'Z') return (char)(a - 'A' + 'a');
	return a;
}

void lowerstring(char* string, int wordrange) 
{
	for (int i=0; string[i] && i<wordrange; i++) 
	{
   		if (isalpha(string[i])) 
		{
      			string[i] = lower_case(string[i]);
    		}
  	}
}

void storefile(FILE* file)
{
	#define maxaline 40

	char ch[200][maxaline+1];
	char line[maxaline+1];
	int i=0;
	memset(line, 0, maxaline + 1);
	while((fgets(line,maxaline+1,file))!=NULL)
	{
	    strcpy(ch[i],line);
	    i++;
	    memset(line, 0, maxaline + 1);
	}
	for (i = 0; i<=maxaline; i++)
	{
		fprintf(stdout,"%s",ch[i]);
	}
}

/*void compare_initial(FILE* file)
{	
	char termlist[200][40];
	int ismatch[200],termlen[200],groundsearch[200];
	int i=0,j=0;
	char listterm;
	char* term;
	while((listterm=fgetc(file))!=EOF)
	{
		if(listterm!='\n')
		{
			termlist[i][j]=listterm;
			j++;
		}
		else
		{
			term=termlist[i];
			termlen[i]=len(term);
			ismatch[i]=0;
			groundsearch[i]=0;
			j=0;
			i++;
		}
	}
}*/

void compare_term(char* term)
{
	char ch; 				//to get every character one by one
	int term_len = len(term);		//get the term length and the new line is counted in the length
	int samepart = 0;			//the length of the same part in the two comparing words
	int isterm = 0;				//if it is a term then we should count, otherwise.
	long charOffset=0,termOffset=0,comparedchar=0;		//How many chars we have already compared in the terms.
	while ((ch = getchar()) != EOF)
	{
		comparedchar++;			//Count the chars
		if (isalnum(ch) && isterm == 0)	// if it is a term then count, otherwise
		{
			termOffset++;
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
			charOffset = comparedchar - term_len;
          		fprintf(stdout,"%ld,%ld,%s\n", charOffset,termOffset,term);
          		samepart = 0; 
		}
	}
}

void compare_term_list(FILE* listfile)
{	
	char termlist[200][40];
	int ismatch[200],termlen[200],groundsearch[200];
	long matchpoint[200];
	int should_count=0;
	int i=0,j=0;
	char listterm;
	char* term;
	long charOffset=0,termOffset=0;
	char ch;
	while((listterm=fgetc(listfile))!=EOF)
	{
		if(listterm!='\n')
		{
			termlist[i][j]=listterm;
			j++;
		}
		else
		{
			term=termlist[i];
			termlen[i]=len(term);
			ismatch[i]=0;
			groundsearch[i]=0;
			j=0;
			i++;
		}
	}	
	//compare_initial(listfile);
	while((ch=getchar())!=EOF)
	{
		charOffset++;
		if(isalnum(ch))
		{
			if(should_count==0)
			{
				termOffset++;
				should_count=1;
			}
		}
		if(!isalnum(ch))
		{
			should_count=0;
		}
		for (int k = 0; k<i; k++)
		{
			term=termlist[k];
			if(ismatch[k]==0)
			{	
				if(tolower(ch)==tolower(term[groundsearch[k]]))
				{
					if(termlen[k]==1)
					{
						fprintf(stdout,"%ld,%ld,%s\n",charOffset,termOffset,term);
					}
					else
					{
						ismatch[k]=1;
						matchpoint[k]=charOffset;
					}	
				}
			}
			if(ismatch[k]==1)
			{
				if((tolower(term[groundsearch[k]]))==tolower(ch))
				{
					if(groundsearch[k]==(termlen[k]-1))
					{
						fprintf(stdout,"%ld,%ld,%s\n",matchpoint[k],termOffset,term);
						groundsearch[k]=0;
						ismatch[k]=0;
					}
					else if(groundsearch[k]<(termlen[k]-1))
					{
						++groundsearch[k];
					}
				}
				else
				{
					groundsearch[k]=0;
					ismatch[k]=0;
				}
			}
		}
	}
}

void compare_term_file(char* term,FILE* file)
{
	char ch; 				//to get every character one by one
	int term_len = len(term);		//get the term length and the new line is counted in the length
	int samepart = 0;			//the length of the same part in the two comparing words
	int isterm = 0;				//if it is a term then we should count, otherwise.
	long charOffset=0,termOffset=0,comparedchar=0;		//How many chars we have already compared in the terms.
	while ((ch = fgetc(file)) != EOF)
	{
		comparedchar++;			//Count the chars
		if (isalnum(ch) && isterm == 0)	// if it is a term then count, otherwise
		{
			termOffset++;
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
			charOffset = comparedchar - term_len;
          		fprintf(stdout,"%ld,%ld,%s\n", charOffset,termOffset,term);
          		samepart = 0; 
		}
	}
}

void compare_term_file_list(FILE* file,FILE* listfile)
{
	char termlist[200][40];
	int ismatch[200],termlen[200],groundsearch[200];
	long matchpoint[200];
	int should_count=0;
	int i=0,j=0;
	char listterm;
	char* term;
	long charOffset=0,termOffset=0;
	char ch;
	while((listterm=fgetc(listfile))!=EOF)
	{
		if(listterm!='\n')
		{
			termlist[i][j]=listterm;
			j++;
		}
		else
		{
			term=termlist[i];
			termlen[i]=len(term);
			ismatch[i]=0;
			groundsearch[i]=0;
			j=0;
			i++;
		}
	}
	while((ch=fgetc(file))!=EOF)
	{
		charOffset++;
		if(isalnum(ch))
		{
			if(should_count==0)
			{
				termOffset++;
				should_count=1;
			}
		}
		if(!isalnum(ch))
		{
			should_count=0;
		}
		for (int k = 0; k<i; k++)
		{
			term=termlist[k];
			if(ismatch[k]==0)
			{	
				if(tolower(ch)==tolower(term[groundsearch[k]]))
				{
					if(termlen[k]==1)
					{
						fprintf(stdout,"%ld,%ld,%s\n",charOffset,termOffset,term);
					}
					else
					{
						ismatch[k]=1;
						matchpoint[k]=charOffset;
					}
				}
			}
			if(ismatch[k]==1)
			{
				if((tolower(term[groundsearch[k]]))==tolower(ch))
				{
					if(groundsearch[k]==(termlen[k]-1))
					{
						fprintf(stdout,"%ld,%ld,%s\n",matchpoint[k],termOffset,term);
						groundsearch[k]=0;
						ismatch[k]=0;
					}
					else if(groundsearch[k]<(termlen[k]-1))
					{
						++groundsearch[k];
					}
				}
				else
				{
					groundsearch[k]=0;
					ismatch[k]=0;
				}
			}
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
		if (strcmp(argv[1],"-f") != 0 && strcmp(argv[1], "-l") != 0)
		{	
      			char* term = argv[1];                // get the term
			compare_term(term);
		}
		else 
		{
      			fprintf(stderr, "Could not open input file haha\n");
      			exit(1);      
   		}
  	}
	else if (argc == 3)
	{	
		FILE* listfile;
		if((strcmp(argv[1],"-l") == 0))
		{  	
			listfile = fopen(argv[2],"r");
			compare_term_list(listfile);
		}
	}
	else if (argc == 4)
	{
		FILE* file;
		char* term;
		if(strcmp(argv[1],"-f")==0)
		{
			file=fopen(argv[2],"r");
			term = argv[3];
		}
		else if (strcmp(argv[2],"-f")==0)
		{
			file=fopen(argv[3],"r");
			term = argv[2];
		}
		compare_term_file(term,file);
	}
	else if (argc == 5)
	{
		FILE* file;
		FILE* listfile;
		if (strcmp(argv[1],"-f") == 0)
		{
			file = fopen(argv[2],"r");
			listfile = fopen(argv[4],"r");
		}
		else if (strcmp(argv[1],"-l") == 0)
		{
			listfile = fopen(argv[2],"r");
			file = fopen(argv[4],"r");
		}
		compare_term_file_list(file,listfile);
	}
	return 0;
}
					




























































































































































































































