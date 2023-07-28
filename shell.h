#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

char *_getline(void);
char *_ini_buffer(ssize_t *chars_read);
ssize_t _read_input(char *buffer);
char **split_line(char *line);
int exec(char **args);
int exec_command(char *cmd_path, char **args);
int is_exit(char *cmd);
int is_env(char *cmd);
void print_env(void);
int search_paths(char *path, char **args);
char *create_cmd_path(char *path, char *cmd);
void free_args(char **args);

#endif

