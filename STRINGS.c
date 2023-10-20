#include "shell.h"

/**
 * _len - length string
 * @s: string
 * Return: length of string
 */
int _len(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _cmp - comparison of two strangs.
 * @s1: string
 * @s2: string
 * Return: + or - or 0
 */
int _cmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * _starts - starts
 * @hay: string
 * @n: substring
 * Return: pointer
 */
char *_starts(const char *hay, const char *n)
{
	while (*n)
		if (*n++ != *hay++)
			return (NULL);
	return ((char *)hay);
}

/**
 * _cat - concatenates
 * @dest: dest
 * @src: src
 * Return: dest
 */
char *_cat(char *dest, char *src)
{
	char *tmp = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (tmp);
}

/**
 * _cpy - copy
 * @dest: dest
 * @src: src
 * Return: dest
 */
char *_cpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _dup - duplicates
 * @s: string
 * Return: pointer
 */
char *_dup(const char *s)
{
	int len = 0;
	char *tmp;

	if (s == NULL)
		return (NULL);
	while (*s++)
		len++;
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (NULL);
	for (len++; len--;)
		tmp[len] = *--s;
	return (tmp);
}

/**
 *_puts - prints string
 *@s: string
 */
void _puts(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		_putchar(s[i]);
		i++;
	}
}

/**
 * _putchar - writes char
 * @c: char
 *
 * Return: 1 or -1
 */
int _putchar(char c)
{
	static int i;
	static char buf[1024];

	if (c == FLUSH || i >= 1024)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 **_strncpy - copy string
 *@dest: dest
 *@src: src
 *@x: char
 *Return: string
 */
char *_strncpy(char *dest, char *src, int x)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < x - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < x)
	{
		j = i;
		while (j < x)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates strings
 *@dest: dest
 *@src: src
 *@n: char
 *Return: string
 */
char *_strncat(char *dest, char *src, int x)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < x)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < x)
		dest[i] = '\0';
	return (s);
}

/**
 **_chr - locate char
 *@s: string
 *@c: char
 *Return: pointer
 */
char *_chr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

/**
 * strtow - splits
 * @s: string
 * @d: delimeter
 * Return: pointer
 */

char **_strtow(char *s, char *d)
{
	int i, j, k, x, num = 0;
	char **z;

	if (s == NULL || s[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; s[i] != '\0'; i++)
		if (!dlm(s[i], d) && (dlm(s[i + 1], d) || !s[i + 1]))
			num++;

	if (num == 0)
		return (NULL);
	z = malloc((1 + num) * sizeof(char *));
	if (!z)
		return (NULL);
	for (i = 0, j = 0; j < num; j++)
	{
		while (dlm(s[i], d))
			i++;
		k = 0;
		while (!dlm(s[i + k], d) && s[i + k])
			k++;
		z[j] = malloc((k + 1) * sizeof(char));
		if (!z[j])
		{
			for (k = 0; k < j; k++)
				free(z[k]);
			free(z);
			return (NULL);
		}
		for (x = 0; x < k; x++)
			z[j][x] = s[i++];
		z[j][x] = 0;
	}
	z[j] = NULL;
	return (z);
}

/**
 * strtow2 - splits
 * @s: string
 * @d: delimeter
 * Return: pointer
 */
char **_strtow2(char *s, char d)
{
	int i, j, k, x, num = 0;
	char **z;

	if (s == NULL || s[0] == 0)
		return (NULL);
	for (i = 0; s[i] != '\0'; i++)
		if ((s[i] != d && s[i + 1] == d) || (s[i] != d && !s[i + 1]) || s[i + 1] == d)
			num++;
	if (num == 0)
		return (NULL);
	z = malloc((1 + num) * sizeof(char *));
	if (!z)
		return (NULL);
	for (i = 0, j = 0; j < num; j++)
	{
		while (s[i] == d && s[i] != d)
			i++;
		k = 0;
		while (s[i + k] != d && s[i + k] && s[i + k] != d)
			k++;
		z[j] = malloc((k + 1) * sizeof(char));
		if (!z[j])
		{
			for (k = 0; k < j; k++)
				free(z[k]);
			free(z);
			return (NULL);
		}
		for (x = 0; x < k; x++)
			z[j][x] = s[i++];
		z[j][x] = 0;
	}
	z[j] = NULL;
	return (z);
}
