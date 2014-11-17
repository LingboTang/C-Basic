#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct treenode {
		struct treenode * left;
		struct treenode * right;
		void * content;
};


int main()
{
	printf("%d\n",sizeof(treenode));
	return 0;
}
