#include "shell.h"

int disp_aliases(void);
int upd_aliases(char **args);
int disp_alias(char *name);
int upd_alias(char *name, char *value);

_alias aliases[MAX_ALIASES];
size_t num_aliases = 0;

/**
 * alias_cmd - A function to handle alias cmd
 * @args: Arguments passed to the function
 *
 * Return: 0 on success, 1 on failure
 */
int _alias_cmd(char **args)
{
	if (args[1] == NULL)
	{
		return (disp_aliases());
	}
	else
	{
		return (upd_aliases(args));
	}
}

/**
 * disp_aliases - Display list of aliases
 *
 * Return: 0 or 1
 */
int disp_aliases(void)
{
	size_t i;

	for (i = 0; i < num_aliases; i++)
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

/**
 * upd_aliases - Update/ create aliases
 * @args: args
 *
 * Return: 0 or 1
 */
int upd_aliases(char **args)
{
	int i;

	for (i = 1; args[i] != NULL; i++)
	{
		char *name = strtok(args[i], "=");
		char *value = strtok(NULL, "=");

		if (value == NULL)
		{
			return (disp_alias(name));
		}
		else
		{
			return (upd_alias(name, value));	
		}
	}
	return (0);
}

/**
 * disp_alias - Display a specific alias
 * @name: name of alias
 *
 * Return: 0 or 1
 */
int disp_alias(char *name)
{
	size_t j;

	for (j = 0; j < num_aliases; j++)
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
			return (0);
		}
	}
	return (1);
}

/**
 * upd_alias - Update or create an alias
 * @name: name of the alias
 * @value: value of the alias
 *
 * Return: 0 or 1
 */
int upd_alias(char *name, char *value)
{
	int fnd = 0;
	size_t j;

	for (j = 0; j < num_aliases; j++)
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
	return (0);
}
