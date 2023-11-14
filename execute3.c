#include "shell.h"

/**
 * _getenv - Display the env variable
 * @env: Array of env variable
 */
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

/**
 * _get_path - Get the value of the PATH
 * @env: Array of env
 *
 * Return: The value of PATH
 */
char *_get_path(char **env)
{
	size_t index = 0, var = 0, count = 5;
	char *path = NULL;

	for (index = 0; env[index] != NULL && strncmp(env[index],
				"PATH=", 5) != 0; index++)
		;

	if (env[index] == NULL)
		return (NULL);

	for (count = 5; env[index][count]; count++)
		;

	path = malloc(sizeof(char) * (count + 1));

	if (path == NULL)
		return (NULL);
	for (var = 5, count = 0; env[index][var]; var++, count++)
		path[count] = env[index][var];
	path[count] = '\0';
	return (path);
}


/**
 * r_alias - Replace an _alias in the command.
 * @command: args to check
 * @_alias: _alias to be replaced
 * @value: value to replace
 *
 * Return: 1 or 0.
 */
int r_alias(char **command, const char *_alias, const char *value)
{
	int replaced = 0, i;

	for (i = 0; command[i] != NULL; i++)
	{
		if (_strcmp(command[i], _alias) == 0)
		{
			free(command[i]);
			command[i] = strdup(value);
			replaced = 1;
		}
	}
	return (replaced);
}
