#include "header.h"

/**
 * free_and_nullify - frees a pointer and sets it to NULL
 * @ptr: address of the pointer to free
 * Return: 1 if freed else 0
 */

int free_and_nullify(void **ptr)
{
	int status = 0;

	if (ptr && *ptr)
	{
		status = free(*ptr);

		if (status == -1)
			return (0);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
