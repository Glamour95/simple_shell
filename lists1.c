#include "shell.h"

/**
 * list_len - determines length of linked list
 * @h: pointer to first node
 * Return: size of list
 */

size_t list_len(const list_t *h)
{
	size_t i = 0;

	for (i = 0; h; i++)
		h = h->next;
	return (i);
}

/**
 * list_to_strings - returns an array of strings
 * @head: pointer
 * Return: array of strings
 */

char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = 0, j = 0;
	char **strs;

	if (!head || !list_len(head))
		return (NULL);
	strs = malloc(sizeof(char *) * (list_len(head) + 1));
	if (!strs)
		return (NULL);
	while (node)
	{
		strs[i] = malloc(strlen(node->str) + 1);
		if (!strs[i])
		{
			while (j < i)
				free(strs[j++]);
			free(strs);
			return (NULL);
		}
		strcpy(strs[i], node->str);
		node = node->next;
		i++;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * print_list - prints all elements
 * @h: pointer to first node
 * Return: size of list
 */

size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		printf("%d: %s\n", h->num, h->str ? h->str : "(nil)");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - returns node
 * @node: pointer to first node
 * @prefix: string to match
 * @c: the next character after prefix to match
 * Return: match node or null
 */

list_t *node_starts_with(list_t *node, char *prefix, char next_char)
{
	if (node == NULL || prefix == NULL)
		return (NULL);
	do {
		if (strncmp(node->str, prefix, strlen(prefix)) == 0)
		{
			if (next_char == -1 ||
					node->str[strlen(prefix)] == next_char)
				return (node);
		}
		node = node->next;
	} while (node);
	return (NULL);
}

/**
 * get_node_index - checks if a string starts with a prefix
 * @head: the string to check
 * @node: the prefix to match
 * Return: pointer
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	ssize_t i = 0;

	if (!head || !node)
		return (-1);
	while (head && head != node)
	{
		head = head->next;
		i++;
	}
	return (head ? i : -1);
}
