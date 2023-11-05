#include "readline.h"

/*------------- proto ---------------*/
void		rd_write_prompt(char *prompt, int ret);
void		rd_files_manager(void);
t_readline	rd_readline_init(char *prompt);
char		rd_extract_char(void);
void		rd_do_delete(t_readline *rdl);
void		rd_do_backspace(t_readline *rdl);
void		rd_move_cursor(t_readline *rdl);
void		rd_treat_char(char c, t_readline *rdl);

/* ================================= */
void	rd_write_prompt(char *prompt, int ret)
{
	if (!ret)
		rd_putstr_fd("\x1B[1m\x1B[32m➜  \x1B[36m", FDOUT);
	else
		rd_putstr_fd("\x1B[1m\x1B[31m➜  \x1B[36m", FDOUT);
	if (prompt)
		rd_putstr_fd(prompt, FDOUT);
	rd_putstr_fd("\x1B[0m ", FDOUT);
}

void	rd_files_manager(void)
{
	int			fd;
	struct stat	st = {0};

	if (stat(".rdlrc", &st) == -1)
		mkdir(".rdlrc", 0755);
	if (access(".rdlrc/.history", F_OK) == -1)
	{
		fd = open(".rdlrc/.history", O_RDWR | O_CREAT | O_APPEND, 0644);
		close(fd);
	}
}

void	add_history(char *line)
{
	int	fd;

	rd_files_manager();
	fd = open(".rdlrc/.history", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return ;
	rd_putstr_fd(line, fd);
	rd_putstr_fd("\n", fd);
	close(fd);
}

void	clear_history(void)
{
	int	fd;

	fd = open(".rdlrc/.history", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	close(fd);
}

t_readline	rd_readline_init(char *prompt)
{
	t_readline	ret;

	if (!prompt)
		ret.begin_pos = 3;
	else
		ret.begin_pos = rd_strlen(prompt) + 3;
	ret.cursor = 0;
	ret.line = NULL;
	ret.flx = 0;
	ret.flux = NULL;
	return (ret);
}

char	rd_extract_char(void)
{
	char	c;
	struct termios	oldt;
	struct termios	newt;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;

	newt.c_lflag &= ~(ICANON | ECHO);

	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	c = getchar();
	if (c == '\033')
	{
		getchar(); // skip the '['
		switch (getchar())
		{
			case 'A':
				c = -1;
				break;
			case 'B':
				c = -2;
				break;
			case 'C':
				c = -3;
				break;
			case 'D':
				c = -4;
				break;
			case '3':
				if (getchar() == '~')
					c = -5;
				break ;
		}
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return (c);
}

void	rd_do_delete(t_readline *rdl)
{
	if (rd_strlen(rdl->line) <= rdl->cursor)
		return ;
	rdl->line = rd_remove_one(rdl->line, rdl->cursor + 1);
	rd_close_flux(rdl);
}

void	rd_do_backspace(t_readline *rdl)
{
	rdl->line = rd_remove_one(rdl->line, rdl->cursor);
	if (rdl->cursor > 0)
		rdl->cursor--;
	rd_close_flux(rdl);
}

void	rd_move_cursor(t_readline *rdl)
{
	int	move;

	move = rd_strlen(rdl->line) - rdl->cursor;
	for (int i = 0; i < move; i++)
		write(1, "\033[1D", 4);
}

void	rd_close_flux(t_readline *rdl)
{
		if (rdl->flx)
			fclose(rdl->flux);
		rdl->flux = NULL;
		rdl->flx = 0;
}

void	rd_treat_char(char c, t_readline *rdl)
{
	if (c == -1) // up
		rd_find_in_index(rdl, 1);
	else if (c == -2) // down
		rd_find_in_index(rdl, 0);
	else if (c == -3 && (rdl->cursor < rd_strlen(rdl->line))) // right
		rdl->cursor++;
	else if (c == -4 && rdl->cursor > 0) // left
		rdl->cursor--;
	else if (c == -5)
		rd_do_delete(rdl);
	else if (c == 127)
		rd_do_backspace(rdl);
	else if (c == '\t')
		rd_auto_compl(rdl);
	else if (c > 0)
	{
		rdl->line = rd_cat_line(rdl->line, rdl->cursor++, c);
		rd_close_flux(rdl);
	}

	printf("\033[%dG", rdl->begin_pos + 2); // set cursor to begin of line
	fflush(stdout);
	rd_putstr_fd("\033[K", FDIN); //  Erase line (cursor -> END line)

	rd_putstr_fd(rdl->line, FDIN);
	rd_move_cursor(rdl);
}

char	*readline(char *prompt, int ret)
{
	char		c;
	t_readline	rdl;

	rd_files_manager();
	rdl = rd_readline_init(prompt);
	rd_write_prompt(prompt, ret);

	while ((c = rd_extract_char()) && c != '\n')
		rd_treat_char(c, &rdl);
	rd_close_flux(&rdl);

	for (;rdl.cursor < rd_strlen(rdl.line); rdl.cursor++) // set cursor to end of line
		rd_putstr_fd("\033[1C", FDIN);
	rd_putstr_fd("\033[J", 1); // Erase display (cursor -> END)

	write(1, "\n", 1);
	return (rdl.line);
}
