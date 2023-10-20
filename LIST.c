#include "shell.h"

/**
 * _node - adds node
 * @h: head
 * @s: string
 * @n: index
 * Return: size
 */
list_t *_node(list_t **h, const char *s, int n)
{
	list_t *_new;

	if (!h)
		return (NULL);
	_new = malloc(sizeof(list_t));
	if (!_new)
		return (NULL);
	_memset((void *)_new, 0, sizeof(list_t));
	_new->n = n;
	if (s)
	{
		_new->s = _dup(s);
		if (!_new->s)
		{
			free(_new);
			return (NULL);
		}
	}
	_new->next = *h;
	*h = _new;
	return (_new);
}

/**
 * _nodeend - adds node to end
 * @h: head
 * @s: string
 * @n: index
 * Return: size
 */
list_t *_nodeend(list_t **h, const char *s, int n)
{
	list_t *_new, *node;

	if (!h)
		return (NULL);

	node = *h;
	_new = malloc(sizeof(list_t));
	if (!_new)
		return (NULL);
	_memset((void *)_new, 0, sizeof(list_t));
	_new->n = n;
	if (s)
	{
		_new->s = _dup(s);
		if (!_new->s)
		{
			free(_new);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = _new;
	}
	else
		*h = _new;
	return (_new);
}

/**
 * print_liststr - prints string
 * @h: head
 * Return: size
 */
size_t print_liststr(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->s ? h->s : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * rm_node - delete node
 * @h: head
 * @n: index
 * Return: 1 or 0
 */
int rm_node(list_t **h, unsigned int n)
{
	list_t *node, *prev;
	unsigned int i = 0;

	if (!h || !*h)
		return (0);

	if (!n)
	{
		node = *h;
		*h = (*h)->next;
		free(node->s);
		free(node);
		return (1);
	}
	node = *h;
	while (node)
	{
		if (i == n)
		{
			prev->next = node->next;
			free(node->s);
			free(node);
			return (1);
		}
		i++;
		prev = node;
		node = node->next;
	}
	return (0);
}

/**
 * _freelist - free nodes
 * @h: head
 */
void _freelist(list_t **h)
{
	list_t *node, *next, *head;

	if (!h || !*h)
		return;
	head = *h;
	node = head;
	while (node)
	{
		next = node->next;
		free(node->s);
		free(node);
		node = next;
	}
	*h = NULL;
}

/**
 * list_l - length of list
 * @h: head
 * Return: size
 */
size_t list_l(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_s - array of strings
 * @h: head
 * Return: array of strings
 */
char **list_s(list_t *h)
{
	list_t *node = h;
	size_t i = list_l(h), j;
	char **ss;
	char *s;

	if (!h || !i)
		return (NULL);
	ss = malloc(sizeof(char *) * (i + 1));
	if (!ss)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		s = malloc(_len(node->s) + 1);
		if (!s)
		{
			for (j = 0; j < i; j++)
				free(ss[j]);
			free(ss);
			return (NULL);
		}

		s = _cpy(s, node->s);
		ss[i] = s;
	}
	ss[i] = NULL;
	return (ss);
}

/**
 * print_list - ptint list
 * @h: head
 * Return: size
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_n(h->n, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->s ? h->s : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * _nodestarts - node string
 * @h: head
 * @px: string
 * @c: char
 * Return: node or null
 */
list_t *_nodestarts(list_t *h, char *px, char c)
{
	char *p = NULL;

	while (h)
	{
		p = _starts(h->s, px);
		if (p && ((c == -1) || (*p == c)))
			return (h);
		h = h->next;
	}
	return (NULL);
}

/**
 * get_node - index of node
 * @h: head
 * @node: node
 * Return: index or -1
 */
ssize_t get_node(list_t *h, list_t *node)
{
	size_t i = 0;

	while (h)
	{
		if (h == node)
			return (i);
		h = h->next;
		i++;
	}
	return (-1);
}
