#include "minishell.h"

/* ---------- small enum printers ---------- */

static const char	*ft_redir_type_str(enum e_redir t)
{
	if (t == R_IN)
		return ("R_IN");
	if (t == R_OUT)
		return ("R_OUT");
	if (t == R_HEREDOC)
		return ("R_HEREDOC");
	if (t == R_APPEND)
		return ("R_APPEND");
	return ("R_MAX/UNKNOWN");
}

/* ---------- generic list/array printers ---------- */

static void	ft_print_str_dlist(const char *label, t_dlist *lst)
{
	size_t	i;

	printf("%s: [", label);
	i = 0;
	while (lst)
	{
		printf("\"%s\"", (char *)lst->content);
		if (lst->next)
			printf(", ");
		lst = lst->next;
		i++;
	}
	printf("] (n=%zu)\n", i);
}

static void	ft_print_str_arr(const char *label, char **arr)
{
	size_t	i;

	printf("%s: [", label);
	if (!arr)
	{
		printf("NULL]\n");
		return ;
	}
	i = 0;
	while (arr[i])
	{
		printf("\"%s\"", arr[i]);
		if (arr[i + 1])
			printf(", ");
		i++;
	}
	printf("] (n=%zu)\n", i);
}

/* ---------- struct printers ---------- */

void	ft_print_ifs(t_ifs *ifs)
{
	if (!ifs)
	{
		printf("t_ifs: NULL\n");
		return ;
	}
	printf("t_ifs {\n");
	printf("  lead_sep: %s\n", ifs->lead_sep ? "true" : "false");
	printf("  trail_sep: %s\n", ifs->trail_sep ? "true" : "false");
	printf("  ");
	ft_print_str_dlist("fields", ifs->fields);
	printf("}\n");
}

void	ft_print_redir(t_redir *r)
{
	t_dlist	*tok;

	if (!r)
	{
		printf("t_redir: NULL\n");
		return ;
	}
	printf("t_redir {\n");
	printf("  type: %s\n", ft_redir_type_str(r->type));
	printf("  target: %s\n", r->target ? r->target : "(null)");
	printf("  quoted: %s\n", r->quoted ? "true" : "false");
	printf("  tokens: [");
	tok = r->tokens;
	while (tok)
	{
		printf("\"%s\"", (char *)tok->content);
		if (tok->next)
			printf(", ");
		tok = tok->next;
	}
	printf("]\n");
	printf("}\n");
}

void	ft_print_cmd(t_cmd *cmd, size_t idx)
{
	t_dlist	*rnode;
	size_t	ridx;

	if (!cmd)
	{
		printf("cmd[%zu]: NULL\n", idx);
		return ;
	}
	printf("cmd[%zu] {\n", idx);
	printf("  cmd: %s\n", cmd->cmd ? cmd->cmd : "(null)");
	printf("  ");
	ft_print_str_arr("argv", cmd->argv);
	printf("  ");
	ft_print_str_dlist("tokens", cmd->tokens);
	printf("  redirs:\n");
	rnode = cmd->redirs;
	ridx = 0;
	while (rnode)
	{
		printf("    - redir[%zu]:\n", ridx);
		ft_print_redir((t_redir *)rnode->content);
		rnode = rnode->next;
		ridx++;
	}
	if (!cmd->redirs)
		printf("    (none)\n");
	printf("}\n");
}

void	ft_print_data(t_data *data)
{
	size_t	i;

	if (!data)
	{
		printf("t_data: NULL\n");
		return ;
	}
	printf("t_data {\n");
	printf("  line: %s\n", data->line ? data->line : "(null)");
	printf("  ");
	ft_print_str_dlist("pipeline", data->pipeline);
	printf("  n_cmds: %zu\n", data->n_cmds);
	printf("  cmds:\n");
	if (!data->cmds)
		printf("    (null)\n");
	else
	{
		i = 0;
		while (data->cmds[i])
		{
			ft_print_cmd(data->cmds[i], i);
			i++;
		}
		if (i == 0)
			printf("    (empty)\n");
	}
	printf("}\n");
}
