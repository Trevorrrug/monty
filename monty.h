#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * struct stack_s - doubly linked list representation of a stack
 * @n: integer
 * @prev: points to the previous element
 * @next: points to the next element
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: opcode
 * @f: function to handle the opcode
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

int is_integer(char *str);
void push(stack_t **stack, unsigned int line_number);
void pall(stack_t **stack, unsigned int line_number);
void pint(stack_t **stack, unsigned int line_number);
void free_stack(stack_t *stack);
int execute_instruction(char *opcode, stack_t **stack,
		unsigned int line_number);
int process_file(FILE *file, stack_t **stack);

#endif
