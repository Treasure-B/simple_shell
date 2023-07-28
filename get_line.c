#include "shell.h"

#define READ_SIZE 1024

/**
* _getline - Reads a line
* Return: The line read or NULL
*/

char *_getline(void)
{
static ssize_t chars_read;
static char *position;
ssize_t charact;
ssize_t line_size = 0;
char *line;

if (chars_read <= 0)
{
position = _ini_buffer(&chars_read);
}

line = malloc(READ_SIZE);
if (!line)
{
perror("malloc");
exit(EXIT_FAILURE);
}

while (*position != '\n')
{
line[line_size] = *position;
line_size++;
position++;
chars_read--;

if (chars_read == 0)
{
charact = _read_input(position = _ini_buffer(&chars_read));
if (charact <= 0)
{
free(line);
exit(EXIT_SUCCESS);
}
}
}
line[line_size] = *position;
position++;
chars_read--;

return (line);
}

/**
* _read_input - Read input
* @buffer: Stores the read input
* Return: Number of characters read or -1 on error
*/

static ssize_t _read_input(char *buffer)
{
ssize_t charact = read(STDIN_FILENO, buffer, READ_SIZE);

if (charact == -1)
{
perror("read");
}
return (charact);
}

/**
* _ini_buffer - Initialize buffer and read initial input
* @chars_read: A pointer to store the number of characters read
* Return: Pointer to the buffer or NULL
*/

static char *_ini_buffer(ssize_t *chars_read)
{
static char buffer[READ_SIZE];
ssize_t charact = _read_input(buffer);

if (charact <= 0)
{
if (charact == 0)
printf("\n");
else
perror("read");
exit(EXIT_SUCCESS);
}
*chars_read = charact;
return (buffer);
}
