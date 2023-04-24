/*#include "header.h"*/
#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @dest: the pointer to the memory area to fill
 * @value: the byte to fill dest with
 * @size: the amount of bytes to fill
 * Return: a pointer
 */

char *_memset(char *dest, char value, unsigned int size)
{
	unsigned int index;

	for (index = 0; index < size; index++)
		dest[index] = value;
	return (dest);
}

/**
 * ffree - frees a string of strings
 * @str_array: string of strings
 */

void ffree(char **pp)
{
	char **temp = pp;

	if (!pp)
	{
		return;
	}
	while (*pp)
	{
		free(*pp++);
	}
	free(temp);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 * Return: pointer to the reallocated block or NULL if failed
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;
	unsigned int min_size;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size == old_size)
		return (ptr);
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	min_size = old_size < new_size ? old_size : new_size;
	while (min_size--)
		new_ptr[min_size] = ((char *)ptr)[min_size];
	free(ptr);
	return (new_ptr);
}
