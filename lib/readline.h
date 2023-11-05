#ifndef __SHELL__H__
# define __SHELL__H__

/* ========== includes ========== */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdarg.h>
# include <termios.h>
# include <curses.h>
# include <dirent.h>

/* ========== define ========== */
# ifndef FDIN
#  define FDIN 0
# endif

# ifndef FDOUT
#  define FDOUT 1
# endif

# ifndef FDERR
#  define FDERR 2
# endif

/* ========== struct ========== */

typedef struct
{
	int		begin_pos;
	int		cursor;
	char	*line;
	int		flx;
	FILE	*flux;
}	t_readline;

typedef struct
{
	char	**words;
	int		pos;
	int		n;
	int		begin_word;
}	t_auto_compl;

/* ========== protos ========== */

/*---------- readline -------------*/
char			*readline(char *prompt, int ret);
void			add_history(char *line);
void			clear_history(void);
void			rd_close_flux(t_readline *rdl);

/*--------- read_history ----------*/
FILE			*rd_new_flux(char *name, char *mode);
char			*rd_line_from_stream(FILE *flux, int mode);
char			*rd_read_first_line(FILE *flux);
void			rd_find_in_index(t_readline *rdl, int mode);
int				rd_is_past_command(char *cmd);

/*------------ funct -------------*/
char			*rd_cat_line(char *line, int pos, char c);
char			*rd_remove_one(char *line, int pos);
char			**rd_tabPush(char **tab, char *to_add);
char			*rd_replace_words(char *line, int begin_word, char *repl);
void			rd_print_files(char **files);
void			rd_freeCompl(char **files, t_auto_compl *cmpl);

/*------------ utils -------------*/
int				rd_strlen(char *str);
void			rd_putstr_fd(char *str, int fd);
void			*rd_free_tab(char **tab);
int				rd_comp(const char *s1, const char *s2);
int				rd_compn(const char *s1, const char *s2, const int n); // [beta]
char			*rd_strdup(char *str);
char			*rd_substring(char *str, int start, int end);
char			*rd_read_one_line(int fd);

/*---------- auto_compl ----------*/ /*      [beta]      */
t_auto_compl	*rd_extract_word(char *line, int cursor);
char			**rd_list_files(char *curr_dir, char *line, int cursor, int (*cmp)());
char			**rd_splitLine(char const *s, int cursor, t_auto_compl *cmpl);
void			rd_auto_compl(t_readline *rdl);
int				rd_is_sep(char c);
void			rd_change_line(t_auto_compl *cmpl, char *repl, t_readline *rdl);

#endif
