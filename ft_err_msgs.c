#include "minishell.h"

// TODO:	some idea for err messages without static const globals . File needs work

int	ft_error_messages(enum e_err error, char *str)
{
	static const char	*msg[ERR_MAX] = {"minishell: ambiguous redirect ",
			"minishell: syntax error", "minishell: No such file or directory "};

	ft_putstr_fd((char *)msg[error], 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

void	ft_err_with_arg(const char *arg, const char *suffix)
{
	write(2, "minishell: ", 11);
	if (arg)
		write(2, arg, ft_strlen(arg));
	if (suffix)
		write(2, suffix, ft_strlen(suffix));
	write(2, "\n", 1);
}

void	ft_perror_arg(const char *arg)
{
	write(2, "minishell: ", 11);
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
}
