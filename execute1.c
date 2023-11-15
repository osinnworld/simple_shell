#include "shell.h"

/**
 * _execute - execute a cmd
 * @arg: argss
 * @av: array of string
 * @env: env variable
 * @ptr: ptr to line
 * @np: arg
 * @c: arg
 *
 * Return: exit
 */
int _execute(char **arg, char **av, char **env, char *ptr, int np, int c)
{
	pid_t child;
	int status, i = 0;

	if (arg[0] == NULL)
		return (1);

	for (i = 0; i < num_builtins(); i++)
	{
		if (_strcmp(arg[0], builtin_str[i]) == 0)
			return (builtin_func[i](arg));
	}

	child = fork();
	if (child == 0)
	{
		if (execve(arg[0], arg, env) == -1)
		{
			if (errno == ENOENT)
			{
				err_msg(arg[0], av[0], 127);
			}
			else
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		wait(&status);

		if (WIFEXITED(status))
		{
			return WEXITSTATUS(status);
		}
		else
		{
<<<<<<< HEAD
			wait(&status);
			free(arg[0]);
			free(arg);
=======
>>>>>>> b03e48f0a313c7644af036e91745f37eff6fb6e8
			return (status);
		}
	}

	return (0);
}
/**
 * err_msg - display error msg
 * @command: cmd causing error
 * @pg: program name
 * @status: arg
 */
void err_msg(char *command, char *pg int status)
{
	char *err_msg = pg;
	char *err_msg2 = ": 1: ";
	char *err_msg3 = ": not found\n";

	write(STDERR_FILENO, err_msg, _strlen(err_msg));
	write(STDERR_FILENO, err_msg2, _strlen(err_msg2));
	write(STDERR_FILENO, command, _strlen(command));
	write(STDERR_FILENO, err_msg3, _strlen(err_msg3));
	exit(status);
}
