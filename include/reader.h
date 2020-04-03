// Sachin Shah
// April 1, 2020
// Read binary and .c files

#ifndef _READER_H
#define _READER_H

#include <stdio.h>
#include <stdint.h>

FILE *open_binary(char *filename);

uint8_t get_next_byte(FILE *file);

int move_to_next_asm(FILE *file);

char *open_c(char *filename);

#endif