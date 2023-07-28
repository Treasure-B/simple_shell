#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

char *_getline(void);
static char *_ini_buffer(ssize_t *chars_read);
static ssize_t _read_input(char *buffer);
char **split_line(char *line);
int exec(char **args);
int exec_command(char *cmd_path, char **args);
int is_exit(char *cmd);
int is_env(char *cmd);
void print_env(void);
void free_args(char **args);

#endif

