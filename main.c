#include "shell.h"

builtin_cmd builtins[] = {
	{"cd", &_cd},{"help", &_help},
	{"exit", &_exit_exe},{"^D", &_ctrld},
	{"env", &_env},{"setenv", &_setenv},
	{"unsetenv", &_unsetenv},{"_alias", &_alias_cmd},
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
	int vstatus = 0;
	char *ln = NULL;

	(void)ac;
	signal(SIGINT, sigint_handler);

	while (1)
	{
		errno = 0;
		ln = _getline();
		if (ln == NULL && errno == 0)
			return (0);

		if (ln)
		{
			char **token = tokenize(ln, ";");

			exe_tk(token, av, env, ln, status);
			free(token);
		}
		else
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "$ ", 3);
			exit(status);
		}
		free(ln);
	}
	return (status);
}
