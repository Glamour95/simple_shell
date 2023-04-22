#include <header.h>

/**
 * _eputs - prints an input
 * @str: the string to be printed
 * Return: Nothing
 */

void _eputs(char *str)
{
	if (!str)
		return;
	printf("%s", str);
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 * Return: On success 1 else -1
 */

int _eputchar(char c)
{
	if (write(2, &c, 1) == -1)
	{
		return (-1);
	}
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1 else -1
 */

int _putfd(char c, int fd)
{
	if (write(fd, &c, 1) == -1)
	{
		return (-1);
	}
	return (1);
}
/**
 * _putfd - writes the character c to a given file
 * @c: The character to print
 * @fd: The filedescriptor to write to
 * Return: On success 1 else -1
 */

int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		if (write(fd, buf, i) == -1)
		{
			return (-1);
		}
		i = 0;
	}
	if (c != BUF_FLUSH)
	{
		buf[i++] = c;
	}
	return (1);
}

/**
 * _putsfd - prints an input string to a given file
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 * Return: the number of chars put on success, or -1 on error.
 */

int _putsfd(char *str, int fd)
{
	int i = 0;
	int count = 0;
	int result;

	if (!str)
	{
		return (-1);
	}
	while (str[i])
	{
		result = _putfd(str[i++], fd);
		if (result == -1)
		{
			return (-1);
		}
		count += result;
	}
	result = _putfd(BUF_FLUSH, fd);
	if (result == -1)
	{
		return (-1);
	}
	return (count);
}
