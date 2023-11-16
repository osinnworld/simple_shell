#include "shell.h"

/**
 * _getline - reads a line from std input
 *
 * Return: ptr
 */
char *_getline(void)
{
	char *line = NULL;
	size_t size = 0;
	ssize_t r, i;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);

	r = getline(&line, &size, stdin);

	if (r == -1)
	{
		free(line);
		return (NULL);
	}
	if (line[r - 1] == '\n')
		line[r - 1] = '\0';
	
	for (i = 0; i < r - 1; i++)
	{
		if (line[i] != ' ')
			break;
	}
	if (i == r - 1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

/**
 * tokenize - tokenize a string based on delimiters
 * @ptr: The input string to tokenize
 *
 * Return: An array of tokens (strings)
 */
char **tokenize(char *ptr)
{
	char **cmd = NULL;
	char *token = NULL;
	size_t i = 0;
	int size = 0;

	if (ptr == NULL)
	{
		return (NULL);
	}

	for (i = 0; ptr[i]; i++)
	{
		if (ptr[i] == '\0')
		{
			size++;
		}
	}
	if ((size + 1) == _strlen(ptr))
		return (NULL);
	cmd = malloc(sizeof(char *) * (size + 2));
	if (cmd == NULL)
		return (NULL);
	token = strtok(ptr, " \n\t\r");

	for (i = 0; token != NULL; i++)
	{
		cmd[i] = token;
		token = strtok(NULL, " \n\t\r");
	}
	cmd[i] = NULL;
	return (cmd);
}

