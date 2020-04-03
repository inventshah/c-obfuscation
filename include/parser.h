// Sachin Shah
// April 1, 2020
// Parse binary files

#ifndef _PARSER_H
#define _PARSER_H

#include <stdio.h>
#include <stdint.h>

struct instruction
{
	uint8_t instruction;
	struct instruction *next;
};

typedef struct instruction instruction_t;

struct asm_function
{
	instruction_t *instructions;
	uint32_t size;
	struct asm_function *next;
};

typedef struct asm_function asm_function_t;

instruction_t *create_instruction(uint8_t byte, instruction_t *last);

asm_function_t *create_function(void);

asm_function_t *parse_asm(FILE* bin);

#endif