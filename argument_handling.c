#include "shell.h"
/**
 * argument_handling - handles argument
 * @argv: the input
 * @ptr: pointer to the command
 * @ev: environment variables
*/
void argument_handling(char **argv, char *ptr, char **ev)
{
char *pointer;
int n;
n = argv_counter(argv);
if (*ptr == '/' && (access(ptr, F_OK)) == 0) /**checks wether it's
*an absolute path and if it exists
*/
{
process_creation(argv, ev); /*call of process_creation function*/
}
else if (*ptr == '.' && (access(ptr, F_OK)) == 0)
{
process_creation(argv, ev);
}
else if (*ptr != '/')
/*if it is not an absolute path , call of paht_handling function*/
{
pointer = path_handling(ptr);
if (pointer != NULL)
{
free(argv[0]);
argv[0] = strdup(pointer);  /**change of the initial command by
*it's absolute path
*/
free(pointer);
ar_process_creation(argv, ev); /*call of ar_process_creation*/
}
}
else
{
_execute(argv, ev); /*call of _execute function*/
_free(argv, n);
}
}
/********************************************************/
/**
 * ar_process_creation - creates a process a special process
 * for the argument handling
 * @argv: the input
 * @ev: environment variables
 * Return: nothing in success, failure if it's failed
*/
int ar_process_creation(char **argv, char **ev)
{
pid_t my_pid;
int status;
int check, n = 0;
n = argv_counter(argv); /*call of argv_counter function*/
my_pid = fork();  /*child process creation*/
if (my_pid == -1)
{
perror("process creation failed");
_free(argv, n); /*call of _free function*/
return (EXIT_FAILURE);
}
if (my_pid == 0)/*inside the child process*/
{
if (execve(argv[0], argv, ev) == -1) /*execution of the command*/
{
perror("executable failed");
}
}
else     /*parent process*/
{
check = wait(&status);
_free(argv, n);
if (check == -1)
{
perror("wait failed");
return (EXIT_FAILURE);
}
}
return (0);
}
