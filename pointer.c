#include <stdio.h>
int main()
{
	int ar[] = {1,2,3,4};
	int* ptr = &ar[3];
	int** ptrPtr = &ptr;
	(*ptrPtr)--;
	**ptrPtr = 9;
	for (int i = 0; i < 4; i++)
		printf("a[%d]:%d\n",i,ar[i]);
	return 0;
}
