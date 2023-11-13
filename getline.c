#include "shell.h"
/**
 * _getline - a function that reads a line from a standard input
 *
 * Return: A pointer to the read line, or NULL on failure at the end of file
 */

char *_getline(void)
{
	char *line = NULL;
	size_t size = 0;
	ssize_t characters;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);

	characters = getline(&line, &size, stdin);

	if (characters == -1)
	{
		if (line)
			free(line);
		return (NULL);
	}

	if (characters > 0)
	{
		if (line[characters - 1] == '\n')
			line[characters - 1] = '\0';
	}
	return (line);
}

/**
 * tokenize - tokenize a string based on delimiters
 * @lineptr: The input string to tokenize
 * @delimeters: The delimiters to use for tokenization
 *
 * Return: An array of tokens (strings), or NULL on failure or empty imput
 */
char **tokenize(char *lineptr, const char *delimiters)
{
	char **cmd = NULL;
	char *token = NULL;
	size_t i = 0;
	int count = 0;
	int in_token = 0;

	if (lineptr == NULL || lineptr[0] == '\0')
	{
		return (NULL);
	}

	for (i = 0; lineptr[i] != '\0'; i++)
	{
		if (strchr(delimiters, lineptr[i]) != NULL)
		{
			if (in_token)
			{
				lineptr[i] = '\0';
				cmd = realloc(cmd, sizeof(char *) * (count + 1));
				if (cmd == NULL)
				{
					return (NULL);
				}
				cmd[count] = strdup(token);
				count++;
				in_token = 0;
			}
		}

		else if (lineptr[i] == '&' && lineptr[i + 1] == '&')
		{
			if (in_token)
			{
				lineptr[i] = '\0';
				cmd = realloc(cmd, sizeof(char *) * (count + 1));
				if (cmd == NULL)
				{
					return (NULL);
				}
				cmd[count] = strdup(token);
				count++;
				in_token = 0;
			}
			cmd = realloc(cmd, sizeof(char *) * (count + 1));
			if (cmd ==  NULL)
			{
				return (NULL);
			}
			cmd[count] = strdup("&&");
			count++;
			i++;
		}

		else
		{
			if (!in_token)
			{
				token = &lineptr[i];
				in_token = 1;
			}
		}
	}

	if (in_token)
	{
		cmd = realloc(cmd, sizeof(char *) * (count + 1));
		if (cmd == NULL)
		{
			return (NULL);
		}
		cmd[count] = strdup(token);
		count++;
	}
	cmd = realloc(cmd, sizeof(char *) * (count + 1));
	if (cmd == NULL)
	{
		return (NULL);
	}
	cmd[count] = NULL;
	return (cmd);
}
