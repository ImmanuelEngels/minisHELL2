#include "minishell.h"

t_redir	*ft_get_redir(t_dlist *node)
{
	if (!node || !node->content)
		return (NULL);
	return ((t_redir *)node->content);
}

t_redir	*ft_redir_new(void)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	ft_bzero(redir, sizeof(t_redir));
	redir->type = R_MAX;
	return (redir);
}

static bool	ft_redir_unlink_pair(t_dlist **it, t_dlist **tokens, t_dlist **op,
		t_dlist **target)
{
	*op = *it;
	*target = (*op)->next;
	if (!*target || ft_is_operator((char *)(*target)->content))
		return (false);
	*it = (*target)->next;
	ft_dlst_unwrap(tokens, *op);
	ft_dlst_unwrap(tokens, *target);
	return (true);
}

static bool	ft_redir_attach(t_cmd *cmd, t_dlist *op, t_dlist *target)
{
	t_redir	*redir;
	t_dlist	*rnode;

	redir = ft_redir_new();
	if (!redir)
		return (ft_dlstdelone(op, free), ft_dlstdelone(target, free), false);
	redir->type = ft_get_redir_type((char *)op->content);
	if (redir->type == R_MAX)
		return (ft_free_redirs(&cmd->redirs), ft_dlstdelone(op, free),
			ft_dlstdelone(target, free), false);
	redir->quoted = (ft_strchr((char *)target->content, '\'')
				|| ft_strchr((char *)target->content, '"'));
	ft_dlstdelone(op, free);
	ft_dlstadd_back(&redir->tokens, target);
	rnode = ft_dlstnew(redir);
	if (!rnode)
		return (ft_free_redirs(&cmd->redirs), false);
	ft_dlstadd_back(&cmd->redirs, rnode);
	return (true);
}

bool	ft_redir_init(t_cmd *cmd, t_dlist **tokens)
{
	t_dlist	*it;
	t_dlist	*op;
	t_dlist	*target;

	if (!cmd || !tokens)
		return (false);
	it = *tokens;
	while (it)
	{
		if (!ft_is_operator((char *)it->content))
		{
			it = it->next;
			continue ;
		}
		if (!ft_redir_unlink_pair(&it, tokens, &op, &target))
			return (false);
		if (!ft_redir_attach(cmd, op, target))
			return (false);
	}
	return (true);
}
