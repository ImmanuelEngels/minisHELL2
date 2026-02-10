#include "minishell.h"

int	ft_cleanup_runtime(t_data **data)
{
	if (!data || !*data)
		return (1);

	ft_free((void **)&(*data)->line);
	(*data)->pipeline = NULL;

	if ((*data)->cmds)
		ft_free_cmds(*data);
	if ((*data)->quit || (*data)->malloc_err)
		return (1);
	return (0);
}

int	ft_cleanup_quit(t_data **data, bool malloc_err)
{
	ft_free_data(data);
	if (malloc_err)
		return (write(2, "minishell> SYSCALL ERROR: Malloc. Exiting\n", 42), 1);
	return (g_exit_status);
}

t_data	*ft_init_data(int ac, char **av, char **env)
{
	t_data	*data;

	(void)av;
	(void)ac;
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	ft_bzero((void *)data, sizeof(t_data));
	data->env = ft_arrdup(env);
	if (!data->env)
		return (free(data), NULL);
	return (data);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	t_dlist	*tmp;

	data = ft_init_data(ac, av, env);
	if (!data)
		return (ft_cleanup_quit(NULL, true));
	data->line = readline("minishell>");
	if (!data->line)
		return (free(data), 1);
	if (!ft_tokenize(data))
	{
		tmp = data->pipeline;
		for (; tmp; tmp = tmp->next)
			printf("LINEEEE[%s]\n", (char *)tmp->content);
	}
	ft_cmds_create(data);
	if (!ft_expander(data))
		return 1;
	if (!ft_direct_token_pointers(data))
		return (ft_cleanup_quit(&data, data->malloc_err));
	ft_print_data(data);
	return (ft_cleanup_quit(&data, data->malloc_err));
}
