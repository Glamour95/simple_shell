#include "header.h"

/**
 * _myenv - prints the current environment
 * @info: Struct containing argument
 * Return: Always 0
 */

int _myenv(info_t *info)
{
	char **env = environ;
	int i = 0;

	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: Struct containing arguments
 * @name: environ var name
 * Return: the value
 */

char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;
	size_t len = strlen(name);

	while (node != NULL)
	{
		if (strncmp(node->str, name, len) == 0
				&& node->str[len] == '=')
		{
			return (node->str + len + 1);
		}
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable
 * @info: Struct containing arguments
 * Return: Always 0
 */

int _mysetenv(info_t *info)
{
	char *name = info->argv[1];
	char *value = info->argv[2];
	char *var;
	int len;

	if (name == NULL || value == NULL
			|| _strchr(name, '=') != NULL)
		return (-1);
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (-1);
	}
	len = _strlen(name) + _strlen(value) + 2;
	var = malloc(sizeof(char) * len);
	if (var == NULL)
		return (-1);
	_strcpy(var, name);
	_strcat(var, "=");
	_strcat(var, value);
	if (_unsetenv(info, name) == -1)
		return (-1);
	return (_add_node_end(&(info->env), var));
}

/**
 * _myunsetenv - Remove one or more environment variables
 * @info: Struct containing arguments
 * Return: 0 on success, -1 on failure
 */

int _myunsetenv(info_t *info)
{
	char *name;
	int i, status = 0;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (-1);
	}
	for (i = 1; i < info->argc; i++)
	{
		name = info->argv[i];
		if (name == NULL || _strchr(name, '=') != NULL)
			continue;
		if (_unsetenv(info, name) == -1)
			status = -1;
	}
	return (status);
}

/**
 * populate_env_list - populates env linked list
 * @info: Struct containing arguments
 * Return: Always 0
 */

int populate_env_list(info_t *info)
{
	char **envp = info->envp;
	char *var;
	int i;

	for (i = 0; envp[i] != NULL; i++)
	{
		var = _strdup(envp[i]);
		if (var == NULL)
			return (-1);
		if (_add_node_end(&(info->env), var) == NULL)
			return (-1);
	}
	return (0);
}
