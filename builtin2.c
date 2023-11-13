#include "shell.h"

Alias aliases[MAX_ALIASES];

/**
 * _setenv - a sunction that sets an environment variable
 * @args: args
 *
 * Return: 0 or 1
 */
int _setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		wriet(STDERR_FILENO, "SETENV: iNVALID ARGUMENTS\N", 26);
		return (-1);
	}
	if (setenv(args[1], args[2], 1) != 0)
	{
		perror("setenv");
		return (-1);
	}

	return (0);
}

/**
 * _unsetenv - A function that unsets an environment variable
 * @args: args
 *
 * Return: 0 or -1
 */
int _unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		write(STDERR_FILENO, "unsetenv: Variable name not provided\n", 37);
		return (-1);
	}

	return (0);
}

/**
 * alias_cmd - A function that handles the alias command
 * @args: Arguments passed to the function
 *
 * Return: 0 on success, 1 on failure
 */
int alias_cmd(char **args)
{
	if (args[1] == NULL)
	{
		for (size_t i = 0; i < num_aliases; i++)
		{
			char buf[1024];
			int len = _strlen(aliases[i].name) + _strlen(aliases[i].value) + 4;

			_strcpy(buf, aliases[i].name);
			_strcat(buf, "='");
			_strcat(buf, aliases[i].value);
			_strcat(buf, "'\n");
			write(STDOUT_FILENO, buf, len);
		}
		return (0);
	}
	else
	{
		for (int i = 1; args[i] != NULL; i++)
		{
			char *name = strtok(args[i], "=");
			char *value = strtok(NULL, "=");

			if (value == NULL)
			{
				for (size_t j = 0; j < num_aliases; j++)
				{
					if (_strcmp(name, aliases[j].name) == 0)
					{
						char buf[1024];
						int len = _strlen(aliases[j].name) + _strlen(aliases[j].value) + 4;

						_strcpy(buf, aliases[j].name);
						_strcat(buf, "=");
						_strcat(buf, aliases[j].value);
						_strcat(buf, "'\n");
						write(STDOUT_FILENO, buf, len);
						break;
					}
				}
			}
			else
			{
				int fnd = 0;

				for (size_t j = 0; j < num_aliases; j++)
				{
					if (_strcmp(name, aliases[j].name) == 0)
					{
						free(aliases[j].value);
						aliases[j].value = strdup(value);
						fnd = 1;
						break;
					}
				}

				if (!fnd)
				{
					if (num_aliases < MAX_ALIASES)
					{
						aliases[num_aliases].name = strdup(name);
						aliases[num_aliases].value = strdup(value);
						num_aliases++;
					}
					else
					{
						write(STDERR_FILENO, "alias: Max number of aliases reached\n", 36);
						return (1);
					}
				}
			}
		}
	}
	return (0);
}
