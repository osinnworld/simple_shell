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
		perror("setenv: Invalid arguments");
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
 * @args: args
 *
 * Return: 0 or -1
 */
int _unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		perror("unsetenv: Variable name not provided");
		return (-1);
	}

	if (unsetenv(args[1]) != 0)
	{
		perror("unsetenv");
		return (-1);
	}

	return (0);
}
