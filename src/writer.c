// Sachin Shah
// April 1, 2020

#include "writer.h"
#include "parser.h"
#include "utils.h"
#include "regex_helper.h"

#include <ctype.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <regex.h>

// Regex to get functions
const char *function_regex = "(([a-zA-Z0-9_ \t\n]|\\[|\\])+[ \t\n*]*[ \t\n]+[*]*)([a-zA-Z0-9_]+)[ \t\n]*\\((([a-zA-Z0-9_ \t\n.,*]|\\[|\\])*)\\)[ \t\n]*{"; //"([a-zA-Z0-9_ \t\n\\[\\]]+[ \t\n*]*[ \t\n]+[*]*)([a-zA-Z0-9_]+)[ \t\n]*\\(([* \t\na-zA-Z0-9_,.\\[\\]]*)\\)[ \t\n]*{";
const char *declaration_regex = "(([a-zA-Z0-9_ \t\n]|\\[|\\])+[ \t\n*]*[ \t\n]+[*]*)([a-zA-Z0-9_]+)[ \t\n]*\\((([a-zA-Z0-9_ \t\n.,*]|\\[|\\])*)\\)[ \t\n]*;";
const char *type_regex = "([a-zA-Z0-9_ \t\n]+[ \t\n*]*[ \t\n]+[*]*)([a-zA-Z0-9_]+|\\[|\\])+";

// Regex to clear comments
const char *inline_regex = "\\/\\/[^\n]*\n";
const char *block_regex = "\\/\\*.*?\\*\\/";

// Remove trailing whitespace
void chomp(char *str)
{
	int i = strlen(str) - 1;

	while (isspace(str[i]) && i >= 0) str[i--] = '\0';
}

// Remove leading whitespace
void strip(char *str)
{
	int i = 0, j = 0, length = strlen(str);

	while (isspace(str[i]) && i++ < length);

	while (i <= length) str[j++] = str[i++];
}

// Remove trailing and leading whitespace
void trim(char *str)
{
	chomp(str);
	strip(str);
}

// Convert an asm functions to a hex string like "\xc3"
char *asm_to_hex(asm_function_t *function)
{
	int i = 0;
	instruction_t *instruction = function->instructions;
	char *string = (char *) calloc(sizeof(char), (function->size * 4) + 1);
	check_null(string, "failed to find space for hex string");

	while (instruction != NULL)
	{
		sprintf(string + i, "\\x%02x", instruction->instruction);
		instruction = instruction->next;
		i += 4;
	}

	return string;
}

// Return a substring from start to end
char *get_substring(char *str, uint32_t start, uint32_t end)
{
	char *substr = (char *) calloc(sizeof(char), end - start + 1);
	check_null(substr, "calloc failed to find space for substring");

	memcpy(substr, str + start, end - start);

	trim(substr);

	return substr;
}

// Convert a function parameter list in form (type name, ...) to (type, ...)
char *get_param_types(char *params, regex_t *re, regmatch_t *groups, size_t n_groups)
{
	size_t length = strlen(params);

	char *token, *type, *type_list;
	type_list = calloc(sizeof(char), length);
	check_null(type_list, "calloc failed to find space for type_list when getting param types");
	token = strtok(params, ",");
	
	while (token != NULL)
	{
		if (strcmp(token, "void") == 0)
		{
			strcat(type_list, "void");
		}
		else if (match(re, groups, n_groups, token))
		{
			type = get_substring(token, groups[1].rm_so, groups[1].rm_eo);
			trim(type);

			strcat(type_list, type);
			free(type);
		}
		token = strtok(NULL, ",");
		if (token != NULL) strcat(type_list, ",");	
	}

	trim(type_list);

	return type_list;
}

// Remove all comments from input
void clear_comments(char *input)
{
	regex_t re_inline, re_block;
	regmatch_t groups[1], inline_groups[1], block_groups[1];
	int compile_code; 
	uint8_t block_match, input_match;
	size_t n_groups;
	char *start = input, clear = '\n';

	compile_regex(&re_inline, inline_regex);
	compile_regex(&re_block, block_regex);

	while(*input != '\0')
	{
		input_match = match(&re_inline, inline_groups, 1, input);
		block_match = match(&re_block, block_groups, 1, input);

		if (input_match == 1 && block_match == 1) groups[0] = block_groups[0].rm_so < inline_groups[0].rm_so ? block_groups[0] : inline_groups[0];
		else if (input_match == 1 && block_match != 1) groups[0] = inline_groups[0];
		else if (input_match != 1 && block_match == 1) groups[0] = block_groups[0];
		else break;

		memset(input + groups[0].rm_so, clear, groups[0].rm_eo - groups[0].rm_so);
		input += groups[0].rm_eo;
	}

	regfree(&re_inline);
	regfree(&re_block);
}

