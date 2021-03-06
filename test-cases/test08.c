#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void swap(int *a, int *b);

int main(void)
{
	int a = 1;
	int b = 2;

	printf("(%d, %d)\n", a, b);

	swap(&a, &b); // swap a and b

	printf("(%d, %d)\n", a, b);

	return 0;
}


void swap(int *a, int *b)
{
	int t = *a; // temp variable
	*a = *b;
	*b = t;
}