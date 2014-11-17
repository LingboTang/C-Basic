#include <stdio.h>


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
	bitsop(8);
}
