#include "shell.h"

/**
 * _setenv - A function that sets an env variable
 * @args: An array of args
 *
 * Return: 0 or -1
 */
int _setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		write(STDERR_FILENO, "setenv: invalid arguments\n", 26);
		return (-1);
	}

	if (setenv(args[1], args[2], 1) != 0)
	{
		perror("setenv");
		free(args[2]);
		return (-1);
	}
	free(args[2]);
	return (0);
}

/**
 * _unsetenv - a function taht unsets env variable
 * @args: array of args
 *
 * Return: 0 or -1
 */
int _unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		write(STDERR_FILENO, "unsetenv: variable name not provided\n", 37);
		return (-1);
	}

	return (0);
}
