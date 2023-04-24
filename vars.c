/*#include "header.h"*/
#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * Return: 1 if chain delimeter else 0
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	if (buf[*p] == '|' && buf[*p + 1] == '|')
	{
		buf[*p] = 0;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[*p] == '&' && buf[*p + 1] == '&')
	{
		buf[*p] = 0;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[*p] == ';')
	{
		buf[*p] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	(*p)++;
	return (1);
}

/**
 * check_chain - checks chain
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 * Return: Void
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	if (info->status == 0)
	{
		if (info->cmd_buf_type == CMD_OR)
		{
			while (i < len && buf[i] != 0)
				i++;
			*p = i;
		}
	}
	else
	{
		if (info->cmd_buf_type == CMD_AND)
		{
			while (i < len && buf[i] != 0)
				i++;
			*p = i;
		}
	}
}

/**
 * replace_alias - replaces an aliases
 * @info: the parameter struct
 * Return: 1 if replaced else 0
 */

int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;
	
	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		p = _strdup(_strchr(node->str, '=') + 1);
		if (!p)
			return (0);
		free(info->argv[0]);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */

int replace_vars(info_t *info)
{
	int i;
	list_t *node;
	char *value;
	
	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;
		if (!_strcmp(info->argv[i], "$?"))
			value = _strdup(convert_number(info->status, 10, 0));
		else if (!_strcmp(info->argv[i], "$$"))
			value = _strdup(convert_number(getpid(), 10, 0));
		else
		{
			node = node_starts_with(info->env, &info->argv[i][1], '=');
			value = node ? _strdup(_strchr(node->str, '=')
					+ 1) : _strdup("");
		}
		replace_string(&(info->argv[i]), value);
	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 * Return: 1 if replaced else
 */

int replace_string(char **old, char *new)
{
	int old_len = strlen(*old);
	int new_len = strlen(new);
	
	if (*old == NULL || new == NULL)
	{
		return (0);
	}
	if (new_len > old_len)
	{
		char *tmp = (char *) realloc(*old, new_len + 1);

		if (tmp == NULL)
		{
			return (0);
		}
		*old = tmp;
	}
	strcpy(*old, new);
	return (1);
}