// Print regular code without newlines and tabs unless required
void print_plain(char *input, FILE *output, uint32_t num, regmatch_t *groups)
{
	uint32_t i = 0, j = 0;
	uint8_t hashtag = 0;

	while (i < num || hashtag == 1)
	{
		// #define and #input lines
		if (input[i] == '#') hashtag = 1;
		
		if (input[i] != '\n' && input[i] != '\t') fprintf(output, "%c", input[i]);

		if (hashtag == 1 && input[i] == '\n')
		{
			fprintf(output, "\n");
			hashtag = 0;	
		}

		i++;
	}

	if (i > num && groups != NULL)
	{
		for (j = 0; j < 2; j++) groups[j].rm_so = i;
	}
}

// Write a c file based on asm functions
void write_c(char *input, FILE *output, asm_function_t *functions)
{
	char buffer[BUFFER_SIZE], current_char;
	char *function_name, *parameters, *parameter_types, *return_type, *hex;

	regex_t re_function, re_type, re_declaration;
	regmatch_t *function_groups, *type_groups, *declaration_groups;
	int compile_code;
	size_t n_groups_function, n_groups_type;
	uint32_t bracket_count, new_index;

	// Init regex vars
	compile_regex(&re_function, function_regex);
	compile_regex(&re_type, type_regex);
	compile_regex(&re_declaration, declaration_regex);

	n_groups_function = re_function.re_nsub + 1;
	n_groups_type = re_type.re_nsub + 1;

	function_groups = allocate_groups(n_groups_function);
	type_groups = allocate_groups(n_groups_type);
	declaration_groups = allocate_groups(n_groups_function);

	// Get the next function
	while (match(&re_function, function_groups, n_groups_function, input) == 1 && functions != NULL)
	{
		// If there is a declaration before the function, print it with the new type
		if (match(&re_declaration, declaration_groups, n_groups_function, input) == 1 && function_groups[0].rm_so > declaration_groups[0].rm_so)
		{
			print_plain(input, output, declaration_groups[0].rm_so, declaration_groups);
			return_type = get_substring(input, declaration_groups[1].rm_so, declaration_groups[1].rm_eo);
			function_name = get_substring(input, declaration_groups[3].rm_so, declaration_groups[3].rm_eo);
			parameters = get_substring(input, declaration_groups[4].rm_so, declaration_groups[4].rm_eo);
			parameter_types = get_param_types(parameters, &re_type, type_groups, n_groups_type);
			fprintf(output, "%s(*%s)(%s);", return_type, function_name, parameter_types);

			input += declaration_groups[0].rm_eo;
			free(return_type);
			free(function_name);
			free(parameters);
			free(parameter_types);
			continue;
		}
		else
		{
			print_plain(input, output, function_groups[0].rm_so, function_groups);
		}

		// Get function parts
		return_type = get_substring(input, function_groups[1].rm_so, function_groups[1].rm_eo);
		function_name = get_substring(input, function_groups[3].rm_so, function_groups[3].rm_eo);
		parameters = get_substring(input, function_groups[4].rm_so, function_groups[4].rm_eo);
		parameter_types = get_param_types(parameters, &re_type, type_groups, n_groups_type);

		// If its not the main function, convert to asm
		if (strcmp(function_name, "main") != 0)
		{
			input += function_groups[0].rm_eo;
			fprintf(output, "%s(*%s)(%s)=(%s(*)(%s))", return_type, function_name, parameter_types, return_type, parameter_types);

			bracket_count = 1;
			while ((current_char = *input) != '\0')
			{
				if (current_char == '{') bracket_count++;
				else if (current_char == '}') bracket_count--;
				input++;
				if (bracket_count == 0) break;	
			}

			hex = asm_to_hex(functions);

			fprintf(output, "\"%s\";", hex);
			free(hex);
		}
		else
		{
			input += function_groups[0].rm_so;
			print_plain(input, output, function_groups[0].rm_eo - function_groups[0].rm_so, function_groups);
			input += function_groups[0].rm_eo - function_groups[0].rm_so;
		}

		functions = functions->next;

		free(return_type);
		free(function_name);
		free(parameters);
		free(parameter_types);
	}

	print_plain(input, output, strlen(input), NULL);

	regfree(&re_function);
	regfree(&re_type);
	regfree(&re_declaration);

	free(function_groups);
	free(type_groups);
	free(declaration_groups);
}
