/*#include "header.h"*/
#include "shell.h"

/**
 * bfree - frees a pointer and sets it to NULL
 * @ptr: address of the pointer to free
 * Return: 1 if freed else 0
 */

int bfree(void **ptr)
{
	if (!ptr || !*ptr)
		return (0);
	free(*ptr);
	*ptr = NULL;
	return (1);
}

