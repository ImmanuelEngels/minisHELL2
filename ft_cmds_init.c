#include "minishell.h"

size_t	ft_count_cmds(t_dlist *lst)
{
	size_t	count;

	count = 1;
	while (lst)
	{
		if (((char *)lst->content)[0] == '|')
			count++;
		lst = lst->next;
	}
	return (count);
}

t_cmd	*ft_cmd_new(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	ft_bzero(cmd, sizeof(t_cmd));
	return (cmd);
}

bool	ft_cmds_valid(t_data *data)
{
	t_dlist	*temp;

	if (!data || data->pipeline)
		if (((char *)data->pipeline->content)[0] == '|')
			return (false);
	if (ft_is_operator((char *)ft_dlstlast(data->pipeline)->content))
		return (false);
	temp = data->pipeline;
	while (temp->next)
	{
		if (ft_is_operator((char *)temp->content)
			&& ft_is_operator((char *)temp->next->content))
			return (false);
		temp = temp->next;
	}
	return (true);
}

bool	ft_cmds_init(t_data *data)
{
	t_dlist	*node;
	t_dlist	*next;
	size_t	i;
	char	*tok;

	if (!data || !data->pipeline || !data->cmds)
		return (false);
	i = 0;
	node = data->pipeline;
	while (node)
	{
		next = node->next;
		tok = (char *)node->content;
		ft_dlst_unwrap(&data->pipeline, node);
		if (tok[0] == '|' && tok[1] == '\0')
		{
			ft_dlstdelone(node, free);
			if (++i >= data->n_cmds)
				return (false);
		}
		else
			ft_dlstadd_back(&data->cmds[i]->tokens, node);
		node = next;
	}
	return (true);
}

bool	ft_cmds_create(t_data *data)
{
	int	i;

	if (!data || !data->pipeline || !ft_cmds_valid(data))
		return (false);
	data->n_cmds = ft_count_cmds(data->pipeline);
	data->cmds = ft_calloc((data->n_cmds + 1), sizeof(t_cmd *));
	if (!data->cmds)
		return (false);
	i = -1;
	while ((size_t)(++i) < data->n_cmds)
	{
		data->cmds[i] = ft_cmd_new();
		if (!data->cmds[i])
			return (ft_free_cmds(data), false);
	}
	if (!ft_cmds_init(data))
		return (ft_free_cmds(data), false);
	i = -1;
	while ((size_t)(++i) < data->n_cmds)
	{
		if (!ft_redir_init(data->cmds[i], &data->cmds[i]->tokens))
			return (ft_free_cmds(data), false);
	}
	return (true);
}
