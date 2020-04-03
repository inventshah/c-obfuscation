// Sachin Shah
// April 1, 2020

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <regex.h>

#include "utils.h"
#include "parser.h"
#include "reader.h"
#include "writer.h"

#include <string.h>

int main(int argc, char **argv)
{
	FILE *file = open_binary("a.out");

	asm_function_t *fnct = parse_asm(file);

	instruction_t *i = fnct->instructions;

	// while (fnct != NULL)
	// {
	// 	printf("hex: \"%s\"\n", asm_to_hex(fnct));
	// 	fnct = fnct->next;
	// }
	
	char *ifp = open_c("test.c");
	clear_comments(ifp);
	FILE *ofp = fopen("out.c", "w");

	write_c(ifp, ofp, fnct);

	free(ifp);
	fclose(ofp);
	fclose(file);

	return 0;
}