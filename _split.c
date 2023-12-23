#include "shell.h"
/**
 * _split - splits the input
 * @buffer: the input
 * @delim: the delimitor
 * Return: an array of strings or NULL at failure
*/
char **_split(char *buffer, const char *delim)
{
char **words = NULL;
char *token;
int word_count = 0;
int i;
token = strtok(buffer, delim);
while (token != NULL)
{
words = realloc(words, (word_count + 1) * sizeof(char *));
if (words == NULL)
{
perror("realloc failed inside split");
_free(words, word_count);
return (NULL);
}
words[word_count] = strdup(token);
if (words[word_count] == NULL)
{
perror("strdup inside split failed");
_free(words, word_count);
return (NULL);
}
token = strtok(NULL, delim);
word_count++;
}
words = realloc(words, (word_count + 1) * sizeof(char *));
if (words == NULL)
{
perror("realloc failed inside split");
_free(words, word_count);
return (NULL);
}
words[word_count] = NULL;
return (words);
}
/***********************************************************/
/**
 * _free - frees the memory inside split
 * @str: array of strings
 * @count: number of strings
*/
void _free(char **str, int count)
{
int i;
for (i = 0; i < count; i++)
{
free(str[i]);
}
free(str);
}
