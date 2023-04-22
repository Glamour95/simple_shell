#include "header.h"

/**
 * get_history_file - gets the history
 * @info: parameter struct
 * Return: allocated string
 */

char *get_history_file(info_t *info)
{
	char *home = _getenv("HOME");
	char *file = ".simple_shell_history";
	char *path;
	int len;

	if (home == NULL || file == NULL)
		return (NULL);
	len = _strlen(home) + _strlen(file) + 2;
	path = malloc(sizeof(char) * len);
	if (path == NULL)
		return (NULL);
	_strcpy(path, home);
	_strcat(path, "/");
	_strcat(path, file);
	return (path);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 * Return: 1 on success, else -1
 */

int write_history(info_t *info)
{
	char *file;
	int fd;
	ssize_t bytes;

	if (info == NULL)
		return (-1);
	file = get_history_file(info);
	if (file == NULL)
		return (-1);
	fd = open(file, O_WRONLY |
			O_CREAT | O_APPEND, 0600);
	if (fd == -1)
		return (-1);
	bytes = write(fd, info->line,
			_strlen(info->line));
	if (bytes == -1)
		return (-1);
	close(fd);
	free(file);
	return (1);
}

/**
 * read_history - reads history
 * @info: the parameter struct
 * Return: Hcount on success else 0
 */

int read_history(info_t *info)
{
	int fd;
	char *file;
	char *buf = NULL;
	size_t len = 0;
	ssize_t bytes;
	int linecount = 0;

	if (info == NULL)
		return (0);
	file = get_history_file(info);
	if (file == NULL)
		return (0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	while ((bytes = getline(&buf, &len, fd)) != -1)
	{
		buf[bytes - 1] = 0;
		build_history_list(info, buf, linecount++);
	}
	close(fd);
	free(file);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Struct containing arguments
 * @buffer: buffer containing the command
 * @linecount: the history linecount, hcount
 * Return: Always 0
 */

int build_history_list(info_t *info, char *buffer, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buffer, linecount);
	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked
 * @info: Struct containing arguments
 * Return: the new hcount
 */

int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->hcount = i);
}
