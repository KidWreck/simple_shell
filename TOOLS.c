#include "shell.h"

/**
 * my_int - interactive mode
 * @h: struct
 * Return: 1 or 0
 */
int my_int(my_t *h)
{
	return (isatty(STDIN_FILENO) && h->readfd <= 2);
}

/**
 * dlm -delimeter
 * @c: char
 * @s: string
 * Return: 1 or 0
 */
int dlm(char c, char *s)
{
	while (*s)
		if (*s++ == c)
			return (1);
	return (0);
}

/**
 *_alpha - alphabet
 *@c: char
 *Return: 1 or 0
 */

int _alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts to integer
 *@s: string
 *Return: int
 */

int _atoi(char *s)
{
	int i, sign = 1, f = 0, x;
	unsigned int r = 0;

	for (i = 0;  s[i] != '\0' && f != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			f = 1;
			r *= 10;
			r += (s[i] - '0');
		}
		else if (f == 1)
			f = 2;
	}

	if (sign == -1)
		x = -r;
	else
		x = r;

	return (x);
}

/**
 * _erratoi - converts to int
 * @s: string
 * Return: 0 or -1
 */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int r = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			r *= 10;
			r += (s[i] - '0');
			if (r > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (r);
}

/**
 * print_err - error message
 * @h: struct
 * @s: string
 * Return: 0 or -1
 */
void print_err(my_t *h, char *s)
{
	_eputs(h->fname);
	_eputs(": ");
	print_d(h->l_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(h->argv[0]);
	_eputs(": ");
	_eputs(s);
}

/**
 * print_d - prints base 10
 * @x: input
 * @fd: filedescriptor
 * Return: int
 */
int print_d(int x, int fd)
{
	int (*klam)(char) = _putchar;
	int i, num = 0;
	unsigned int m6lq, tmp;

	if (fd == STDERR_FILENO)
		klam = _eputchar;
	if (x < 0)
	{
		m6lq = -x;
		klam('-');
		num++;
	}
	else
		m6lq = x;
	tmp = m6lq;
	for (i = 100000000; i > 1; i /= 10)
	{
		if (m6lq / i)
		{
			klam('0' + tmp / i);
			num++;
		}
		tmp %= i;
	}
	klam('0' + tmp);
	num++;

	return (num);
}

/**
 * convert_n - clone of itoa
 * @num: number
 * @b: base
 * @f: flags
 * Return: string
 */
char *convert_n(long int num, int b, int f)
{
	static char *a;
	static char buf[50];
	char sign = 0;
	char *p;
	unsigned long n = num;

	if (!(f & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	a = f & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buf[49];
	*p = '\0';

	do	{
		*--p = a[n % b];
		n /= b;
	} while (n != 0);

	if (sign)
		*--p = sign;
	return (p);
}

/**
 * rm_comments - replaces '#' with '\0'
 * @p: pointer
 * Return: Always 0;
 */
void rm_comments(char *p)
{
	int i;

	for (i = 0; p[i] != '\0'; i++)
		if (p[i] == '#' && (!i || p[i - 1] == ' '))
		{
			p[i] = '\0';
			break;
		}
}
