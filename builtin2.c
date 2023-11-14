#include "shell.h"

Alias aliases[MAX_ALIASES];
size_t num_aliases = 0;

/**
 * alias_cmd - A function to handle alias cmd
 * @args: Arguments passed to the function
 *
 * Return: 0 on success, 1 on failure
 */
int alias_cmd(char **args)
{
	char buf[1024];
	int len;

	if (args[1] == NULL)
	{
		size_t i;

		for (i = 0; i < num_aliases; i++)
		{
			len = _strlen(aliases[i].name) + _strlen(aliases[i].value) + 4;
			_strcpy(buf, aliases[i].name);
			_strcat(buf, "='");
			_strcat(buf, aliases[i].value);
			_strcat(buf, "'\n");
			write(STDOUT_FILENO, buf, len);
			break;
		}
		return (0);
	}
	else
	{
		int i;

		for (i = 1; args[i] != NULL; i++)
		{
			char *name = strtok(args[i], "=");
			char *value = strtok(NULL, "=");

			if (value == NULL)
			{
				size_t j;
				
				for (j = 0; j < num_aliases; j++)
				{
					if (_strcmp(name, aliases[j].name) == 0)
					{
						len = _strlen(aliases[j].name) + _strlen(aliases[j].value) + 4;
						_strcpy(buf, aliases[j].name);
						_strcat(buf, "='");
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
			}
		}
	}
	return (0);
}
