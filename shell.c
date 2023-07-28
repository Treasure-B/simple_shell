#include "shell.h"

#define READ_SIZE 1024

/**
* exec - Execute a command
* @args: An array of arguments.
*
* Return: 1 on success, 0 if the command is not found.
*/

int exec(char **args)
{
	pid_t pid, wpid;
	int status;
	char *cmd_path;

	cmd_path = args[0];

	if (is_exit(args[0]))
	{
		free_args(args);
		return (0);
	}
	else if (is_env(args[0]))
	{
		print_env();
		free_args(args);
		return (1);
	}
	if (strchr(args[0], '/') != NULL)
	{
		if (access(cmd_path, X_OK) == 0)
			return (exec_command(cmd_path, args));
	}
	else
	{
		char *path = getenv("PATH");

		if (path != NULL)
		{
			char *token, *path_dup = strdup(path);

			if (path_dup == NULL)
			{
				perror("strdup");
				exit(EXIT_FAILURE);
			}

			token = strtok(path_dup, ":");
			while (token != NULL)
			{
				cmd_path = malloc(strlen(token) + strlen(args[0]) + 2);
				if (!cmd_path)
				{
					perror("malloc");
					exit(EXIT_FAILURE);
				}
				sprintf(cmd_path, "%s/%s", token, args[0]);
				if (access(cmd_path, X_OK) == 0)
				{
					free(path_dup);
					return (exec_command(cmd_path, args));
				}
				free(cmd_path);
				token = strtok(NULL, ":");
			}
			free(path_dup);
		}
	}
	printf("Command not found: %s\n", args[0]);
	return (1);
}

/**
* exec_command - Execute a command with its arguments.
* @cmd_path: path of the command.
* @args: An array of arguments.
*
* Return: 1 on success, 0 on failure.
*/

int exec_command(char *cmd_path, char **args)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd_path, args, environ) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (1);
}

/**
* is_exit - Checks if command is "exit".
* @cmd: command entered by the user.
*
* Return: 1 if the command is "exit", 0 otherwise.
*/

int is_exit(char *cmd)
{
	return (strcmp(cmd, "exit") == 0);
}

/**
* is_env - Checks if command is "env".
* @cmd: command entered by the user.
*
* Return: 1 if the command is "env", 0 otherwise.
*/

int is_env(char *cmd)
{
	return (strcmp(cmd, "env") == 0);
}

