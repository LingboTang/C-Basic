#include <stdio.h>

int main() {
  char ch;
  //Why we want to define three kinds of integer?
  //Because we have to analysis three cases
  //These integers are actually boolean variables.
  int isSpaceOrTab = 0;
  int isEnter = 0;
  int isTag = 0;
  while ((ch=getchar()) != EOF) {
    //These segments are designed for cleaning target char
      //This is for cleaning ' ' and '\t'
    if (ch != ' ' || ch != '\t') {
      if ( isSpaceOrTab == 0 && isTag ==0) {
        putchar(ch);
        isSpaceOrTab = 0;
      }
      else if ( isSpaceOrTab == 1 || isTag == 1) {
        if ( isSpaceOrTab == 1 && isTag == 0){ 
        isSpaceOrTab = 1;
        }
        else if ( isSpaceOrTab == 0 && isTag == 1){
        isTag = 1;
        }
      }
    }
      //This step is to clean the tag
    else if (ch == '<' || ch == '>') {
      if ( ch == '<' ) {
      isTag = 1;
      }
      else if (ch == '>') {
      isTag = 0;
      }
    }
      //This step is to clean the '\n'
    else if (ch == '\n' && isTag == 0) {
      if ( isEnter == 0) { 
        putchar('\n');
        isEnter = 1;
      }
      else if (isEnter == 1) {
        isEnter ==  1;
      }
    }
      //This step is to put the chars
     else if ( ch != '<' && ch != '>' && ch != ' ' && ch != '\t' && ch != '\n') {
       if (isTag == 0) {
         putchar = (ch);
         isEnter = 0;
         isSpaceOrTab = 0;
       }
     }
  return 0;
}
