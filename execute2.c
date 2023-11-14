#include "shell.h"

int process_path(char **arg, char **paths);
char *build_path(char *arg, char *path, size_t len);

/**
 * _absolute_path - get absolute path of cmd
 * @arg: absolute path
 * @env: env variable
 *
 * Return: 0 or -1
 */
int _absolute_path(char **arg, char **env)
{
	char *r_path = NULL;
	char **path = NULL;
	int result;

	struct stat st;
	if (stat(*arg, &st) == 0)
		return (-1);

	r_path = _get_path(env);

	if (!r_path || r_path[0] == '\0')
	{
		free(r_path);
		return (-1);
	}

	path = parse_path(r_path);
	result = process_path(arg, path);

	free(r_path);
	free(path);

	return (result);
}

/**
 * process_path - process each path
 * @arg: absolute path
 * @paths: array of path
 *
 * Return: 0 or -1
 */
int process_path(char **arg, char **paths)
{
	size_t len, i;
	char *abs_path;

	for (i = 0; paths[i] != NULL; i++)
	{
		struct stat st;
		len = _strlen(*arg) + _strlen(paths[i]) + 2;
		abs_path = build_path(*arg, paths[i], len);

		if (!abs_path)
		{
			return (-1);
		}

		if (stat(abs_path, &st) == 0)
		{
			free(*arg);
			*arg = strdup(abs_path);
			free(abs_path);
			return (0);
		}
		free(abs_path);
	}
	return (-1);
}

/**
 * build_path - build absolute path
 * @arg: absolute path
 * @path: current path
 * @len: length
 *
 * Return: absolute path
 */
char *build_path(char *arg, char *path, size_t len)
{
	char *abs_path = malloc(sizeof(char) * len);

	if (!abs_path)
		return (NULL);

	_strcpy(abs_path, path);
	_strcat(abs_path, "/");
	_strcat(abs_path, arg);

	return (abs_path);
}

/**
 * parse_path - Parse the PATH environment
 * @path: env variable
 *
 * Return: Array of string
 */
char **parse_path(char *path)
{
	return (tokenize(path, ":"));
}

