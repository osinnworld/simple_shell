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
 * create_token - create a token from given token string
 * @token_str: pointer to token
 *
 * Return: pointer to created token
 */
char *create_token(char *token_str)
{
	return (strdup(token_str));
}


/**
 * add_token - add a token to array of token
 * @cmd: pointer to array of token
 * @token: pointer to token to add
 * @count: pointer to count of token
 */
void add_token(char ***cmd, char *token, int *count)
{
	*cmd = realloc(*cmd, sizeof(char *) * (*count + 1));
	if (*cmd == NULL)
		return;
	(*cmd)[*count] = create_token(token);
	(*count)++;
}

/**
 * process_token - process the current and add it to the array
 * @cmd: pointer to array of token
 * @token: pointer to current token
 * @count: pointer to count of token
 */
void process_token(char ***cmd, char *token, int *count)
{
	if (token != NULL)
	{
		add_token(cmd, token, count);
	}
}


/**
 * tokenize - tokenize a string based on delimiters
 * @lineptr: The input string to tokenize
 * @delimiters: The delimiters to use for tokenization
 *
 * Return: An array of tokens (strings), or NULL on failure or empty imput
 */
char **tokenize(char *lineptr, const char *delimiters)
{
	char **cmd = NULL;
	char *token = NULL;
	size_t i = 0;
	int count = 0;

	if (lineptr == NULL || lineptr[0] == '\0')
	{
		return (NULL);
	}

	for (i = 0; lineptr[i] != '\0'; i++)
	{
		if (strchr(delimiters, lineptr[i]) != NULL)
		{
			if (token != NULL)
			{
				lineptr[i] = '\0';
				process_token(&cmd, token, &count);
				free(token);
				token = NULL;
			}
		}
		else if (lineptr[i] == '&' && lineptr[i + 1] == '&')
		{
			process_token(&cmd, token, &count);
			add_token(&cmd, "&&", &count);
			token = NULL;
			i++;
		}
		else
		{
			if (token == NULL)
			{
				token = &lineptr[i];
			}
		}
	}
	process_token(&cmd, token, &count);
	add_token(&cmd, NULL, &count);

	return (cmd);
}
