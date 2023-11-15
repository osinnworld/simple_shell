#include "shell.h"
/**
 * _strcat - a function that concatenates two strings
 * @dest: The destination string
 * @src: The source string
 *
 * Return: A pointer to the resulting string
 */
char *_strcat(char *dest, char *src)
{
	int i, j = 0;

	for (i = 0; dest[i] != '\0'; i++)
	{
	}
	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strlen - A function that calculates the length of the string
 * @s: An input string
 *
 * Return: The length of the string
 */
int _strlen(char *s)
{
	int i;

	for (i = 0; s[i] != 0; i++)
		;

	return (i);
}

/**
 * _strcmp - a function that comapres two strings
 * @s1: First string
 * @s2: Second string
 *
 * Return: 0 or 1
 */
int _strcmp(const char *s1, const char *s2)
{
	int j, i = 0;

	while (s1[i] != 0 && s2[i] != 0 && s1[i] == s2[i])
		i++;
	j = s1[i] - s2[i];
	return (j);
}

/**
 * _strncmp -  a function that compares two strings
 * up to a specified number of characters
 * @s1: first string
 * @s2: second string
 * @n: the number of characters to compare
 *
 * Return: 0 or 1
 */
size_t _strncmp(char *s1, char *s2, size_t n)
{
	size_t i, j;

	for (j = 0; s1[j] != '\0' && j < n; j++)
	{
		i = s1[j] - s2[j];

		if (i != 0)
		{
			return (i);
		}
	}
	return (0);
}

/**
 * _strcpy - a function that copies a string
 * @dest: destination string
 * @src: the source string
 *
 * Return: pointer to the resulting string
 */
char *_strcpy(char *dest, const char *src)
{
	int i = 0;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return (dest);
}
