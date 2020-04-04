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
#include <unistd.h>

int main(int argc, char **argv)
{
	FILE *binfile = NULL, *outfile = NULL;
	asm_function_t *functions = NULL;
	char *cfile = NULL, *command = NULL, *c_name = NULL;
	size_t length;
	int opt;
	uint8_t compile_flag = 0;

	if (argc < 2) error("Too few arguments. Please enter a filename.");

	while ((opt = getopt(argc, argv, ":o:b:")) != -1)
	{
		switch (opt)
		{
			case 'o':
				outfile = fopen(optarg, "w");
				break;
			case 'b':
				binfile = open_binary(optarg);
				break;
			case ':':
				printf("Option needs value.\n");
				break;
			case '?':
				printf("Unknown option.\n");
				break;
		}
	}

	if (optind < argc) c_name = argv[optind];
	else error("Enter a .c file");

	cfile = open_c(c_name);

	// Compile binary file
	if (binfile == NULL)
	{
		length = strlen(c_name);
		command = (char *) calloc(sizeof(char), 22 + length);
		sprintf(command, "gcc %s", c_name);
		system(command);
		free(command);

		binfile = open_binary("a.out");
		compile_flag = 1;
	}

	if (outfile == NULL) outfile = fopen("out.c", "w");

	functions = parse_asm(binfile);
	
	clear_comments(cfile);
	write_c(cfile, outfile, functions);

	free(cfile);
	fclose(outfile);
	fclose(binfile);

	// Clean up extra a.out
	if (compile_flag) system("rm a.out");

	return 0;
}