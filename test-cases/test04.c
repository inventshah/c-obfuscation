#include <stdio.h>

int foo(int k) { return k * k; }

int main(void)
{
	printf("%d\n", foo(5));
	return 0;
}