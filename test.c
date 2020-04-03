/* easy */
#include <stdio.h>

// swap function
void foo(int *a, int *b)

{
	int t = *a;
	*a = *b;
	*b = t;
}

int thing();

/*
	LONG BLOCK
	!@#$%^&*() sjdflkjasdlf
	rjqwoerij` ~~` lk`j`kl

*/

int main(void) {
	int a = 1;
	int b = 2; ///// inline coment

	printf("(%d, %d)\n", a, b);
	printf("%d\n", thing());
	foo(&a, &b);

	printf("(%d, %d)\n", a, b);

	return 0;
}

int thing()
{
	return 3;
}
