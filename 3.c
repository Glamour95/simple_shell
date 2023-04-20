#include "header.h"

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
 * show_alias - shows an alias string
 * @node: the alias node
 * Return: Always 0 on success else 1
 */

int show_alias(list_t *node)
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
 * _myalias - mimics the alias
 * @info: Struct containing argument
 * Return: Always 0
 */

int _myalias(info_t *info)
{
	char **args = NULL;
	int i = 0;
	char *p = NULL;

	list_t *node = NULL;

	args = split_string(info->arg, ' ');

	if (!args)
		return (1);
	if (!args[0])
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		free(args);
		return (0);
	}
	for (i = 0; args[i]; i++)
	{
		p = _strchr(args[i], '=');
		if (p)
			set_alias(info, args[i]);
		else
		{
			node = node_starts_with(info->alias, args[i], -1);
			if (node)
				print_alias(node);
			else
				perror("alias: not found");
		}
	}
	free(args);
	return (0);
}
