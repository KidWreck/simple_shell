#include "shell.h"

/**
 * my_exit - exit
 * @h: Struct
 *  Return: exit
 */
int my_exit(my_t *h)
{
	int x;
	
	if (h->argv[1]) 
	{
		x = _erratoi(h->argv[1]);
		if (x == -1)
		{
			h->status = 2;
			print_err(h, "NOT a number: ");
			_eputs(h->argv[1]);
			_eputchar('\n');
			return (1);
		}
		h->err_num = _erratoi(h->argv[1]);
		return (-2);
	}
	h->err_num = -1;
	return (-2);
}

/**
 * my_cd - change cd
 * @h: Struct
 * Return: Always 0
 */
int my_cd(my_t *h)
{
	char *s, *d, buf[1024];
	int ret;

	s = getcwd(buf, 1024);
	if (!s)
		_puts("ERROR!!\n");
	if (!h->argv[1])
	{
		d = _getenv(h, "HOME=");
		if (!d)
			ret = chdir((d = _getenv(h, "PWD=")) ? d : "/");
		else
			ret = chdir(d);
	}
	else if (_cmp(h->argv[1], "-") == 0)
	{
		if (!_getenv(h, "OLD PWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(h, "OLD PWD=")), _putchar('\n');
		ret = chdir((d = _getenv(h, "OLD PWD=")) ? d : "/");
	}
	else
		ret = chdir(h->argv[1]);
	if (ret == -1)
	{
		print_err(h, "can't CD to ");
		_eputs(h->argv[1]), _eputchar('\n');
	}
	else
	{
		set_env(h, "OLD PWD", _getenv(h, "PWD="));
		set_env(h, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
 * my_help - changes the current directory of the process
 * @h: Struct
 *  Return: Always 0
 */
int my_help(my_t *h)
{
	char **a;

	a = h->argv;
	_puts("WORKS \n");
	if (0)
		_puts(*a);
	return (0);
}

/**
 * my_history - history list
 * @h: Struct
 *  Return: Always 0
 */
int my_history(my_t *h)
{
	print_list(h->history);
	return (0);
}

/**
 * unset_a - unsets alias
 * @info: struct
 * @s: string
 * Return: 0 or 1
 */
int unset_a(my_t *h, char *s)
{
	char *p, c;
	int ret;

	p = _chr(s, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = rm_node(&(h->alias),
		get_node(h->alias, _nodestarts(h->alias, s, -1)));
	*p = c;
	return (ret);
}

/**
 * set_a - sets alias
 * @h: struct
 * @s: string
 * Return: 0 or 1
 */
int set_a(my_t *h, char *s)
{
	char *p;

	p = _chr(s, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_a(h, s));

	unset_a(h, s);
	return (_nodeend(&(h->alias), s, 0) == NULL);
}

/**
 * print_alias - prints alias
 * @node: node
 * Return: 0 or 1
 */
int print_alias(list_t *node)
{
	char *p = NULL, *y = NULL;

	if (node)
	{
		p = _chr(node->s, '=');
		for (y = node->s; y <= p; y++)
			_putchar(*y);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - mimics alias 
 * @h: Struct
 * Return: Always 0
 */
int my_alias(my_t *h)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (h->argc == 1)
	{
		node = h->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; h->argv[i]; i++)
	{
		p = _chr(h->argv[i], '=');
		if (p)
			set_a(h, h->argv[i]);
		else
			print_alias(_nodestarts(h->alias, h->argv[i], '='));
	}

	return (0);
}
