#include "shell.h"

extern Alias aliases[MAX_ALIASES];
/**
 * _execute - execute a cmd
 * @arg: argss
 * @av: array of string
 * @env: env variable
 * @ptr: ptr to line
 * @fm: free memory
 *
 * Return: status of cmd
 */
int _execute(char **arg, char **av, char **env, char *ptr, int prc, int fm)
{
	pid_t child;
	int status;
	size_t i = 0;
	int nxt = 1;
	(void)prc;

	if (arg == NULL || arg[0] == NULL)
		return (1);

	for (i = 0; i < num_builtins(); i++)
	{
		if (_strcmp(arg[0], builtins[i].command) == 0)
			return (builtins[i].func(arg));
	}

	for (i = 0; i < num_aliases; i++)
	{
		while (r_alias(arg, aliases[i].name, aliases[i].value))
			;
	}

	for (i = 0; arg[i] != NULL; i++)
	{
		if (_strcmp(arg[i], "&&") == 0 || _strcmp(arg[i], "||") == 0)
		{
			char **cmd1, **cmd2;
			int op_and = _strcmp(arg[i], "&&") == 0;
			int prv_cmd = status == 0;

			nxt = op_and ? prv_cmd : !prv_cmd;

			arg[i] = NULL;
			cmd1 = arg;
			cmd2 = &arg[i + 1];

			if (nxt)
			{
				child = fork();
				if (child == 0)
				{
					if (execve(cmd1[0], cmd1, env) == -1)
					{
						err_msg(cmd1[0], av[0]);
						if (!fm)
							free(cmd1[0]);
						free(cmd1);
						free(ptr);
						exit(errno);
					}
				}
				else
				{
					wait(&status);
					if ((op_and && status != 0) || (!op_and && status == 0))
					{
						nxt = 0;
						break;
					}
				}
			}
			arg = cmd2;
			i = -1;
		}
	}
	if (nxt)
	{
		child = fork();
		if (child == 0)
		{
			if (execve(arg[0], arg, env) == -1)
			{
				err_msg(arg[0], av[0]);
				if (!fm)
					free(arg[0]);
				free(arg);
				free(ptr);
				exit(errno);
			}
		}
		else
		{
			wait(&status);
			free(arg[0]);
			free(arg);
			return (status);
		}
	}
	return (0);
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
