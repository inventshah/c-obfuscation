// Sachin Shah
// April 1, 2020

#include "utils.h"
#include "asm.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <regex.h>

FILE *open_binary(char *filename)
{
	FILE *fp;
	size_t size;

	fp = fopen(filename, "rb");
	check_null(fp, "Could not open binary file.");

	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	rewind(fp);

	printf("Opened %s with %zu bytes.\n", filename, size);

	return fp;
}

uint8_t get_next_byte(FILE *file)
{
	uint8_t byte = 0;
	size_t size = 0;

	size = fread(&byte, sizeof(uint8_t), 1, file);
	return byte;
}

uint16_t get_next_two_bytes(FILE *file) {
	uint16_t byte = 0;

	fread(&byte, sizeof(uint8_t), 2, file);
	printf("%d ", byte);
	return byte;
}

int move_to_next_asm(FILE *file)
{
	while (feof(file) == 0 && get_next_byte(file) != ASM_START);
	return !feof(file);
}

int move_to_first_asm(FILE *file)
{
	uint8_t last = 0, current = 0;;
	while (feof(file) == 0)
	{
		current = get_next_byte(file);
		if (last == 0x00 && current == ASM_START) break;
		last = current;
	}
	return !feof(file);
}

// header_t *get_headers(char *filename)
// {
// 	FILE *fp;
// 	char buffer[25], header[16];
// 	const char include = "#[ \t]*include[ \t]+<([a-z].h)>";
// 	regex_t re;
// 	rematch_t groups[2];
// 	header_t *headers;
// 	uint8_t i;
// 	char header_files[10][10] = {"assert.h", "ctype.h", "math.h", "setjmp.h", "signal.h", "stdarg.h", "stdio.h", "stdlib.h", "string.h"};
	
// 	headers = (header_t *) calloc(sizeof(header_t), 10);
// 	check_null(headers, "calloc failed to find space for a header");

// 	for (i = 0; i < 10; i++) strcpy(headers[i].name, header_files[i]);

// 	compile_regex(&re, include);

// 	fp = fopen(filename, "r");
// 	check_null(fp, "Could not open c file.");

// 	while ((fgets(buffer, 25, fp) != NULL))
// 	{
// 		if (match(&re, groups, 2, buffer) == 1)
// 		{
// 			memcpy(header, buffer + groups[1].rm_so, groups[1].rm_eo - groups[1].rm_so);

// 			for (i = 0; i < 10; i++)
// 			{
// 				if (strcmp(header, headers[i].name) == 0)
// 				{
// 					headers[i].has = 1;
// 					break;
// 				}
// 			}
// 		}
// 		else if (buffer[0] != '/' && buffer[0] != '#') break;
// 	}

// 	regfree(&re);

// 	return headers;
// }

char *open_c(char *filename)
{
	FILE *fp;
	size_t size;
	char *file;

	fp = fopen(filename, "r");
	check_null(fp, "Could not open c file.");

	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	rewind(fp);

	printf("Opened %s with %zu bytes.\n", filename, size);

	file = (char *) calloc(sizeof(char), size + 1);

	fread(file, sizeof(char), size, fp);
	fclose(fp);

	return file;
}
