#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include <stdlib.h>
int main(int argc,char *argv[]){
	FILE* input;
	FILE* list;
	long charOffset=0,termOffset=0,mark_cOs=0;
	if(argc==2){
		char* word=argv[1];
	    int len=strlen(word);
		char in;
		int count_term=0;
		int index=0;
		int keep_matching=0;
		while((in=getchar())!=EOF){
		    charOffset++;
		    if(isalnum(in)){
		    	if(count_term==0){
		    		termOffset++;
		    		count_term=1;
		    	}
		    }
		    if((keep_matching==0)&&((tolower(word[index]))==(tolower(in)))){
		    	if(len==1){
		    		fprintf(stdout,"%ld,%ld,%s\n",charOffset,termOffset,word);
		    	}
		    	else{
		    		keep_matching=1;
		    		mark_cOs=charOffset;
		    	}
		    }
		    if(keep_matching==1){
		    	if((tolower(word[index]))==(tolower(in))){
		    		if(index==(len-1)){
		    			fprintf(stdout,"%ld,%ld,%s\n",mark_cOs,termOffset,word);
		    			index=0;
		    			keep_matching=0;
		    		}
		    		else if(index<(len-1)){
		    			index++;
		    		}
		    	}
		    	else{
		    		index=0;
		    		keep_matching=0;
		    	}
		    }
			if(!isalnum(in)){
			    count_term=0;
			}
		}
	}
	else if (argc==3){
		if(strcmp(argv[1],"-l")==0){
			list=fopen(argv[2],"r");
			char array[200][40];
			int sw_keep_matching[200],len_record[200],term_index[200];
			long mark_cOs[200];
			int count_term=0;
			int array_process;
			int array_index=0,word_index=0;
			char list_in;
			char* word;
			while((list_in=fgetc(list))!=EOF){
				if(list_in!='\n'){
					array[array_index][word_index]=list_in;
					word_index++;
				}
				else{
					word=array[array_index];
					len_record[array_index]=strlen(word);
					sw_keep_matching[array_index]=0;
					term_index[array_index]=0;
					word_index=0;
					array_index++;
				}
			}
			char in;
			while((in=getchar())!=EOF){
				//starts here
				charOffset++;
				if(isalnum(in)){
					if(count_term==0){
						termOffset++;
						count_term=1;
					}
				}
				if(!isalnum(in)){
					count_term=0;
				}
				array_process=0;
				while(array_process<array_index){
					word=array[array_process];
					if((sw_keep_matching[array_process]==0)&&(tolower(in)==tolower(word[term_index[array_process]]))){
						if(len_record[array_process]==1){
							fprintf(stdout,"%ld,%ld,%s\n",charOffset,termOffset,word);
						}
						else{
							sw_keep_matching[array_process]=1;
							mark_cOs[array_process]=charOffset;
						}
					}
					if(sw_keep_matching[array_process]==1){
						if((tolower(word[term_index[array_process]]))==tolower(in)){
							if(term_index[array_process]==(len_record[array_process]-1)){
								fprintf(stdout,"%ld,%ld,%s\n",mark_cOs[array_process],termOffset,word);
								term_index[array_process]=0;
								sw_keep_matching[array_process]=0;
							}
							else if(term_index[array_process]<(len_record[array_process]-1)){
								term_index[array_process]++;
							}
						}
						else{
							term_index[array_process]=0;
							sw_keep_matching[array_process]=0;
						}
					}
					array_process++;
				}
				//ends here
			}
        }
    }
    else if (argc==4){
    	char* word;
    	if(strcmp(argv[1],"-f")==0){
    		input=fopen(argv[2],"r");
    		word=argv[3];
    	}
    	else if(strcmp(argv[2],"-f")==0){
    		input=fopen(argv[3],"r");
    		word=argv[1];
    		
    	}
    	input=fopen(argv[2],"r");
    	char in;
    	int len=strlen(word);
    	int count_term=0;
        int index=0;
		int keep_matching=0;
		while((in=fgetc(input))!=EOF){
		    charOffset++;
		    if(isalnum(in)){
		    	if(count_term==0){
		    		termOffset++;
		    		count_term=1;
		    	}
		    }
		    if((keep_matching==0)&&((tolower(word[index]))==(tolower(in)))){
		    	if(len==1){
		    		fprintf(stdout,"%ld,%ld,%s\n",charOffset,termOffset,word);
		    	}
		    	else{
		    		keep_matching=1;
		    		mark_cOs=charOffset;
		    	}
		    }
		    if(keep_matching==1){
		    	if((tolower(word[index]))==(tolower(in))){
		    		if(index==(len-1)){
		    			fprintf(stdout,"%ld,%ld,%s\n",mark_cOs,termOffset,word);
		    			index=0;
		    			keep_matching=0;
		    		}
		    		else if(index<(len-1)){
		    			index++;
		    		}
		    	}
		    	else{
		    		index=0;
		    		keep_matching=0;
		    	}
		    }
			if(!isalnum(in)){
			    count_term=0;
			}
		}
    	
    }
    //last 2 cases handle
    else if(argc==5){
    	if(strcmp(argv[1],"-f")==0){
    		input=fopen(argv[2],"r");
    		list=fopen(argv[4],"r");
    	}
    	else if(strcmp(argv[1],"-l")==0){
    		input=fopen(argv[4],"r");
    		list=fopen(argv[2],"r");
    	}
    	char array[200][40];
		int sw_keep_matching[200],len_record[200],term_index[200];
		long mark_cOs[200];
		int count_term=0;
		int array_process;
		int array_index=0,word_index=0;
		char list_in;
		char* word;
		while((list_in=fgetc(list))!=EOF){
			if(list_in!='\n'){
				array[array_index][word_index]=list_in;
				word_index++;
			}
			else{
				word=array[array_index];
				len_record[array_index]=strlen(word);
				sw_keep_matching[array_index]=0;
				term_index[array_index]=0;
				word_index=0;
				array_index++;
			}
		}
		char in;
		while((in=fgetc(input))!=EOF){
			charOffset++;
			if(isalnum(in)){
				if(count_term==0){
					termOffset++;
					count_term=1;
				}
			}
			if(!isalnum(in)){
				count_term=0;
			}
			array_process=0;
			while(array_process<array_index){
				word=array[array_process];
				if((sw_keep_matching[array_process]==0)&&(tolower(in)==tolower(word[term_index[array_process]]))){
					if(len_record[array_process]==1){
						fprintf(stdout,"%ld,%ld,%s\n",charOffset,termOffset,word);
					}
					else{
						sw_keep_matching[array_process]=1;
						mark_cOs[array_process]=charOffset;
					}
				}
				if(sw_keep_matching[array_process]==1){
					if((tolower(word[term_index[array_process]]))==tolower(in)){
						if(term_index[array_process]==(len_record[array_process]-1)){
							fprintf(stdout,"%ld,%ld,%s\n",mark_cOs[array_process],termOffset,word);
							term_index[array_process]=0;
							sw_keep_matching[array_process]=0;
						}
						else if(term_index[array_process]<(len_record[array_process]-1)){
							term_index[array_process]++;
						}
					}
					else{
						term_index[array_process]=0;
						sw_keep_matching[array_process]=0;
					}
				}
				array_process++;
			}
		}
    }
    //end
}

