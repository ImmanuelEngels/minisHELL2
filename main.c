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

bool	ft_prompt(t_data *data)
{
	while (data && !data->malloc_err && !data->quit)
	{
		data->line = readline("minishell>");
		if (!data->line)
		{
			/* Ctrl-D / EOF */
			data->quit = true;
			break;
		}
		if (!ft_cmds_create(data) || !ft_expander(data))
			return (false);
		if (!ft_direct_token_pointers(data))
			return (false);

		/* TODO: execution */

		if (ft_cleanup_runtime(&data))
			break;
	}
	return (data && !data->malloc_err);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	data = ft_init_data(ac, av, env);
	if (!data)
		return (ft_cleanup_quit(NULL, true));
	if (ft_prompt(data))
		return (ft_cleanup_quit(&data, data->malloc_err));
	ft_print_data(data);
	return (ft_cleanup_quit(&data, data->malloc_err));
}
