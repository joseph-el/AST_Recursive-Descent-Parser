#include "readline.h"

/*------------- proto ---------------*/
char	*rd_add_char(char *str, char c);

/* ================================= */

int	rd_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void	rd_putstr_fd(char *str, int fd)
{
	if (!str || fcntl(fd, F_GETFD) == -1)
		return ;
	for (int i = 0; str[i]; i++)
		write(fd, &str[i], 1);
}

void	*rd_free_tab(char **tab)
{
	for (int i = 0; tab && tab[i]; i++)
		free(tab[i]);
	free(tab);
	return (NULL);
}

int	rd_comp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*t1;
	unsigned char	*t2;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	t1 = (unsigned char *)s1;
	t2 = (unsigned char *)s2;
	while ((t1[i] && t2[i]) && (t1[i] == t2[i]))
		i++;
	return (t1[i] - t2[i]);
}

int	rd_compn(const char *s1, const char *s2, const int n)
{
	size_t			i;
	unsigned char	*t1;
	unsigned char	*t2;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	t1 = (unsigned char *)s1;
	t2 = (unsigned char *)s2;
	while ((t1[i] && t2[i]) && (t1[i] == t2[i]) && (int)i < n)
		i++;
	if (!t1[i] && t2[i])
		return (0);
	return (t1[i] - t2[i]);
}

char	*rd_strdup(char *str)
{
	int		len;
	char	*ret;

	if (!str)
		return (NULL);
	len = rd_strlen(str);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (int i = 0; str && str[i]; i++)
		ret[i] = str[i];
	ret[len] = 0;
	return (ret);
}

char	*rd_substring(char *str, int start, int end)
{
	int		i;
	int		len;
	char	*ret;

	len = rd_strlen(str);
	if (end == -1)
		len -= (start);
	else
		len -= (len - end) + (start);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (i = 0; str[start + i] && i < len; i++)
		ret[i] = str[start + i];
	ret[i] = 0;
	return (ret);
}

char	*rd_add_char(char *str, char c)
{
	int		len;
	char	*ret;

	len = rd_strlen(str) + 2;
	ret = malloc(sizeof(char) * len);
	if (!ret)
	{
		free(str);
		return (NULL);
	}
	for (int i = 0; str && str[i]; i++)
		ret[i] = str[i];
	ret[len - 2] = c;
	ret[len - 1] = 0;
	free(str);
	return (ret);
}

char	*rd_read_one_line(int fd)
{
	char	*ret;
	int		rd_bytes;
	char	buff[2] = {0};

	ret = NULL;
	rd_bytes = 0;
	rd_bytes = read(fd, buff, 1);
	while (rd_bytes > 0 && buff[0])
	{
		if (buff[0] == '\n')
		{
			if (!ret)
				ret = rd_strdup("\n");
			break ;
		}
		ret = rd_add_char(ret, buff[0]);
		if (!ret)
			break ;
		rd_bytes = read(fd, buff, 1);
	}
	return (ret);
}
