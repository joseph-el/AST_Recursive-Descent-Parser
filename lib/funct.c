#include "readline.h"

char	*rd_cat_line(char *line, int pos, char c)
{
	int		i;
	int		len;
	char	*newline;

	i = 0;
	len = rd_strlen(line);
	if (pos > len)
		pos = len;
	newline = malloc(sizeof(char) * (len + 2));
	if (!newline)
		return (NULL);
	for (; line && i < pos; i++)
		newline[i] = line[i];
	newline[i++] = c;
	for (; line && line[i - 1]; i++)
		newline[i] = line[i - 1];
	newline[i] = 0;
	free(line);
	return (newline);
}

char	*rd_remove_one(char *line, int pos)
{
	int		i;
	int		len;
	char	*newline;

	i = 0;
	if (pos == 0)
		return (line);
	len = rd_strlen(line);
	if (pos > len)
		pos = len;
	newline = malloc(sizeof(char) * (len));
	if (!newline)
		return (NULL);
	for (; line && i < pos - 1; i++)
		newline[i] = line[i];
	for (; line && line[i + 1]; i++)
		newline[i] = line[i + 1];
	newline[i] = 0;
	free(line);
	return (newline);
}

char	**rd_tabPush(char **tab, char *to_add)
{
	int		len;
	char	**ret;

	len = 0;
	while (tab && tab[len])
		len++;
	ret = malloc(sizeof(char *) * (len + 2));
	if (!ret)
		return (rd_free_tab(tab));
	len = 0;
	while (tab && tab[len]) {
		ret[len] = tab[len];
		len++;
	}
	ret[len] = rd_strdup(to_add);
	if (!ret[len++]) {
		free(ret);
		return (rd_free_tab(tab));
	}
	ret[len] = NULL;
	if (tab)
		free(tab);
	return (ret);
}

char	*rd_replace_words(char *line, int begin_word, char *repl)
{
	int		i;
	int		len;
	char	*ret;

	i = begin_word;
	len = begin_word;
	while (line && line[i] && rd_is_sep(line[i]))
		i++;
	while (line && line[i++])
		len++;
	len += rd_strlen(repl);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (i = 0; i < begin_word; i++)
		ret[i] = line[i];
	for (int j = 0; repl && repl[j]; j++)
		ret[i++] = repl[j];
	len = begin_word;
	while (line && line[len] && !rd_is_sep(line[len]))
		len++;
	for (; line && line[len]; len++)
		ret[i++] = line[len];
	ret[i] = 0;
	return (ret);
}

void	rd_print_files(char **files)
{
	for (int i = 0; files && files[i]; i++) {
		if (!(i % 6))
			rd_putstr_fd("\n", FDIN);
		rd_putstr_fd(files[i], FDIN);
		rd_putstr_fd("\t", FDIN);
	}
}

void	rd_freeCompl(char **files, t_auto_compl *cmpl)
{
	if (cmpl)
	{
		rd_free_tab(cmpl->words);
		free(cmpl);
	}
	rd_free_tab(files);
}