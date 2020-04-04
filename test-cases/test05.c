#include <stdio.h>
#define NUM 4

int foo(int k)
{
	return k * k;
}

int main(void)
{
	printf("%d\n", foo(NUM));
	return 0;
}