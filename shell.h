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


typedef struct {
	char *command;
	int (*func)(char **);
} builtin_cmd;

extern builtin_cmd builtins[];

typedef struct {
	char *name;
	char *value;
} Alias;


int _setenv(char **);
int _unsetenv(char **);
int _ctrld(char **);
int _cd(char **);
int _help(char **);
int _exit_exe(char **);

int _strcmp(char *s1, char *s2);
size_t _strncmp(char *s1, char *s2, size_t n);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);

int _execute(char **arg, char **av, char **env, char *ptr, int np, int c);
void err_msg(char *command, char *pg, int status);
int _absolute_path(char **arg, char **env);
char *_get_path(char **env);
char *_getline(void);
char **tokenize(char *ptr);
int num_builtins(void);
int _execute_builtin(char **args);

#endif
