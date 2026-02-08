#include "minishell.h"

bool	ft_match_found(char *c)
{
	size_t	i;
	char	q;

	if (!c || !*c)
		return (false);
	q = *c;
	i = 0;
	while (c[++i])
		if (c[i] == q)
			return (true);
	return (false);
}
