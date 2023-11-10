#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

int _setenv(char **args);
int _unsetenv(char **args);
int _ctrld(char **args);
int _cd(char **args);
int _help(char **args);
int _exit_exe(char **args);
int _strcmp(char *s1, char *s2);
size_t _strncmp(char *s1, char *s2, size_t n);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *strcat(char *dest, char *src);
int _putchar(char c);

char *_get_path(char **env);
int _values_path(char **arg, char **env);
char *_getline(void);
void _getenv(char **env);
char **tokenize(char *lineptr);
int _execute(char **arg, char **av, char **env, char *lineptr, int np, int c);
void err_msg(char *8command, char *pg);
void sigintHandler(int signum);
int _env(char **env);

#endif
