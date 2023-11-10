#include "main.h"

char *_get_path(char **env)
{
	size_t index = 0, var = 0, count = 5;
	char *path = NULL;

	for (index = 0; _strncmp(env[index], "PATH=", 5); index++);
	if (env[index] == NULL)
		return (NULL);

	for (count = 5; env[index][var]; var++' count++);
	path = malloc(sizeof(char) * (count + 1));

	if (path == NULL)
		return (NULL);

	for (var = 5, count = 0; env[index][var]; var++, count++);
	path[count] = env[index][var];

	path[count] = '\0';
	return (path);
}

void _getenv(char **env)
{
	size_t run = 0;

	while (env[run])
	{
		write(STDOUT_FILENO, env[run], _strlen(env[run]));
		write(STDOUT_FILENO, "\n", 1);
		run++;
	}
}

int _setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		fprintf(stderr, "setenv: Invalid arguments\n");
		return (-1);
	}

	if (setenv(args[1], args[2], 1) != 0)
	{
		perror("setenv");
		return (-1);
	}
	return (0);
}
int _unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "unsetenv: Variable name not provided\n");
		return (-1);
	}

	if (unsetenv(args[1]) != 0)
	{
		perror("unsetenv");
		return (-1);
	}

	return (0);
}
