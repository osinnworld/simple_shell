#include "shell.h"

char *create_token(char *token_str);
void add_token(char ***cmd, char *token, int *count);
void process_token(char ***cmd, char *token, int *count);

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
 * @delimiters: The delimiters to use for tokenization
 *
 * Return: An array of tokens (strings)
 */
char **tokenize(char *ptr, const char *delimiters)
{
	char **cmd = NULL;
	char *token = NULL;
	size_t i = 0;
	int count = 0;
	int tk = 0;

	if (ptr == NULL || ptr[0] == '\0')
	{
		return (NULL);
	}

	for (i = 0; ptr[i] != '\0'; i++)
	{
		if (strchr(delimiters, ptr[i]) != NULL)
		{
			if (tk)
			{
				ptr[i] = '\0';
				cmd = realloc(cmd, sizeof(char *) * (count + 1));
				if (cmd == NULL)
					return (NULL);
				cmd[count] = strdup(token);
				count++;
				tk = 0;
			}
		}
		else if (ptr[i] == '&' && ptr[i + 1] == '&')
		{
			if (tk)
			{
				ptr[i] = '\0';
				cmd = realloc(cmd, sizeof(char *) * (count + 1));
				if (cmd == NULL)
					return (NULL);
				cmd[count] = strdup(token);
				count++;
				tk = 0;
			}
			cmd = realloc(cmd, sizeof(char *) * (count + 1));
			if (cmd == NULL)
				return (NULL);
			cmd[count] = strdup("&&");
			count++;
			i++;
		}
		else
		{
			if (!tk)
			{
				token = &ptr[i];
				tk = 1;
			}
		}
	}
	if (tk)
	{
		cmd = realloc(cmd, sizeof(char *) * (count + 1));
		if (cmd == NULL)
			return (NULL);
		cmd[count] = strdup(token);
		count++;
	}
	cmd = realloc(cmd, sizeof(char *) * (count + 1));
	if (cmd == NULL)
		return (NULL);
	cmd[count] = NULL;
	return (cmd);
}
