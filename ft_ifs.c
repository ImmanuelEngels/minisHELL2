#include "minishell.h"

bool	ft_ifs(unsigned char c)
{
	return (c == '\t' || c == '\n' || c == ' ');
}

void	ft_free_ifs(t_ifs *ifs)
{
	if (!ifs)
		return ;
	ft_dlstclear(&ifs->fields, free);
	free(ifs);
}

bool	ft_insert_after(t_dlist *at, const char *s, t_dlist **newn)
{
	t_dlist	*n;
	char	*dup;

	dup = ft_strdup(s);
	if (!dup)
		return (false);
	n = ft_dlstnew(dup);
	if (!n)
		return (free(dup), false);
	ft_dlstadd_after(at, n);
	if (newn)
		*newn = n;
	return (true);
}

bool	ft_replace_content(t_dlist *tok, char *newc)
{
	if (!tok || !newc)
		return (false);
	free(tok->content);
	tok->content = newc;
	return (true);
}

t_ifs	*ft_create_ifs(char *value)
{
	t_ifs	*ifs;
	size_t	len;
	bool	err;

	if (!value)
		return (NULL);
	ifs = malloc(sizeof(t_ifs));
	if (!ifs)
		return (NULL);
	len = ft_strlen(value);
	ifs->lead_sep = (len > 0 && ft_ifs((unsigned char)value[0]));
	ifs->trail_sep = (len > 0 && ft_ifs((unsigned char)value[len - 1]));
	ifs->fields = ft_dlist_split_f(value, ft_ifs, &err);
	if (err)
		return (free(ifs), NULL);
	return (ifs);
}
