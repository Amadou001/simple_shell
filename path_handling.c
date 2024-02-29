#include "shell.h"
/**
 * path_handling - handles the path
 * @command: given input
 * Return: a pointer to the absolue path found
*/
char *path_handling(char *command)
{
const char *PATH = "PATH";
char *path_value, *token;
char *full_path;
size_t len_full_path = 0;
path_value = _getenv(PATH);    /*Use of _getenv function*/
if (path_value == NULL)
{
perror("getenv, failed");
return (NULL);
}
token = strtok(path_value, ":");
while (token != NULL)
{
len_full_path = strlen(token) + strlen(command) + 2;
full_path = (char *)malloc(len_full_path);
if (full_path == NULL)
{
free(path_value);
perror("allocution failed from path_handling");
return (NULL);
}
snprintf(full_path, len_full_path, "%s/%s", token, command);
if ((access(full_path, F_OK)) == 0)
{
free(path_value);
return (full_path);
}
free(full_path);
token = strtok(NULL, ":");
}
perror("Not found");
free(path_value);
return (NULL);
}
/**
 * _getenv - gets the value of the environment variable
 * @name: environment variable name
 * Return: the corresponding value
*/
char *_getenv(const char *name)
{
char **ev = environ_duplicate();
char **ev_cp = ev;
char *token;
char *value = NULL;
while (*ev_cp != NULL)
{
token = strtok(*ev_cp, "=");
if (token != NULL && strcmp(token, name) == 0)
{
value = strdup(strtok(NULL, "="));
_free_environ_cp(ev);
return (value);
}
ev_cp++;
}
_free_environ_cp(ev);
return (NULL);
}
/**
 * environ_duplicate - duplicates the environment
 * Return: the duplicated environment
*/
char **environ_duplicate(void)
{
int env_count = 0;
char **environ_cp;
int i;
char **ptr_environ = environ;
while (*ptr_environ != NULL)
{
env_count++;
ptr_environ++;
}
environ_cp = (char **)malloc(sizeof(char *) * (env_count + 1));
if (environ_cp == NULL)
{
perror("memory allocution for environ copy failed");
return (NULL);
}
for (i = 0; i < env_count; i++)
{
environ_cp[i] = strdup(environ[i]);
}
environ_cp[env_count] = NULL;
return (environ_cp);
}
/**
 * _free_environ_cp - frees the duplicated environment
 * @env: duplicated environment
*/
void _free_environ_cp(char **env)
{
int i;
for (i = 0; env[i] != NULL; i++)
{
free(env[i]);
}
free(env);
}
