// CMPUT 201 / Fall 2013 - sample code
// Written by: Davood Rafiei

#include <stdio.h>

int main()
{
  char Firstname[20],Lastname[20];

  printf("What is your Firstname? ");
  scanf("%s", Firstname);
  printf("What is your Lastname? ");
  scanf("%s", Lastname);
  printf("%s %s",Firstname,Lastname);
}

