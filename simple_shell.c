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
char *new_command;
char **argv;
int n = 0, i = 0;
char *ptr;
(void)ac;
(void)av;
while (1 || isatty(STDIN_FILENO))
{
if (isatty(STDIN_FILENO) != 0)
{
write(STDOUT_FILENO, "$ ", 2);
}
bytes_read = getline(&command, &length, stdin);
if (bytes_read == -1)
{
free(command);
return (0);
}
for (i = 0; i < bytes_read; i++)
{
if ((i == 0 || command[i - 1] == ' ') && command[i] == '#')
{
while (command[i] != '\n' && i < bytes_read)
{
command[i] = ' ';
i++;
}
}
}
command[bytes_read - 1] = '\0'; /*remove the new line*/
if ((strspn(command, " ")) == (size_t)(bytes_read - 1))
{
continue;
}
argv = _split(command, " \n");    /*use of _split function*/
n = argv_counter(argv);         /*call of argv_counter function*/
ptr = argv[0]; /*pointer to the command*/
if (strcmp(argv[0], "exit") == 0)
{
free(command);
_free(argv, n);
_exit_function();
}
else if (argv[1] != NULL && argv[0] != NULL)    /*when there is an argument or option*/
{
argument_handling(argv, ptr, ev); /*use of argument_handling function*/
}
else if (argv[1] == NULL && *ptr == '/' && access(argv[0], F_OK) == 0) /*to check wether the command is an absolute path*/
{
process_creation(argv, ev); /*use of process_creation function*/
}
else if (argv[1] == NULL && *ptr == '.' && access(argv[0], F_OK) == 0) /*to check wether the command is an absolute path*/
{
process_creation(argv, ev); /*use of process_creation function*/
}
else if (*ptr != '/' && ((new_command = path_handling(argv[0])) != NULL)) /*if it's not an absolute paht*/
{
free(argv[0]);
argv[0] = strdup(new_command);
free(new_command);
process_creation(argv, ev); /*use of process_creation function*/
}
else
{
_execute(argv, ev); /*if the command does not exit*/
}
}
return (0);
}

/**
 * _execute - executes the file
 * @argv: the input
 * @env: the environment variables
 * Return: nothing in success and FAILURE in failure
*/
int _execute(char **argv, char **env)
{
int check;
int n  = argv_counter(argv);
check = check_executable(argv[0]); /*Use of check_executable*/
if (check == -1)
{
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
_free(argv, n);
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
