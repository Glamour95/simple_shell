/*#include "header.h"*/
#include "shell.h"

/**
 * _strcpy - Copies a string
 * @dest: The destination buffer
 * @src: The source string
 * Return: Pointer to the destination buffer
 */

char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == NULL)
		return (dest);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strdup - Duplicates a string
 * @str: The string to duplicate
 * Return: Pointer
 */

char *_strdup(const char *str)
{
	int length;
	char *ret;
	
	if (str == NULL)
		return (NULL);
	length = strlen(str);
	ret = malloc(sizeof(char) * (length + 1));
	if (ret == NULL)
		return (NULL);
	strcpy(ret, str);
	return (ret);
}

/**
 * _puts - Prints a string to stdout
 * @str: The string to print
 * Return: Nothing
 */

void _puts(char *str)
{
	if (str == NULL)
		return;
	while (*str != '\0')
	{
		_putchar(*str);
		str++;
	}
}

/**
 * _putchar - Writes the character c to stdout
 * @c: The character to print
 * Return: On success 1 else -1
 */

int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
