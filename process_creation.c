#include "shell.h"
/**
 * process_creation - creates a child process
 * @command: the input
 * @ev: environment variables
 * Return: nothing in success an failure if it's failed
*/
int process_creation(char **argv, char **ev)
{
pid_t my_pid;
int status;
int check;
my_pid = fork();/*child process creation*/
if (my_pid == -1)
{
perror("process creation failed");
return (EXIT_FAILURE);
}
if (my_pid == 0)/*inside the child process*/
{
_execute(argv, ev);
perror("child process failed");
}
else     /*parent process*/
{
check = wait(&status);
if (check == -1)
{
perror("wait failed");
return (EXIT_FAILURE);
}
}
}
