/*#include "header.h"*/
#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter
 * @av: the argument vector
 * Return: 0 on success else 1
 */

int hsh(info_t *info, char **av)
{
	ssize_t input_status = 0;
	int builtin_ret = 0;
	
	while (input_status != -1 && builtin_ret != -2)
	{
		clear_info(info);
		
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		input_status = get_input(info);
		
		if (input_status != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 * Return: -1,0,1,2
 */

int find_builtin(info_t *info)
{
	int i;
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
 * find_cmd - runs a command from PATH
 * @info: the pointer to a struct with input and output data
 * Return: void
 */

void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, j;
	
	info->path = info->argv[0];
	
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, j = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			j++;
	if (!j)
		return;
	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
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
