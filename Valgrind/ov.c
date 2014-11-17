#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
  char *buf = malloc( 3 );
  strcpy( buf, "012345" );
  printf("buf: %s\n", buf );
  return 0;
}
