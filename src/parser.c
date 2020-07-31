// Sachin Shah
// April 1, 2020

#include "parser.h"
#include "reader.h"
#include "utils.h"
#include "asm.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

instruction_t *create_instruction(uint8_t byte, instruction_t *last)
{
	instruction_t *instruction = (instruction_t *) calloc(sizeof(instruction_t), 1);
	check_null(instruction, "calloc failed to find space for an instruction");

	instruction->instruction = byte;
	if (last != NULL) last->next = instruction;

	return instruction;
}

asm_function_t *create_function(void)
{
	asm_function_t *function = (asm_function_t *) calloc(sizeof(asm_function_t), 1);
	check_null(function, "calloc failed to find space for an asm function");

	function->instructions = create_instruction(ASM_START, NULL);
	function->size = 1;
	
	return function;
}

asm_function_t *parse_asm(FILE* bin)
{
	asm_function_t *root = NULL, *function = NULL;
	instruction_t *instruction = NULL;
	uint8_t byte = 0, flag = 1;

	move_to_first_asm(bin);

	while (flag)
	{
		if (root == NULL)
		{
			function = create_function();
			root = function;
		}
		else
		{
			function->next = create_function();
			function = function->next;
		}

		instruction = function->instructions;

		do
		{
			byte = get_next_byte(bin);

			instruction = create_instruction(byte, instruction);
			function->size++;
		} while (feof(bin) == 0 && byte != ASM_END);

		flag = move_to_next_asm(bin);
	}

	return root;
}
