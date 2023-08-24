#include "monty.h"

/**
 * get_op_func - Selects the correct function to perform the operation.
 * @opcode: The operation code to check
 * @line_number: Line number in the bytecode file
 * @stack: Pointer to the top of the stack
 */
void (*get_op_func(char *opcode))(stack_t **stack, unsigned int line_number)
{
	instruction_t instructions[] = {
		{"push", push},
		{"pall", pall},
		{NULL, NULL}
	};

	int i = 0;

	while (instructions[i].opcode != NULL)
	{
		if (strcmp(instructions[i].opcode, opcode) == 0)
			return (instructions[i].f);

		i++;
	}

	return (NULL);
}

/**
 * main - entry point
 *
 * @argc: an integer
 * @argv: array pointer of type char
 * Return: always (0) success
 */
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <bytecode_file>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	FILE *bytecode_file = fopen(argv[1], "r");

	if (bytecode_file == NULL)
	{
		fprintf(stderr, "Error: Could not open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}

	stack_t *stack = NULL;
	char *line = NULL;
	size_t len = 0;
	unsigned int line_number = 0;

	while (getline(&line, &len, bytecode_file) != -1)
	{
		line_number++;
		char *opcode = strtok(line, " \n");
		if (opcode != NULL && opcode[0] != '#')
		{
			void (*op_func)(stack_t **, unsigned int);
			op_func = get_op_func(opcode);
			if (op_func == NULL)
			{
				fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
				free(lin);
				fclose(bytecode_file);
				free_stack(&stack);
				return (EXIT_FAILURE);
			}
			op_func(&stack, line_number);
		}
	}

	free(line);
	fclose(bytecode_file);
	free_stack(&stack);
	return (EXIT_SUCCESS);
}
