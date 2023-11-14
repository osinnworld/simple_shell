#include "shell.h"
/**
 * _absolute_path - absolute path cmd
 * @arg: absolute path
 * @env: env variable
 *
 * Return: 0 or 1
 */
int _absolute_path(char **arg, char **env)
{
	char *r_path = NULL, *abs_path = NULL;
	size_t len;
	struct stat st;
	char **path;
	size_t i;

	(void)env;

	if (stat(*arg, &st) == 0)
		return (-1);

	r_path = _get_path(env);

	if (!r_path || r_path[0] == '\0')
	{
		free(r_path);
		return (-1);
	}

	path = parse_path(r_path);

	for (i = 0; path[i] != NULL; i++)
	{
		len = _strlen(*arg) + _strlen(path[i]) + 2;
		abs_path = malloc(sizeof(char) * len);

		if (!abs_path)
		{
			free(r_path);
			free(path);
			return (-1);
		}

		_strcpy(abs_path, path[i]);
		_strcat(abs_path, "/");
		_strcat(abs_path, *arg);

		if (stat(abs_path, &st) == 0)
		{
			free(*arg);
			*arg = strdup(abs_path);
			free(r_path);
			free(path);
			free(abs_path);
			return (0);
		}
		free(abs_path);
	}
	free(r_path);
	free(path);
	return (-1);
}

/**
 * parse_path - Parse the PATH
 * @path: env variable
 *
 * Return: array of string
 */
char **parse_path(char *path)
{
	return (tokenize(path, ":"));
}

/**
 * _getenv - Display env variable
 * @env: env variable
 *
 * Return: Array of string containing paths
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
 * _get_path - Get value of PATH
 * @env: array of env variable
 *
 * Return: PATH
 */
char *_get_path(char **env)
{
	size_t index = 0, var = 0;
	size_t count = 5;
	char *path = NULL;

	for (index = 0; env[index] != NULL && strncmp(env[index], "PATH=", 5) != 0; index++)
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
 * r_alias - Replace an alias in the cmd
 * @cmd: arg to check and replace aliases
 * @alias: alias to be replaced
 * @value: value to replace
 *
 * Return: 1 or 0
 */
int r_alias(char **cmd, const char *alias, const char *value)
{
	int i, r = 0;

	for (i = 0; cmd[i] != NULL; i++)
	{
		if (_strcmp(cmd[i], alias) == 0)
		{
			free(cmd[i]);
			cmd[i] = strdup(value);
			r = 1;
		}
	}
	return (r);
}


