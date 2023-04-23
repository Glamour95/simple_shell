#include "header.h"
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
	int i;

	for (i = 0; i < info->chain_len; i++)
	{
		if (buf[*p] == info->chain[i])
		{
			buf[*p] = 0;
			(*p)++;
			return (1);
		}
	}
	return (0);
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
	int i, j;
	char *alias;

	for (i = 0; i < info->argc; i++)
	{
		lias = get_alias(info->argv[i], info);
		if (alias != NULL)
		{
			free(info->argv[i]);
			info->argv[i] = _strdup(alias);

			if (info->argv[i] == NULL)
				return (0);
			return (1);
		}
	}
	return (0);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */

int replace_vars(info_t *info)
{
	int i;
	char *var, *val;

	for (i = 0; i < info->argc; i++)
	{
		if (info->argv[i][0] == '$')
		{
			var = info->argv[i] + 1;
			if (strcmp(var, "?") == 0)
			{
				val = get_exit_status();
			}
			else if (strcmp(var, "$") == 0)
			{
				val = get_pid();
			}
			else
			{
				val = get_env(var, info);
			}
			free(info->argv[i]);
			info->argv[i] = strdup(val ? val : "");
		}
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
	if (*old == NULL || new == NULL)
	{
		return (0);
	}
	int old_len = strlen(*old);
	int new_len = strlen(new);

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
