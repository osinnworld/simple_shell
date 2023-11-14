#include "shell.h"

static int _builtin(char **arg);
static int _log(char ***arg, char **av, char **env, int *s, int *n, int *i, int fm);
static void _child(char **cmd, char **env, char **av, char *ptr, int fm);


/**
 * _execute - execute a cmd
 * @arg: argss
 * @av: array of string
 * @env: env variable
 * @ptr: ptr to line
 * @prc: process variable
 * @fm: free memory
 *
 * Return: status of cmd
 */
int _execute(char **arg, char **av, char **env, char *ptr, int *prc, int fm)
{
	int i;
	int nxt = 1;

	if (arg == NULL || arg[0] == NULL)
		return (1);

	if (_builtin(arg))
		return (0);

	for (i = 0; arg[i] != NULL; i++)
	{
		if (_log(&arg, av, env, prc, &nxt, &i, fm))
		{
			break;
		}
	}

	if (nxt)
	{
		_child(arg, env, av, ptr, fm);
	}
	return (0);
}

/**
 * _builtin - execute builtin command
 * @arg: array of args
 *
 * Return: 0 or 1
 */
static int _builtin(char **arg)
{
	size_t i;

	for (i = 0; i < num_builtins(); i++)
	{
		if (_strcmp(arg[0], builtins[i].command) == 0)
			return (builtins[i].func(arg));
	}
	return (1);
}

/**
 * _log - Handle logical operators
 * @arg: pointer to array of args
 * @av: array of string
 * @env: env variable
 * @s: pointer to status variable
 * @n: pointer to next cmd
 * @i: pointer to loop var
 *
 * Return: 1 or 0
 */
static int _log(char ***arg, char **av, char **env, int *s, int *n, int *i, int fm)
{
	int op_and, prv_cmd;
	char **cmd1, **cmd2;

	if (_strcmp((*arg)[*i], "&&") == 0 || _strcmp((*arg)[*i], "||") == 0)
	{
		op_and = _strcmp((*arg)[*i], "&&") == 0;
		prv_cmd = *s == 0;

		*n = op_and ? prv_cmd : !prv_cmd;

		(*arg)[*i] = NULL;
		cmd1 = *arg;
		cmd2 = &(*arg)[*i + 1];

		if (*n)
		{
			pid_t child = fork();

			if (child == 0)
			{
				if (execve(cmd1[0], cmd1, env) == -1)
				{
					err_msg(cmd1[0], av[0]);
					if (!fm)
						free(cmd1[0]);
					free(cmd1);
					exit(errno);
				}
			}
			else
			{
				wait(s);
				if ((op_and && *s != 0) || (!op_and && *s == 0))
				{
					*n = 0;
					return (1);
				}
			}
		}
		*arg = cmd2;
		*i = -1;
		return (1);
	}
	return (0);
}

/**
 * _child - execute a child process
 * @cmd: array of args
 * @env: env variable
 * @av: array of string
 * @ptr: pointer to line
 * @fm: free memory
 */
static void _child(char **cmd, char **env, char **av, char *ptr, int fm)
{
	pid_t child = fork();
	int status;

	if (child == 0)
	{
		if (execve(cmd[0], cmd, env) == -1)
		{
			err_msg(cmd[0], av[0]);
			if (!fm)
				free(cmd[0]);
			free(cmd);
			free(ptr);
			exit(errno);
		}
	}
	else
	{
		wait(&status);
	}
}

/**
 * err_msg - display error msg
 * @command: cmd causing error
 * @pg: program name
 */
void err_msg(char *command, char *pg)
{
	char *err_msg = pg;
	char *err_msg2 = ": 1: ";
	char *err_msg3 = ": not found\n";

	write(STDERR_FILENO, err_msg, _strlen(err_msg));
	write(STDERR_FILENO, err_msg2, _strlen(err_msg2));
	write(STDERR_FILENO, command, _strlen(command));
	write(STDERR_FILENO, err_msg3, _strlen(err_msg3));
	exit(EXIT_FAILURE);
}
