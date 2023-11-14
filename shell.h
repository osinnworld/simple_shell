#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>

#define MAX_ALIASES 50

typedef struct {
	char *command;
	int (*func)(char **);
} builtin_cmd;

extern builtin_cmd builtins[];

typedef struct {
	char *name;
	char *value;
} Alias;

extern Alias aliases[MAX_ALIASES];

extern size_t num_aliases;

int _setenv(char **);
int _unsetenv(char **);
int _ctrld(char **);
int _cd(char **);
int _help(char **);
int _exit_exe(char **);
size_t _strncmp(char *, char *, size_t);
int _strlen(char *);
char *_strcpy(char *, const char *);
char *_strcat(char *, char *);
int _strcmp(const char *, const char *);

char *_get_path(char **);
int _absolute_path(char **, char **);
char *_getline(void);
void _getenv(char **);
char **tokenize(char *, const char *);
int _execute(char **, char **, char **, char *, int , int);
void err_msg(char *, char *);
void sigint_handler(int);
int _env(char **);
char **parse_path(char *);
int alias_cmd(char **);
int r_alias(char **, const char *, const char *);
size_t num_builtins(void);



#endif
