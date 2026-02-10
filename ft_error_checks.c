#include "minishell.h"

bool	ft_has_ambiguous_redirect(t_cmd **cmds)
{
	t_dlist	*rnode;
	t_redir	*r;
	size_t	i;

	if (!cmds)
		return (false);
	i = 0;
	while (cmds[i])
	{
		rnode = cmds[i]->redirs;
		while (rnode)
		{
			r = (t_redir *)rnode->content;
			if (!r || !r->tokens || !r->tokens->content || r->tokens->next)
				return (true);
			rnode = rnode->next;
		}
		i++;
	}
	return (false);
}

