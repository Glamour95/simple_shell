/*#include "header.h"*/
#include "shell.h"

/**
 * _myhistory - displays the history list
 * @info: Struct containing arguments
 * Return: Always 0
 */

int _myhistory(info_t *info)
{
	list_t *node = info->history;
	size_t i = 0;

	while (node)
	{
		printf("%lu %s\n", i, node->str);
		node = node->next;
		i++;
	}
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: string
 * Return: Always 0 on success else 1
 */

int unset_alias(info_t *info, char *str)
{
	list_t *node = info->alias;
	list_t *prev = NULL;

	if (!str)
		return (1);

	while (node)
	{
		if (_strcmp(node->str, str) == 0)
		{
			if (prev)
				prev->next = node->next;
			else
				info->alias = node->next;
			free(node->str);
			free(node);
			return (0);
		}
		prev = node;
		node = node->next;
	}
	return (1);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 on success else 1
 */

int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');

	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));
	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - shows an alias string
 * @node: the alias node
 * Return: Always 0 on success else 1
 */

int print_alias(list_t *node)
{
	char *key, *value;

	if (node)
	{
		key = _strdup(node->str);
		value = _strchr(key, '=');
		if (!value)
		{
			free(key);
			return (1);
		}
		*value = 0;
		value++;
		_puts(key);
		_putchar('=');
		_putchar('"');
		_puts(value);
		_putchar('"');
		_putchar('\n');
		free(key);

		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias command
 * @info: pointer to info struct
 * Return: Always 0
 */

int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		for (node = info->alias; node; node = node->next)
			print_alias(node);
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
		{
			set_alias(info, info->argv[i]);
		}
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}
	return (0);
}
