#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <unistd.h>

extern int			g_exit_status;

enum				e_redir
{
	R_IN,
	R_OUT,
	R_HEREDOC,
	R_APPEND,
	R_MAX
};

enum				e_err
{
	ERR_AMBIGOUS,
	ERR_SYNTAX,
	ERR_FILE,
	ERR_MAX
};

typedef struct s_expand
{
	char			*str;
	char			*name;
	char			*val;
	char			*start;
	char			*stop;
	size_t			first_q;
}					t_expand;

typedef struct s_ifs
{
	bool			lead_sep;
	bool			trail_sep;
	t_dlist			*fields;
}					t_ifs;

typedef struct s_redir
{
	enum e_redir	type;
	char			*target;
	bool			quoted;
	t_dlist			*tokens;
}					t_redir;

typedef struct s_cmd
{
	enum e_err		err;
	char			*cmd;
	char			**argv;
	t_dlist			*redirs;
	t_dlist			*tokens;
	pid_t			pid;
	int				fd_in;
	int				fd_out;
	int				pipe_in[2];
	int				pipe_out[2];
	bool			is_builtin;
	bool			needs_fork;
	int				exit_status;
}					t_cmd;

typedef struct s_data
{
	char			*line;
	t_dlist			*pipeline;
	t_cmd			**cmds;
	size_t			n_cmds;
	char			**env;
	bool			err[ERR_MAX];
	bool			abandon;
	bool			quit;
	bool			malloc_err;
}					t_data;

/*				*/
bool				ft_tokenize(t_data *data);

/*		ft_free.c			*/
void				ft_free_data(t_data **data);
void				ft_close_if(int *fd);
void				ft_free_cmds(t_data *data);
void				ft_free_redirs(t_dlist **redirs);

/*		ft_redir_init.c		*/
bool				ft_redir_init(t_cmd *cmd, t_dlist **tokens);
bool				ft_cmds_create(t_data *data);

/*		ft_is.c			*/
enum e_redir		ft_get_redir_type(char *str);
bool				ft_is_pipe(char *str);
bool				ft_is_redir(char *str);
bool				ft_is_operator(char *str);

/*		ft_cmds_init.c		*/
bool				ft_init_cmds(t_data *data);

/*		ft_ifs_and_superglue.c	*/

t_ifs				*ft_create_ifs(char *value);
bool				ft_insert_after(t_dlist *at, const char *s, t_dlist **newn);
void				ft_free_ifs(t_ifs *ifs);
bool				ft_replace_content(t_dlist *tok, char *newc);
bool				ft_expand_nq(t_expand *e, t_data *data, t_dlist **tokens);
bool				ft_superglue_ifs(t_dlist **tok, char *value, size_t start,
						char **stop);

/*		ft_remove_quotes.c	*/
bool				ft_remove_quotes(char *q, t_expand *e, t_dlist **tokens,
						char c);

/*		ft_getenv.c	*/
char				*ft_getenv(char *name, char **env);
char				*ft_get_varname(char *str, char **end);

/*		ft_expand_dq.c		*/
bool				ft_expand_dq(t_expand *e, t_data *data, t_dlist **tok);

/*		ft_match_found.c	*/
bool				ft_match_found(char *c);

/*		ft_expander.c	*/
bool				ft_expander(t_data *data);

/*		DEBUG			*/
void				ft_print_data(t_data *data);
/*		DEBUG			*/

#endif
