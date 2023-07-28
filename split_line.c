#include "shell.h"

/**
 * split_line - Split the input line into individual arguments.
 * @line: The input line.
 *
 * Return: An array of arguments or NULL on failure.
 */

char **split_line(char *line)
{
	char **tokens = NULL;
	char *token;
	int position = 0;
	const char *delimiters = " \t\r\n\a";
	size_t bufsize = 64;

	tokens = malloc(bufsize * sizeof(char *));
	if (!tokens)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, delimiters);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, delimiters);
	}
	tokens[position] = NULL;
	return (tokens);
}

/**
 * free_args - Free the memory allocated
 * @args: An array of arguments.
 */

void free_args(char **args)
{
	if (args)
	{
		for (int i = 0; args[i]; i++)
		{
			free(args[i]);
		}
		free(args);
	}
}
