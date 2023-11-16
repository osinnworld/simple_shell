#include "shell.h"

builtin_cmd builtins[] = {
	{"cd", &_cd},{"help", &_help},
	{"exit", &_exit_exe},{"^D", &_ctrld},
	{"env", &_env},{"setenv", &_setenv},
	{"unsetenv", &_unsetenv},
};


/**
 * num_builtins - Get no. of built-in cmd
 *
 * Return: No of builtin commands
 */
int num_builtins(void)
{
	return (sizeof(builtins) / sizeof(builtins[0]));
}


/**
 * sigint_handler - Signal handler for SIGINT
 * @signum: signal number
 */
void sigint_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n$ ", 3);
}


/**
 * main - Entry point to simple shell
 * @ac: no of cmd args
 * @av: array of cmd args
 * @env: array of env variables
 *
 * Return: exit status of program
 */
int main(int ac, char **av, char **env)
{
	char **cmd = NULL, *line = NULL;
	int path = 0, status = 0, value = 0;
	int blt;

	(void)ac;

	signal(SIGINT, sigint_handler);

	while (1)
	{
		errno = 0;
		line = _getline();
		if (line == NULL && errno == 0)
			return (0);
		if (line)
		{
			value++;
			cmd = tokenize(line);
			if (!cmd)
				free(line);
			if (_strcmp(cmd[0], "exit") == 0)
			{
				free(cmd);
				free(line);
				return _exit_exe(cmd);
			}

			blt = _execute_builtin(cmd);
			if (blt)
			{
				status = blt;
			}
			else
			{
				if (cmd)
				{
					path = _absolute_path(&cmd[0], env);
					status = _execute(cmd, av, env);
					if (status == 200)
					{
						free(line);
						return (0);
					}
					if (path == 0)
						free(cmd[0]);
				}
			}
			free(cmd);
		}
		else
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			exit(status);
		}
		free(line);
	}
	return (status);
}


/**
 * _execute_builtin - execute a builtin cmd
 * args: args
 *
 * Returb: status
 */
int _execute_builtin(char **args)
{
	int i;

	for (i = 0; i < num_builtins(); i++)
	{
		if (_strcmp(args[0], builtins[i].command) == 0)
		{
			return (builtins[i].func(args));
		}
	}
	return (0);
}
