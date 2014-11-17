#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define size_n 20
int bitsop(unsigned int *n) {
    unsigned int m = *n;
    int cnt=0;
    while (m != 0) {
      cnt += (m & 0x01) ? 1:0;
      m = m >> 1;
    }
    *n = *n ^ 0xffffffff;
    return cnt;
}


int main()
{
	unsigned int *n;
	n = malloc(size_n*sizeof(unsigned int));
	memset(n,0,size_n+1);
	*n = 1111;
	printf("%d\n",bitsop(n));
	return 0;
}
