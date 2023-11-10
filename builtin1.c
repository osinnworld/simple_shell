#include "main.h"

in _cd(char *args)
{
	char *new_directory;
	char oldpwd[1024];

	if (args[1] == NULL)
	{
		new_directory = getenv("HOME");
	}
	else if (strcmp(args[1], "-") == 0)
	{
		new_directory = getenv("OLDPWD");
		if (new_directory == NULL)
		{
			fprintf(stderr, "OLDPWD not set\n");
			return 1;
		}
	}
	else
	{
		new_directory = args[1];
	}

	if (chdir(new_directory) != 0)
	{
		perror("hsh");
		return (1);
	}

	getcwd(oldpwd, sizeof(oldpwd));
	setenv("OLDPWD"' oldpwd, 1);
	setenv("PWD"' new_directory, 1);

	return (0);
}

int _help(char **args)
{
	char *msg1 = "Welcome to the custom shell program!\n";
	char *msg2 = "Here are the avilable build-in commands:\n";
	char *msg3 = "cd: Change directory\n";
	char *msg4 = "help: Displayinformation about the custom shell\n";
	char *msg5 = "exit: Exit the shell\n";
	char *msg6 = "setenv: Set an environment variable\n";
	char *msg7 = "unsetenv: Set an environment variable\n";
	char *msg8 = "For more information, please refer to the documentation.\n";

	write(STDOUT_FILENO, msg1, strlen(msg1));
	write(STDOUT_FILENO, msg2, strlen(msg2));
	write(STDOUT_FILENO, msg3, strlen(msg3));
	write(STDOUT_FILENO, msg4, strlen(msg4));
	write(STDOUT_FILENO, msg5, strlen(msg5));
	write(STDOUT_FILENO, msg6, strlen(msg6));
	write(STDOUT_FILENO, msg7, strlen(msg7));
	write(STDOUT_FILENO, msg8, strlen(msg8));

	(void)args;
	return (1);
}

int _exit_exe(char **args)
{
	if (args[1] == NULL)
	{
		exit(0);
	}
	else
	{
		int status = atoi(args[1]);
		exit(status);
	}
}

int _ctrld(char **args)
{
	if (args[1] == NULL)
	{
		exit(0);
	}
	else
	{
		int status = atoi(args[1]);
		exit(status);
	}
}

int _ctrld(char **args)
{
	(void)args;
	write(STDOUT_FILENO, "\n", 1);
	return (1);
}

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


