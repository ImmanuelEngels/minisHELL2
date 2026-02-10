#include "minishell.h"

#include "minishell.h"

static bool	ft_conv_token_argv_one(t_cmd *cmd)
{
	t_dlist	*node;
	size_t	n;
	size_t	i;

	if (!cmd)
		return (false);
	n = (size_t)ft_dlstsize(cmd->tokens);
	cmd->argv = ft_calloc(n + 1, sizeof(char *));
	if (!cmd->argv)
		return (false);
	node = cmd->tokens;
	i = 0;
	while (node)
	{
		cmd->argv[i++] = (char *)node->content;
		node = node->next;
	}
	cmd->argv[i] = NULL;
	cmd->cmd = cmd->argv[0];
	return (true);
}

bool	ft_conv_token_argv(t_data *data)
{
	size_t	i;

	if (!data || !data->cmds)
		return (false);
	i = 0;
	while (data->cmds[i])
	{
		if (!ft_conv_token_argv_one(data->cmds[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	ft_conv_token_target(t_redir *redir)
{
	if (!redir)
		return (false);
	if (!redir->tokens || redir->tokens->next || !redir->tokens->content)
		return (false);
	redir->target = (char *)redir->tokens->content;
	return (true);
}

bool	ft_direct_token_pointers(t_data *data)
{
	size_t	i;
	t_dlist	*rnode;
	t_redir	*r;

	if (!data || !data->cmds)
		return (false);
	if (!ft_conv_token_argv(data))
		return (false);

	i = 0;
	while (data->cmds[i])
	{
		rnode = data->cmds[i]->redirs;
		while (rnode)
		{
			r = (t_redir *)rnode->content;
			if (!ft_conv_token_target(r))
			{
				data->malloc_err = true;
				return (false);
			}
			rnode = rnode->next;
		}
		i++;
	}
	return (true);
}

