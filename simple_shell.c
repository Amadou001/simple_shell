#include "shell.h"
/**
 * main - Displays a prompt and wait for the user to type a command
 * @ac: argument counter
 * @av: argument vector
 * @ev: environment variables
 * Return: always 0
*/
int main(int ac, char **av, char **ev)
{
ssize_t bytes_read;
char *command = NULL;
size_t length = 0;
pid_t my_pid;
int status;
bool from_pipe = false;
while (1 && !from_pipe)
{
/*condition is for checking wether this input comes from the*/
if (isatty(STDIN_FILENO) == 0)
{
from_pipe = true;
/*from_pipe is assign to true if the input is not comming for the terminal*/
}
write(STDOUT_FILENO, "$ ", 2);
bytes_read = getline(&command, &length, stdin);
if (bytes_read == -1)
{
perror("getline failed!");
free(command);
return (EXIT_FAILURE);
}
command[bytes_read - 1] = '\0';
my_pid = fork();/*child process creation*/
if (my_pid == -1)
{
perror("process creation failed");
free(command);
return (EXIT_FAILURE);
}
if (my_pid == 0)/*inside the child process*/
{
_execute(command, ev);
}
if ((wait(&status)) == -1) /*parent process*/
{
perror("wait failed");
free(command);
exit(EXIT_FAILURE);
}
}
if (from_pipe == false)
{
free(command);
}
return (0);
}

/**
 * _execute - executes the file
 * @buffer: the input
 * @env: the environment variables
 * Return: nothing in success and FAILURE in failure
*/
int _execute(char *buffer, char **env)
{
char **argv;
int check;
int n = 0;
argv = _split(buffer, " "); /*Use of _split function*/
if (argv == NULL)
{
perror("split failed");
exit(EXIT_FAILURE);
}
check = check_executable(argv[0]); /*Use of check_executable*/
if (check == -1)
{
n = argv_counter(argv);
_free(argv, n);
perror("check_executable failed");
exit(EXIT_FAILURE);
}
if (check == 0)
{
perror("Not executable file");
exit(EXIT_FAILURE);
}
execve(argv[0], argv, env);
perror("execve failed"); /*printed only when execve fails*/
exit(EXIT_FAILURE);
}

/**
 * argv_counter - counts the number of strings
 * @argv: array of strings
 * Return: number of strings
*/
int argv_counter(char **argv)
{
int i = 0;
while (argv[i] != NULL)
{
i++;
}
return (i);
}
