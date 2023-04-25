#include "shell.h"

/**
 * get_environ - returns the string array
 * @info: Structure containing potential arguments
 * Return: Always 0
 */

char **get_environ(info_t *info)
{
	if (!info)
		return (NULL);
	if (!info->environ || info->env_changed)
	{
		bfree((void **)&(info->environ));
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Struct containing arguments
 * @var: the string env var property
 * Return: 1 or 0
 */

int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);
	while (node)
	{
		p = strchr(node->str, '=');
		if (p && strcmp(node->str, var) == 0)
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable
 * @info: Struct containing arguments
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
 */

int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;

	list_t *node;

	if (!var || !value)
		return (0);
	buf = strcat(var, "=");
	buf = strcat(buf, value);
	node = info->env;
	while (node)
	{
		if (strcmp(node->str, var) == 0)
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
