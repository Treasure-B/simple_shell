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
int result;
char *cmd_path = args[0];

if (is_exit(args[0]))
{
free_args(args);
return (0);
}

if (is_env(args[0]))
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
char *path_dup = strdup(path);
if (path_dup == NULL)
{
perror("strdup");
exit(EXIT_FAILURE);
}
result = search_paths(path_dup, args);
free(path_dup);
if (result != -1)
return (result);
}
}
printf("command not found: %s\n", args[0]);
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

