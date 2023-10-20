#include "shell.h"

/**
 * my_env - current environment
 * @h: Struct
 * Return: Always 0
 */
int my_env(my_t *h)
{
	print_liststr(h->_env);
	return (0);
}

/**
 * _getenv - gets environ
 * @h: Struct
 * @n: name
 * Return: value
 */
char *_getenv(my_t *h, const char *n)
{
	list_t *node = h->_env;
	char *p;

	while (node)
	{
		p = _starts(node->s, n);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * my_setenv - Initialize environment
 * @h: Struct
 * Return: Always 0
 */
int my_setenv(my_t *h)
{
	if (h->argc != 3)
	{
		_eputs("ERROR\n");
		return (1);
	}
	if (set_env(h, h->argv[1], h->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unsetenv - Remove environment
 * @h: Struct
 * Return: Always 0
 */
int my_unsetenv(my_t *h)
{
	int i;

	if (h->argc == 1)
	{
		_eputs("Few arguements.\n");
		return (1);
	}
	for (i = 1; i <= h->argc; i++)
		unset_env(h, h->argv[i]);

	return (0);
}

/**
 * _populate - populates env
 * @h: Struct
 * Return: Always 0
 */
int _populate(my_t *h)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		_nodeend(&node, environ[i], 0);
	h->_env = node;
	return (0);
}

/**
 * _getenviron - returns environ
 * @h: Struct
 * Return: Always 0
 */
char **_getenviron(my_t *h)
{
	if (!h->_environ || h->env_ch)
	{
		h->_environ = list_s(h->_env);
		h->env_ch = 0;
	}

	return (h->_environ);
}

/**
 * unset_env - Remove environment
 * @h: Struct
 * @v: var
 * Return: 1 or 0
 */
int unset_env(my_t *h, char *v)
{
	list_t *node = h->_env;
	size_t i = 0;
	char *p;

	if (!node || !v)
		return (0);

	while (node)
	{
		p = _starts(node->s, v);
		if (p && *p == '=')
		{
			h->env_ch = rm_node(&(h->_env), i);
			i = 0;
			node = h->_env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (h->env_ch);
}

/**
 * set_env - Initialize environment
 * @h: Struct
 * @v: var
 * @x: value
 * Return: Always 0
 */
int set_env(my_t *h, char *v, char *x)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!v || !x)
		return (0);

	buf = malloc(_len(v) + _len(x) + 2);
	if (!buf)
		return (1);
	_cpy(buf, v);
	_cat(buf, "=");
	_cat(buf, x);
	node = h->_env;
	while (node)
	{
		p = _starts(node->s, v);
		if (p && *p == '=')
		{
			free(node->s);
			node->s = buf;
			h->env_ch = 1;
			return (0);
		}
		node = node->next;
	}
	_nodeend(&(h->_env), buf, 0);
	free(buf);
	h->env_ch = 1;
	return (0);
}
