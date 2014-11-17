#include <stdio.h>
 
int main()
{
      unsigned int x = 3, y = 1, sum, carry;
      sum = x ^ y; // Ex - OR x and y
      carry = x & y; // AND x and y
      while (carry != 0) {
          carry = carry << 1; // left shift the carry
	  printf("%d\n",carry);
	  //printf("%p\n",&carry);
          x = sum; // initialize x as sum
	  printf("%d\n",x);
	  //printf("%p\n",&x);
          y = carry; // initialize y as carry
	  printf("%d\n",y);
	  //printf("%p\n",&y);
          sum = x ^ y; // sum is calculated
	  printf("%d\n",sum);
	  //printf("%p\n",&sum);
          carry = x & y; /* carry is calculated, the loop condition is 
                            evaluated and the process is repeated until 
                            carry is equal to 0.
                          */
	  printf("%d\n",carry);
	  //printf("%p\n",&carry);
      }
      printf("%d\n", sum); // the program will print 4
      //printf("%p\n",&sum);
      return 0;
}
