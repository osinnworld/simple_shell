#include "shell.h"

builtin_cmd builtins[] = {
	{"cd", &_cd},{"help", &_help},
	{"exit", &_exit_exe},{"^D", &_ctrld},
	{"env", &_env},{"setenv", &_setenv},
	{"unsetenv", &_unsetenv},{"_alias", &alias_cmd},
};


/**
 * num_builtins - Get no. of built-in cmd
 *
 * Return: No of builtin commands
 */
size_t num_builtins(void)
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
	int value = 0, status = 0, path = 0;
	char *line = NULL;
	char *token;

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

			token = strtok(line, ";");

			while (token != NULL)
			{
				char **cmd = tokenize(token, " \t\n\r");
				if (cmd != NULL && cmd[0] != NULL)
				{
					if (!_strcmp(cmd[0], "env"))
					{
						_getenv(env);
					}
					else if (!_strcmp(cmd[0], "alias"))
					{
						alias_cmd(cmd);
					}
					else
					{
						path = _absolute_path(&cmd[0], env);
						status = _execute(cmd, av, env, line, value, path);
						if (status == 200)
						{
							free(line);
							return (0);
						}
						if (path == 0)
							free(cmd[0]);
					}
					free(cmd);
				}
				token = strtok(NULL, ";");
			}
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
