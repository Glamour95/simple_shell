#include "shell.h"

/**
 * get_history_file - gets the history
 * @info: parameter struct
 * Return: allocated string
 */

char *get_history_file(info_t *info)
{
	char *buf, *dir;

	if (!info)
		return (NULL);
	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = _strdup(dir);
	if (!buf)
		return (NULL);
	buf = _realloc(buf, _strlen(buf) + 1, _strlen(buf)
			+ _strlen(HIST_FILE) + 2);
	if (!buf)
		return (NULL);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 * Return: 1 on success, else -1
 */

int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = NULL;
	list_t *node = NULL;

	if (!info || !info->history)
		return (-1);
	filename = get_history_file(info);
	if (!filename)
		return (-1);
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		dprintf(fd, "%s\n", node->str);
	}
	close(fd);
	return (1);
}

/**
 * read_history - reads history
 * @info: the parameter struct
 * Return: Histcount on success else 0
 */

int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = NULL;

	if (!info)
		return (0);
	filename = get_history_file(info);
	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (fstat(fd, &st) == 0)
		fsize = st.st_size;
	if (fsize < 2)
		return (close(fd), 0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (close(fd), 0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), close(fd), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
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
 * @buf: buffer containing the command
 * @linecount: the history linecount, histcount
 * Return: Always 0
 */

int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);
	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked
 * @info: Struct containing arguments
 * Return: the new histcount
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
	return (info->histcount = i);
}
