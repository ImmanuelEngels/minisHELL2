#include "minishell.h"

char	ft_is_quoted(char *c, char *q, bool init)
{
	if (init)
		*q = 0;
	else
	{
		if (*q && *q == *c)
			*q = 0;
		else if (!*q && (*c == '\'' || *c == '\"') && ft_match_found(c))
			*q = *c;
	}
	return (*q);
}

static bool	ft_expand_helper(t_expand *e, char *q, t_data *data,
		t_dlist **tokens)
{
	if (!*q && ft_is_quoted(e->start, q, false))
		e->first_q = (size_t)(e->start - e->str);
	else if (*q && !ft_is_quoted(e->start, q, false))
	{
		if (!ft_remove_quotes(q, e, tokens, *e->start))
			return (false);
	}
	else if (*q == 0 && *e->start == '$')
	{
		if (!ft_expand_nq(e, data, tokens))
			return (false);
	}
	else if (*q == '\"' && *e->start == '$')
	{
		if (!ft_expand_dq(e, data, tokens))
			return (false);
	}
	else
		e->start++;
	return (true);
}

static bool	ft_expand_cmd(t_data *data, t_dlist *tokens)
{
	t_expand	e;
	char		q;

	while (tokens != NULL)
	{
		e.str = (char *)tokens->content;
		e.start = e.str;
		ft_is_quoted(0, &q, true);
		while (*e.start)
		{
			if (!ft_expand_helper(&e, &q, data, &tokens))
				return (false);
		}
		tokens = tokens->next;
	}
	return (true);
}

static bool	ft_expand_redir(t_data *data, t_dlist *tokens, enum e_redir type)
{
	t_expand	e;
	char		q;

	if (type == R_HEREDOC)
		return (true);
	e.str = (char *)tokens->content;
	e.start = e.str;
	ft_is_quoted(0, &q, true);
	while (*e.start)
	{
		if (!ft_expand_helper(&e, &q, data, &tokens))
			return (false);
	}
	return (true);
}

bool	ft_expander(t_data *data)
{
	size_t	i;
	t_redir	*rdir;
	t_dlist	*rdir_note;

	i = 0;
	while (i < data->n_cmds)
	{
		rdir_note = (t_dlist *)data->cmds[i]->redirs;
		if (!ft_expand_cmd(data, data->cmds[i]->tokens))
			return (false);
		write(1, "\nATLAST\n", 8);
		while (rdir_note)
		{
			rdir = (t_redir *)rdir_note->content;
			if (!ft_expand_redir(data, rdir->tokens, rdir->type))
				return (false);
			rdir_note = rdir_note->next;
		}
		i++;
	}
	return (true);
}
