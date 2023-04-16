#include <stdio.h>
#include <ctype.h>

/**
 * interactive - check if shell is interactive
 * @info: address for struct
 * Return: 1 if true else 0
 */

int interactive(info_t *info)
{
	return (isatty(0));
}

/**
 * is_delim - checks if character is delimeter
 * @c: the character to be checked
 * @delim: string
 * Return: if true 1 else 0
 */

int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (c == *delim++)
			return (1);
	}
	return (0);
}

/**
 * _isalpha - checks alphabet characters
 * @c: the character to be checked
 * Return: 1 if true else 0
 */

int _isalpha(int c)
{
	return (isalpha(c));
}
/**
 * _atoi - converts string to integer
 * @s: string
 * Return: converted number or else 0
 */

int _atoi(char *s)
{
	int sign = 1;

	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	int res = 0;

	while (*s >= '0' && *s <= '9')
	{
		res = res * 10 + (*s - '0');
		s++;
	}
	return (sign * res);
}
