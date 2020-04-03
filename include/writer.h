// Sachin Shah
// April 1, 2020
// Write obfuscated c files

#ifndef _WRITER_H
#define _WRITER_H

#include "parser.h"

#include <stdio.h>
#include <stdint.h>
#include <regex.h>

#define BUFFER_SIZE 1024

void chomp(char *str);
void strip(char *str);
void trim(char *str);

char *asm_to_hex(asm_function_t *function);

char *get_substring(char *str, uint32_t start, uint32_t end);

int8_t match(regex_t *re, regmatch_t *groups, size_t n_groups, char *str);

char *get_param_types(char *params, regex_t *re, regmatch_t *groups, size_t n_groups);
void clear_comments(char *input);

void write_c(char *input, FILE *output, asm_function_t *functions);


#endif