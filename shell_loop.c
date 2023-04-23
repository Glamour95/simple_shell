#include "header.h"
#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter
 * @av: the argument vector
 * Return: 0 on success else 1
 */

int hsh(info_t *info, char **av)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read = 0;
	int status = 0;

	info->av = av;
	info->env = environ;
	info->line = NULL;
	info->args = NULL;
	info->path = NULL;
	info->status = 0;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
	while ((read = getline(&line, &len, stdin)) != -1)
	{
		info->line = line;
		info->args = split_line(line);

		if (info->args && info->args[0])
			status = check_builtins(info) || execute(info);
		free(line);
		free(info->args);
		line = NULL;
		info->args = NULL;

		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
	}
	free(line);
	return (status == -1 ? errno : status);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 * Return: -1,0,1,2
 */

int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};
	info->line_count++;
	for (i = 0; builtintbl[i].type; i++)
	{
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
			return (builtintbl[i].func(info));
	}
	return (-1);
}

/**
 * find_cmd - finds a command
 * @info: the parameter
 * Return: void
 */

void find_cmd(info_t *info)
{
	char *path;

	info->path = info->argv[0];

	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	if (!has_arg(info))
		return;
	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else if (is_cmd(info, info->argv[0]))
	{
		fork_cmd(info);
	}
	else if (*(info->arg) != '\n')
	{
		info->status = 127;
		print_error(info, "not found\n");
	}
}

/**
 * fork_cmd - forks an exec thread to run cmd
 * @info: the parameter
 * Return: void
 */

void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			print_error(info, "execve failed\n");
			free_info(info, 1);
			exit(errno == EACCES ? 126 : 1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
