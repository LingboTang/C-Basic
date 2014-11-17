#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <assert.h>
//#include "memwatch.h"

#define line_ini 10
#define text_ini 40

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

void compare_term_target(char* term,char*target)
{
	char ch;
	char*text;
	int container = text_ini;
	int i = 0;
	text = malloc(container*sizeof(char));
	assert(text);
	memset(text,0,container);
	int isterm = 0;
	int termOffset = 0;
	while ((ch=getchar()) !=EOF)
	{	
		text[i] = lower_case(ch);
		i++;
		if (i == container-1)
		{
			container*= 2;
			text = realloc(text, container*sizeof(char));
			assert(text);
			memset(text+(container/2)-1,0,container/2+1);
		}
		if (isalnum(text[i]))
		{
			count_term = 1;
			termOffset++;
		}
		if (!isalnum(text[i]))
		{
			count_term = 0;
		}
		if (strncmp((text+i),target,len(target))==0)
		{
			long groundindex = 0;
			if
	}
}

/*void compare_term_target(char* term,char* target)
{
	char ch; 				//to get every character one by one
	int term_len = len(term);		//get the term length and the new line is counted in the length
	int samepart = 0;			//the length of the same part in the two comparing words
	int isterm = 0;				//if it is a term then we should count, otherwise.
	long charOffset=0,termOffset=0,comparedchar=0;		//How many chars we have already compared in the terms.
	int targetlen = len(target);
	int istarget = 0;
	int terOffset[200];
	int tarOffset[200];
	int terOffsetc[200];
	int i = 0;
	int terminal1= 0;
	int terminal2= 0;
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
			terOffset[i] = termOffset;
			terOffsetc[i] = charOffset;
			i++;
          		samepart = 0; 
		}
	}
	terminal1 = i;
	int j =0;
	comparedchar = 0;
	samepart = 0;
	charOffset = 0;
	termOffset = 0;
	i = 0;
	while ((ch = getchar()) != EOF)
	{
		comparedchar++;
		printf("%d\n",comparedchar);
		if (isalnum(ch) && istarget == 0)
		{
			termOffset++;
			istarget =1;
		}
		if (!isalnum(ch))
		{
			istarget = 0;
		}
		if (samepart != targetlen)
		{
			if (lower_case(ch) == lower_case(term[samepart]))
			{
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
			printf("%s\n","shit");
			charOffset = comparedchar - targetlen;
			tarOffset[j] = termOffset;
			j++;
			samepart = 0;
		}
	}
	terminal2 = j;
	i = 0;
	int k;
	printf("%s\n","abcd");
        printf(" 123 %d\n",terminal2);
	while (k < terminal2)
	{       
                printf("%s\n","abcd");
		if ((tarOffset[k] - terOffset[k] == 5) || (terOffset[k] - tarOffset[k] == 5))
		{       
			printf("aslkdfjalksfj\n");
			printf("%d,%d,%s\n",terOffsetc[k],terOffset[k],term);
		}
		k++;
	}
}*/

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
	char list_ch;
	char**termlist;
	int list_i = 0;
	int term_i = 0;
	int list_container = text_ini;
	int termlen = 0;
	termlist = malloc(list_container*sizeof(char*));
	assert(termlist);
	memset(termlist,0,list_container+1);
	termlist[list_i] = malloc(line_ini*sizeof(char));
	assert(termlist[list_i]);
	memset(termlist[list_i],0,line_ini+1);
	while((list_ch = fgetc(listfile)) !=EOF)
	{	
		if (list_ch != '\n')
		{
			termlist[list_i][term_i] = list_ch;
			term_i++;
		}
		else if (list_ch == '\n')
		{	
			termlen = term_i;
			list_i++;
			if(list_i == list_container-1)
			{
				list_container*=2;
				termlist = realloc(termlist,list_container*sizeof(char*));
				assert(termlist);
				memset(termlist+((list_container/2)-1),0,(((list_container/2)+1)*sizeof(char*)));
			}
			termlist[list_i] = malloc((termlen+1)*sizeof(char));
			assert(termlist[list_i]);
			memset(termlist[list_i],0,termlen+1);
			term_i = 0;
		}
	}
}



















/*int main(int argc, char* argv[])
{
	FILE* text;
	FILE* list;
	char* term;
	char* target;
	int* radius;
	int getoption = 0;
	printf("argc: %d\n",argc);
	for (int i=1; i<argc; i++)
	{
		if (argv[i][0] != '-')
		{
			getoption = 0;
		}
		if (argv[i][0] == '-')
		{
			getoption = 1;
		}
		if (getoption == 0)
		{
			term = argv[i];
		}
		if (getoption == 1)
		{
			switch (argv[i][1])
			{
				case 'f':
					text = fopen(&(argv[i][1]),"r");
				case 'l':
					list = fopen(&(argv[i][1]),"r");
				case 'b':
					target = &(argv[i+1][1]);
				case 't':
					radius = atoi((argv[i][1]));
				case 'c':
					radius = atoi((argv[i][1]));
			}
			switch (argv[i][2])
			{
				case 'f':
					text = fopen(&(argv[i][2]),"r");
				case 'l':
					list = fopen(&(argv[i][2]),"r");
				case 'b':
					target = &(argv[i+1][2]);
				case 't':
					radius = atoi((argv[i][2]));
				case 'c':
					radius = atoi((argv[i][2]));
			}
		}
	}
	return 0;
}*/

int main(int argc, char* argv[])
{
	int m = 0;
	int getoption =0;
	FILE* text;
	FILE* checklist;
	char* term;
	char* target;
	int radius;
	for (m=0; m<argc; m++)
	{
		if(argv[m][0] == '-')
		{
			if (len(argv[m])==2)
			{
				getoption =1;
				if(argv[m][1] == 'f')
				{
					text = fopen(argv[m+1],"r");
				}
				else if (argv[m][1] == 'l')
				{
					checklist = fopen(argv[m+1],"r");
				}
				else if (argv[m][1]=='b')
				{
					target = argv[m+1];
				}
				else if (argv[m][1] == 'c')
				{
					radius = atoi(argv[m+1]);
				}
				else if (argv[m][1] == 't')
				{
					radius = atoi(argv[m+1]);
				}
				else
				{
					getoption = 0;
				}
			}
			else if (len((argv[m]))>2)
			{
				if (argv[m][1] =='f')
				{
					text = fopen(argv[m]+2,"r");
				}
				else if(argv[m][1] =='l')
				{
					checklist = fopen(argv[m]+2,"r");
				}
				else if(argv[m][1] == 'b')
				{
					target = argv[m]+2;
				}
				else if(argv[m][1]== 'c')
				{
					radius = atoi(argv[m]+2);
				}
				else if(argv[m][1] =='t')
				{
					radius = atoi(argv[m]+2);
				}
				else
				{
					term = argv[m];
				}
			}
		}
		else
		{
			if(getoption == 0)
			{
				term = argv[m];
			}
			else if (getoption == 1)
			{
				getoption = 0;
			}
		}
	}
	compare_term_target(term,target);
	compare_term_file_list(text,checklist);
	return 0;
}
