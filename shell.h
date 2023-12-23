#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <wait.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
int _execute(char *buffer, char **env);
char **_split(char *buffer, const char *delim);
int check_executable(char *command);
void _free(char **str, int count);
int argv_counter(char ** argv);





#endif