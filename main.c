#include "minishell.h"

int	ft_cleanup(t_data *data, bool malloc_err)
{
	(void)data;
	if (malloc_err)
		write(2, "minishell> SYSCALL ERROR: Malloc. Exiting\n", 42);
	//	if (data)
	//		ft_cleanup(data);
	return (1);
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
		return (ft_cleanup(NULL, true));
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
	ft_print_data(data);
	//	ft_dlstclear(&data->pipeline, free);
	free(data->line);
	free(data);
	return (0);
}
