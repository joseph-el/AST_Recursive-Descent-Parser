#include "readline.h"

/*------------- proto ---------------*/
static int	rd_len_sep_string(const char *str);
static char	*rd_get_next_word(int *index, const char *str, int *tmp);

/* ================================= */

int	rd_is_sep(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ' || c == ';' || c == 34 || c == 39);
}

char	**rd_list_files(char *curr_dir, char *line, int cursor, int (*cmp)())
{
	DIR				*dirp;
	char			**ret;
	struct dirent	*entity;

	ret = NULL;
	dirp = opendir(curr_dir);
	while (1)
	{
		entity = readdir(dirp);
		if (!entity)
			break ;
		else if (cursor && (*cmp)(line, entity->d_name, cursor - 1))
			continue ;
		ret = rd_tabPush(ret, entity->d_name);
		if (!ret)
			break ;
	}
	closedir(dirp);
	return (ret);
}

static int	rd_len_sep_string(const char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str && str[i])
	{
		while (rd_is_sep(str[i]))
			i++;
		if (!rd_is_sep(str[i]) && str[i])
		{
			counter++;
			while (!rd_is_sep(str[i]) && str[i])
				i++;
		}
	}
	return (counter + 1);
}

static char	*rd_get_next_word(int *index, const char *str, int *tmp)
{
	int		i;
	int		len;
	char	*ret;

	i = 0;
	len = 0;
	while (str[*index] && rd_is_sep(str[*index]))
		(*index)++;
	*tmp = *index;
	while (str[*index + len] && !rd_is_sep(str[*index + len]))
		len++;
	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (i < len)
		ret[i++] = str[(*index)++];
	ret[i] = 0;
	return (ret);
}

char	**rd_splitLine(char const *s, int cursor, t_auto_compl *cmpl)
{
	int		i;
	int		j;
	int		ac;
	int		tmp;
	char	**ret;

	i = 0;
	j = 0;
	ac = rd_len_sep_string(s);
	ret = malloc(ac * sizeof(char *));
	if (!ret)
		return (NULL);
	while (i < ac - 1)
	{
		ret[i] = rd_get_next_word(&j, s, &tmp);
		if (cmpl->n == -1 && cursor <= j)
		{
			cmpl->n = i;
			cmpl->pos = j - (rd_strlen(ret[i]) + 1);
			if (1 == ac - 2)
				cmpl->pos++;
			cmpl->pos = cursor - cmpl->pos;
			cmpl->begin_word = tmp;
		}
		i++;
	}
	if (cmpl->pos < 0)
		cmpl->n = -1;
	ret[i] = NULL;
	return (ret);
}

t_auto_compl	*rd_extract_word(char *line, int cursor)
{
	int				i;
	t_auto_compl	*ret;

	i = 0;
	while (line && line[i] && rd_is_sep(line[i]))
		i++;
	if (line && !line[i])
		return (NULL);

	ret = malloc(sizeof(t_auto_compl));
	if (!ret)
		return (NULL);

	ret->pos = -1;
	ret->n = -1;

	ret->words = rd_splitLine(line, cursor, ret);
	if (!ret->words) {
		free(ret);
		return (NULL);
	}
	return (ret);
}

void	rd_change_line(t_auto_compl *cmpl, char *repl, t_readline *rdl)
{
	char	*new_line;

	new_line = rd_replace_words(rdl->line, cmpl->begin_word, repl);
	if (!new_line)
		return ;
	free(rdl->line);
	rdl->line = new_line;
	rdl->cursor = cmpl->begin_word + rd_strlen(repl);
}

int	rd_return_0(const char *s1, const char *s2, const int n)
{
	(void)s1;
	(void)s2;
	(void)n;
	return (0);
}

void	rd_auto_compl(t_readline *rdl)
{
	int				len = 0;
	char			**ret;
	t_auto_compl	*cmpl;

	rd_putstr_fd("\033[J", FDIN); // Erase display (cursor -> END)

	if (!rdl->line) { // if empty line
		ret = rd_list_files(".", NULL, 0, &rd_return_0);
		cmpl = NULL;
	}
	else {
		cmpl = rd_extract_word(rdl->line, rdl->cursor);
		if (!cmpl)
			return ;

		if (cmpl->n == -1) { // cursor not on word
			free(cmpl);
			return ;
		}
		ret = rd_list_files(".", cmpl->words[cmpl->n], cmpl->pos, &rd_compn);
	}

	while (ret && ret[len])
		len++;

	if (!len) { // nothing match
		rd_freeCompl(ret, cmpl);
		return ;
	}
	rd_putstr_fd("\033[s", FDIN); // Save cursor location
	if (len == 1)
		rd_change_line(cmpl, ret[0], rdl);
	if (len > 1)
		rd_print_files(ret);

	rd_freeCompl(ret, cmpl);
	rd_putstr_fd("\033[u", FDIN); // Restore cursor location
}