#include "shell.h"
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
