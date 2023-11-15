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
	char *token = NULL;
	size_t len, path;
	struct stat st;

	(void)env;

	if (stat(*arg, &st) == 0)
		return (-1);

	r_path = _get_path(env);

	if (!r_path || r_path[0] == '\0')
	{
		free(r_path);
		return (-1);
	}

	token = strtok(r_path, ":");
	len = _strlen(*arg);
	while (token)
	{
		path = _strlen(token);
		abs_path = malloc(sizeof(char) * (path + len + 2));
		if (!abs_path)
		{
			free(r_path);
			return (-1);
		}
		abs_path = _strcpy(abs_path, token);
		_strcat(abs_path, "/");
		_strcat(abs_path, *arg);

		if (stat(abs_path, &st) == 0)
		{
			*arg = abs_path;
			free(r_path);
			return (0);
		}
		free(abs_path);
		token = strtok(NULL, ":");
	}
	token = '\0';
	free(r_path);
	return (-1);
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

	for (index = 0; _strncmp(env[index], "PATH=", 5) != 0; index++)
		;
	if (env[index] == NULL)
		return (NULL);
	for (count = 5; env[index][count]; var++, count++)
		;
	path = malloc(sizeof(char) * (count + 1));

	if (path == NULL)
		return (NULL);

	for (var = 5, count = 0; env[index][var]; var++, count++)
		path[count] = env[index][var];

	path[count] = '\0';
	return (path);
}

