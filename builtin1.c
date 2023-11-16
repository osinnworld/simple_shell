#include "shell.h"

/**
 * _cd -  a function that changes the current workinhg directory
 * @args: args
 *
 * Return: 0 or 1
 */
int _cd(char **args)
{
	char *new_dir;
	char *old_pwd = NULL;

	if ((old_pwd = (char *)malloc(1024 * sizeof(char))) == NULL)
	{
		perror("malloc");
		return (1);
	}
	if (args[1] == NULL)
	{
		new_dir = getenv("HOME");
	}
	else if (_strcmp(args[1], "-") == 0)
	{
		new_dir = getenv("OLDPWD");
		if (new_dir == NULL)
		{
			write(STDERR_FILENO, "OLDPWD not set\n", 15);
			free(old_pwd);
			return (1);
		}
	}
	else
	{
		new_dir = args[1];
	}

	if (chdir(new_dir) != 0)
	{
		perror("hsh");
		free(old_pwd);
		return (1);
	}

	if (getcwd(old_pwd, 1024) == NULL)
	{
		perror("hsh");
		free(old_pwd);
		return (1);
	}

	setenv("OLDPWD", old_pwd, 1);
	setenv("PWD", new_dir, 1);

	free(old_pwd);

	return (0);
}

/**
 * _help -  A function that shows information about the simple shell
 * @args: args
 *
 * Return: 1
 */
int _help(char **args)
{
	char *msg1 = "Welcome to the custom shell program!\n";
	char *msg2 = "Here the available built-in commands:\n";
	char *msg3 = "cd: Change directory:\n";
	char *msg4 = "help: Display information about the custom shell.\n";
	char *msg5 = "exit: Exit the shell\n";
	char *msg6 = "setenv: Set an environment variable\n";
	char *msg7 = "unsetenv: Unset an environment variable\n";
	char *msg8 = "For more information, please refer to the documentation. \n";

	write(STDOUT_FILENO, msg1, _strlen(msg1));
	write(STDOUT_FILENO, msg2, _strlen(msg2));
	write(STDOUT_FILENO, msg3, _strlen(msg3));
	write(STDOUT_FILENO, msg4, _strlen(msg4));
	write(STDOUT_FILENO, msg5, _strlen(msg5));
	write(STDOUT_FILENO, msg6, _strlen(msg6));
	write(STDOUT_FILENO, msg7, _strlen(msg7));
	write(STDOUT_FILENO, msg8, _strlen(msg8));

	(void)args;
	return (1);
}

/**
 * _exit_exe - A function that exits the shell
 * @args: args
 *
 * Return: exit status
 */
int _exit_exe(char **args)
{
	int status;
	status = args[1] ? atoi(args[1]) : 0;
	return (status);
}

/**
 * _ctrld - Handle Ctrl-D input
 * @args: args
 *
 * Return: 1
 */
int _ctrld(char **args)
{
	(void)args;
	free(args);
	return (200);
}

/**
 * _env -  a function that displays the environment variables
 * @env: an array of environment variables
 *
 * Return: 0
 */

int _env(char **env)
{
	size_t run = 0;

	while (env[run])
	{
		write(STDOUT_FILENO, env[run], _strlen(env[run]));
		write(STDOUT_FILENO, "\n", 1);
		run++;
	}
	return (0);
}
