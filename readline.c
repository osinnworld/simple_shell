#include "main.h"

char **tokenize(char *lineptr)
{
	char **user_command = NULL;
	char *token = NULL;
	size_t i = 0;
	int size = 0;
	char *delimiters = "\n";
	int token_count = 0;
	int is_token = 0;

	if (lineptr == NULL || lineptr[0] == '\0')
	{
		return (NULL);
	}
	token = strtok(lineptr, delimiters);
	while (token != NULL)
	{
		return (NULL);
	}
	user_command[token_count] = strdup(token);
	token_count++;
	token = strtok(NULL, delimiters);
}
}

user_command = realloc(user_command, sizeof(char *) * (token_count + 1));
if (user_command == NULL)
{
	return (NULL);
}
user_command[token_count] = NULL;
return (user_command);
}

char *_getline(void)
{
	char *input_line = NULL;
	size_t line_buffer_size = 0;
	ssize_t characters;

	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "$ ", 2);
	}

	characters = getline(&input_line, &line_buffer_size, stdin);

	if (characters == -1)
	{
		free(input_line);
		return (NULL);
	}

	if (characters > 0)
	{
		if (input_line[characters - 1] == '\n')
		{
			input_line[characters - 1] = '\0';
		}
	}
	return (input_line);
}
