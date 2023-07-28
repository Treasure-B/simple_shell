#include "shell.h"

/**
* search_paths - Search for the command in the directories
* @path: The 'PATH' environment variables
* @args: An array of arguments
* Return: 1 on success, or or -1 if the command is not found
*/

int search_paths(char *path, char **args)
{
char *token = strtok(path, ":");
while (token != NULL)
{
char *cmd_path = create_cmd_path(token, args[0]);
if (cmd_path == NULL)
{
perror("malloc");
exit(EXIT_FAILURE);
}

if (access(cmd_path, X_OK) == 0)
{
int result = exec_command(cmd_path, args);
free(cmd_path);
return (result);
}

free(cmd_path);
token = strtok(NULL, ":");
}

return (-1);
}

/**
* create_cmd_path - Create the full path of the command
* @path: A directory path from the 'PATH' environment variable
* @cmd: The command name to be executed
* Return: string containing the full path,
* or exits the shell
*/

char *create_cmd_path(char *path, char *cmd)
{
char *cmd_path = malloc(strlen(path) + strlen(cmd) + 2);
if (!cmd_path)
{
perror("malloc");
exit(EXIT_FAILURE);
}
sprintf(cmd_path, "%s/%s", path, cmd);
return (cmd_path);
}
