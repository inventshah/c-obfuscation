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

int move_to_next_asm(FILE *file)
{
	while (feof(file) == 0 && get_next_byte(file) != ASM_START);
	return !feof(file);
}

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
