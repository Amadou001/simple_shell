#include "shell.h"
/**
 * check_executable - checks the stat of the file
 * @command: file name
 * Return: (1) if executable file, (-1) in failure, (0) not executable
*/
int check_executable(char *command)
{
struct stat file_stat;
if ((stat(command, &file_stat)) == -1)
{
return (-1);/*stat failed*/
}
if (file_stat.st_mode & S_IXUSR || file_stat.st_mode & S_IXGRP
|| file_stat.st_mode & S_IXOTH)
{
return (1); /*executable*/
}
else
{
return (0);
}
}
