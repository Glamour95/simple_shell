#include "shell.h"

/**
 * _strncpy - copies a string
 * @dest: the destination string
 * @src: the source string
 * @n: the amount of characters to be copied
 * Return: the concatenated string
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i;
	int j;

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	for (j = i; j < n; j++)
	{
		dest[j] = '\0';
	}
	return (dest);
}

/**
 * _strncat - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @n: the amount of bytes used
 * Return: the concatenated string
 */

char *_strncat(char *dest, char *src, int n)
{
	int i;
	int j;

	for (i = 0; dest[i] != '\0'; i++)
		;
	for (j = 0; j < n && src[j] != '\0'; j++)
		dest[i + j] = src[j];
	dest[i + j] = (j < n) ? '\0' : dest[i + j];
	return (dest);
}

/**
 * _strchr - locates a character in a string
 * @s: the string to be parsed
 * @c: the character to look for
 * Return: a pointer
 */

char *_strchr(char *s, char c)
{
	while (*s != c && *s != '\0')
		s++;
	return ((*s == c) ? s : NULL);
}
