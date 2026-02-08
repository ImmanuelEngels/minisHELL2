#include "minishell.h"

void	ft_free_redirs(t_redir *redirs)
{
	if (!redirs)
		return ;
	if (redirs->target)
		free(redirs->target);
	if (redirs->tokens)
		ft_dlstclear(&redirs->tokens, free);
	free(redirs);
}

void	ft_free_cmds(t_cmd **cmds)
{
	size_t	i;

	i = 0;
	if (!cmds)
		return ;
	while (cmds[i])
	{
		if (cmds[i]->tokens)
			ft_dlstclear(&cmds[i]->tokens, free);
		if (cmds[i]->redirs)
			ft_dlstclear(&cmds[i]->redirs, (void (*)(void *))ft_free_redirs);
		if (cmds[i]->argv)
			ft_free_arr(cmds[i]->argv);
		free(cmds[i]);
		i++;
	}
	free(cmds);
}
