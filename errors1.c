#include "header.h"

/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: the converted number or -1 on error
 */

int _erratoi(char *s)
{
	int i = 0;
	int sign = 1;
	int result = 0;

	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result < 0)
				return (-1);
		}
		else
			return (-1);
	}
	return (sign * result);
}

/**
 * error_msg - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 */

void error_msg(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_num(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_num - function prints a number
 * @n: the number
 * @fd: the filedescriptor
 * Return: number of characters printed
 */

int print_num(int n, int fd)
{
	int (*putchar_func)(char) = _putchar;
	int count = 0;
	unsigned int num = n;

	if (fd == STDERR_FILENO)
		putchar_func = _eputchar;
	if (n < 0)
	{
		num = -n;
		putchar_func('-');
		count++;
	}
	if (num / 10)
		count += print_num(num / 10, fd);
	putchar_func('0' + num % 10);
	count++;
	return (count);
}

/**
 * convert_base - converter function
 * @n: number
 * @base: base
 * @flags: argument flags
 * Return: string
 */

char *convert_base(long int n, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef"
		: "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);
	if (sign)
		*--ptr = sign;
	return (ptr);
}
