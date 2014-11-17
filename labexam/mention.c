#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <assert.h>
#include "memwatch.h"


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

void compare_term(char* term,long totalchar,char*textlist)
{
	int term_len = len(term);
	int samepart = 0;
	int isterm = 0;
	long charOffset = 0,termOffset= 0;
	long text_i = 0;
	int notalnum =0;
	while (text_i < totalchar-1)
	{	
		if (isalnum(textlist[text_i]) && isterm == 0)
		{
			termOffset++;
			isterm = 1;
		}
		if(!isalnum(textlist[text_i]))
		{
			isterm = 0;
		}
		if (samepart != term_len)
		{
			if (lower_case(textlist[text_i]) == lower_case(term[samepart]))
			{
				charOffset = text_i;
				samepart++;
				if(!isalnum(textlist[text_i]))
				{
					notalnum = 1;
					termOffset = termOffset - notalnum;
				}
			}
			else
			{
				charOffset = 0;
				samepart = 0;
			}
		}
		else
		{
			charOffset = text_i - term_len+1;
			fprintf(stdout, "%ld,%ld,%s\n",charOffset, termOffset,term);
			samepart = 0;
		}
		text_i++;
	}
	free(textlist);
}
				


void compare_term_list(FILE* listfile, long totalchar,char*textlist)
{	
	int listcontainer = text_ini;
	int term_len = line_ini;
	int shouldcount=0;
	int list_i=0,term_i=0;
	char listterm_ch;
	char** listterm;
	listterm = malloc(listcontainer*sizeof(char*));
	assert(listterm);
	memset(listterm,0,listcontainer+1);
	listterm[list_i] = malloc((term_len+1)*sizeof(char));
	assert(listterm[list_i]);
	memset(listterm[list_i],0,term_len+1);
	long charOffset=0,termOffset=0;
	int afterlen_list;
	int readindex = 0;
	int readindex_list = 0;
	while((listterm_ch=fgetc(listfile))!=EOF)
	{	
		if (listterm_ch != '\n')
		{
			listterm[list_i][term_i] = listterm_ch;
			term_i++;
		}
		else if (listterm_ch == '\n')
		{
			list_i++;
			term_len = term_i;
			if ((list_i) == listcontainer -1)
			{
				listcontainer = listcontainer*2;
				listterm = realloc(listterm, listcontainer*sizeof(char*));
				assert(listterm);
				afterlen_list = listcontainer/2+1;
				memset(listterm+afterlen_list-2,0,(afterlen_list)*sizeof(char*));
			}
			listterm[list_i] = malloc((term_len+1)*sizeof(char));
			assert(listterm[list_i]);
			memset(listterm[list_i],0,term_len+1);
			term_i = 0;
		}
	}
	int totalterm = list_i;
	while (readindex < sizeof(textlist)/sizeof(char*))
	{	
		if (isalnum(textlist[readindex]) && shouldcount == 0)
		{
			termOffset++;
			shouldcount = 1;
		}
		if (!isalnum(textlist[readindex]))
		{
			shouldcount = 0;
		}
		while (readindex_list < totalterm)
		{	
			if (strncasecmp(textlist,listterm[readindex_list],readindex-len(listterm[readindex_list])) ==0)
			{	
				charOffset = charOffset+len(listterm[readindex_list]);
				termOffset = readindex;
				fprintf(stdout,"%ld,%ld,%s\n",charOffset,termOffset,listterm[readindex_list]);
			}
			else
			{
				readindex_list++;
			}
		}
		readindex_list = 0;
		readindex++;
	}
	free(textlist);
	free(listterm);
}

void compare_term_target(char*term,char*target)
void compare_term_target_list_default(char*term,char*target,FILE*checklist)
void compare_term_target_radius(FILE*term,char*target,FILE*checklist,int radius)


int main(int argc, char* argv[])
{
	int m = 0;
	int getoption =0;
	FILE* file =NULL;
	int container = text_ini;
	FILE* checklist =NULL;
	char* term =NULL;
	char* target = NULL;
	int radius = -10;
	char*textlist;
	textlist = malloc(container*sizeof(char));
	assert(textlist);
	memset(textlist,0,container+1);
	char ch;
	long i = 0;
	FILE* text;
	for (m=0; m<argc; m++)
	{
		if(argv[m][0] == '-')
		{
			if (len(argv[m])==2)
			{
				getoption =1;
				switch(argv[m][1])
				{
					case 'f':
						text = fopen(argv[m+1],"r");
					case 'l':
						list = fopen(argv[m+1],"r");
					case 'b':
						target = (argv[m+1]);
					case 't':
						radius = atoi(argv[m+1]);
					case 'c':
						radius = atoi(argv[m+1]);
					case NULL:
						getoption = 0;
				}
			}
			else if (len((argv[m]))>2)
			{	
				switch(argv[m][1])
				{
					case 'f':
						text = fopen(argv[m]+2,"r");
					case 'l':
						list = fopen(argv[m]+2,"r");
					case 'b':
						target = (argv[m]+2);
					case 't':
						radius = atoi(argv[m]+2);
					case 'c':
						radius = atoi(argv[m]+2);
					case NULL:
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
	if (file == NULL)
	{
		text = stdin;
	}
	if (file != NULL)
	{
		text = file;
	}
	long totalchar;
	int afterlen;
	while ((ch = fgetc(text))!=EOF)
	{	
		textlist[i] = lower_case(ch);
		i++;
		if (i == container-1)
		{
			container = container * 2;
			textlist = realloc(textlist, container*sizeof(char));
			assert(textlist);
			afterlen = container/2+1;
			memset(textlist+afterlen-2,0,afterlen);
		}
	}
	totalchar = i;
	if (checklist == NULL && target == NULL)
	{
		compare_term(term,totalchar,textlist);
	}
	if (checklist == NULL && target != NULL)
	{
		compare_term_target(term,target);
	}
	if (checklist != NULL && target == NULL)
	{
		compare_term_list(checklist,totalchar,textlist);
	}
	if (checklist != NULL && target != NULL)
	{	
		if (radius < 0)
		{
			radius = 5;
			compare_term_target_list_default(term,target,checklist);
		}
		if (radius >= 0)
		{
			compare_term_target_radius(term,target,checklist,radius);
		}
	}
	if (text!= NULL)
	{
		fclose (text);
	}
	if (checklist != NULL)
	{
		fclose (checklist);
	}
	return 0;
}
