#include "monty.h"

/**
 * push - Pushes an element onto the stack.
 * @stack: Pointer to the top of the stack
 * @line_number: Line number in the bytecode file
 */
void push(stack_t **stack, unsigned int line_number)
{
	char *num_str = strtok(NULL, " \n");
	
	if (num_str == NULL)
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	
	int num = atoi(num_str);
	
	if (num == 0 && strcmp(num_str, "0") != 0)
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	stack_t *new_node = malloc(sizeof(stack_t));

	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	new_node->n = num;
	new_node->prev = NULL;
	new_node->next = *stack;

	if (*stack != NULL)
		(*stack)->prev = new_node;

	*stack = new_node;
}

/**
 * pall - Prints all values on the stack.
 * @stack: Pointer to the top of the stack
 * @line_number: Line number in the bytecode file
 */
void pall(stack_t **stack, unsigned int line_number)
{
	(void)line_number;

	stack_t *current = *stack;

	while (current != NULL)
	{
		 printf("%d\n", current->n);
		  current = current->next;
	}
}
