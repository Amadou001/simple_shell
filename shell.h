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
extern char **environ;
int _execute(char **argv, char **env);
char **_split(char *buffer, const char *delim);
int check_executable(char *command);
void _free(char **str, int count);
int argv_counter(char **argv);
char *_getenv(const char *name);
char *path_handling(char *command);
int process_creation(char **argv, char **ev);
void argument_handling(char **argv, char *ptr, char **ev);
char **environ_duplicate(void);
void _free_environ_cp(char **env);
int ar_process_creation(char **argv_counter, char **ev);
void _exit_function(void);



#endif
