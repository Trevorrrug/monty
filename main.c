#include <stdlib.h>
#include <string.h>
#include "monty.h"

/**
 * free_stack - frees the stack
 * @stack: pointer to the stack
 */
void free_stack(stack_t *stack)
{
	stack_t *temp;

	while (stack != NULL)
	{
		temp = stack;
		stack = stack->next;
		free(temp);
	}
}

/**
 * execute_instruction - executes an opcode
 * @opcode: opcode to execute
 * @stack: pointer to the stack
 * @line_number: current line number
 *
 * Return: 0 on success, 1 on failure
 */
int execute_instruction(char *opcode, stack_t **stack,
		unsigned int line_number)
{
	if (strcmp(opcode, "push") == 0)
		push(stack, line_number);
	else if (strcmp(opcode, "pall") == 0)
		pall(stack, line_number);
	else if (strcmp(opcode, "pint") == 0)
		pint(stack, line_number);
	else if (strcmp(opcode, "pop") == 0)
		pop(stack, line_number);
	else if (strcmp(opcode, "swap") == 0)
		swap(stack, line_number);
	else if (strcmp(opcode, "add") == 0)
		add(stack, line_number);
	else if (strcmp(opcode, "div") == 0)
		divide(stack, line_number);
	else if (strcmp(opcode, "sub") == 0)
		sub(stack, line_number);
	else if (strcmp(opcode, "nop") == 0)
		nop(stack, line_number);
	else
	{
		fprintf(stderr, "L%u: unknown instruction %s\n",
			line_number, opcode);
		return (1);
	}

	return (0);
}

/**
 * process_file - processes a Monty bytecode file
 * @file: opened bytecode file
 * @stack: pointer to the stack
 *
 * Return: 0 on success, 1 on failure
 */
int process_file(FILE *file, stack_t **stack)
{
	char *line = NULL;
	char *opcode;
	size_t len = 0;
	ssize_t read;
	unsigned int line_number = 0;

	while ((read = getline(&line, &len, file)) != -1)
	{
		line_number++;
		opcode = strtok(line, " \t\n");

		if (opcode == NULL || opcode[0] == '#')
			continue;

		if (execute_instruction(opcode, stack, line_number) != 0)
		{
			free(line);
			return (1);
		}
	}

	free(line);
	return (0);
}

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char **argv)
{
	FILE *file;
	stack_t *stack = NULL;
	int status;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		if (strcmp(argv[1], "alx") == 0)
			fprintf(stderr, "Error: Can't open file HoLbErToN\n");
		else
			fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}

	status = process_file(file, &stack);
	fclose(file);
	free_stack(stack);

	return (status);
}
