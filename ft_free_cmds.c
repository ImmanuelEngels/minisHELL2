#include "minishell.h"

static void	ft_free_token_content(void *content)
{
	if (!content)
		return ;
	ft_free((void **)&content);
}

static void	ft_free_redir_content(void *content)
{
	t_redir	*redir;

	if (!content)
		return ;
	redir = (t_redir *)content;
	ft_free((void **)&redir->target);
	if (redir->tokens)
		ft_dlstclear(&redir->tokens, ft_free_token_content);
	ft_free((void **)&redir);
}

void	ft_free_redirs(t_dlist **redirs)
{
	if (!redirs || !*redirs)
		return ;
	ft_dlstclear(redirs, ft_free_redir_content);
}

static void	ft_free_cmd_content(t_cmd **cmd)
{
	if (!cmd || !*cmd)
		return ;
	if ((*cmd)->argv)
		ft_free_arrp(&(*cmd)->argv);
	if ((*cmd)->redirs)
		ft_free_redirs(&(*cmd)->redirs);
	if ((*cmd)->tokens)
		ft_dlstclear(&(*cmd)->tokens, ft_free_token_content);
	ft_close_if(&(*cmd)->fd_in);
	ft_close_if(&(*cmd)->fd_out);
	ft_close_if(&(*cmd)->pipe_in[0]);
	ft_close_if(&(*cmd)->pipe_in[1]);
	ft_close_if(&(*cmd)->pipe_out[0]);
	ft_close_if(&(*cmd)->pipe_out[1]);
	ft_free((void **)cmd);
}

void	ft_free_cmds(t_data *data)
{
	size_t	i;

	if (!data || !data->cmds)
		return ;
	i = 0;
	while (data->cmds[i])
	{
		ft_free_cmd_content(&data->cmds[i]);
		i++;
	}
	ft_free((void **)&data->cmds);
}

