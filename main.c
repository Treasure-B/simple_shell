#include "shell.h"

/**
* main - The entry point
*
* Return: Always 0.
*/

int main(void)
{
char *line;
char **args;
int status;

while (1)
{
printf("$ ");
line = _getline();
args = split_line(line);

status = exec(args);

free(line);
free_args(args);
}

return (0);
}
