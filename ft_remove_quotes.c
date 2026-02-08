#include "minishell.h"

static bool	ft_remove_char_at_str(char **s, size_t pos)
{
	char	*old;
	char	*newstr;
	size_t	len;

	if (!s || !*s)
		return (false);
	old = *s;
	len = ft_strlen(old);
	if (pos >= len)
		return (false);
	newstr = malloc(len);
	if (!newstr)
		return (false);
	ft_memcpy(newstr, old, pos);
	ft_memcpy(newstr + pos, old + pos + 1, len - pos);
	free(old);
	*s = newstr;
	return (true);
}

bool	ft_remove_quotes(char *q, t_expand *e, t_dlist **tokens, char c)
{
	size_t	open_i;
	size_t	close_i;

	if (!q || !e || !tokens || !*tokens || !(*tokens)->content || !e->str
		|| !e->start)
		return (false);
	if (c != '\'' && c != '\"')
		return (true);
	if (*e->start != c)
		return (false);
	open_i = e->first_q;
	close_i = (size_t)(e->start - (char *)(*tokens)->content);
	if (open_i >= close_i)
		return (false);
	if (!ft_remove_char_at_str((char **)&(*tokens)->content, close_i))
		return (false);
	if (!ft_remove_char_at_str((char **)&(*tokens)->content, open_i))
		return (false);
	e->str = (char *)(*tokens)->content;
	e->start = e->str + (close_i - 1);
	*q = 0;
	return (true);
}
