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

char *_getenv(info_t *info, const char *name)
{
    list_t *node = info->env;
    char *p;
    size_t len = strlen(name);

    /* loop through the list and compare each string with the name */
    while (node != NULL)
    {
        /* check if the string starts with the name followed by '=' */
        if (strncmp(node->str, name, len) == 0 && node->str[len] == '=')
        {
            /* return a pointer to the value after the '=' */
            return (node->str + len + 1);
        }
        node = node->next;
    }

    return (NULL);
}
