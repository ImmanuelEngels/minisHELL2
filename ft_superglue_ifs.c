#include "minishell.h"

static bool	ft_glue_prefix_first(t_dlist *tok, t_ifs *ifs, char *pre,
		t_dlist **last)
{
	char	*tmp;
	t_dlist	*first;

	if (!ft_replace_content(tok, ft_strdup(pre)))
		return (false);
	*last = tok;
	first = ifs->fields;
	if (!first || ifs->lead_sep)
		return (true);
	tmp = ft_strjoin((char *)(*last)->content, (char *)first->content);
	if (!tmp)
		return (false);
	free((*last)->content);
	(*last)->content = tmp;
	ifs->fields = first->next;
	free(first->content);
	free(first);
	return (true);
}

static bool	ft_glue_suffix_last(t_dlist **tok, char *suf, char **stop,
		bool trail_sep)
{
	char	*tmp;

	if (!suf || !*suf)
		return (true);
	if (!trail_sep)
	{
		tmp = ft_strjoin((char *)(*tok)->content, suf);
		if (!tmp)
			return (false);
		free((*tok)->content);
		(*tok)->content = tmp;
		*stop = (char *)(*tok)->content + (ft_strlen((char *)(*tok)->content)
				- ft_strlen(suf));
		return (true);
	}
	if (!ft_insert_after(*tok, suf, tok))
		return (false);
	*stop = (char *)(*tok)->content;
	return (true);
}

static bool	ft_apply_glue_ifs(t_dlist **tok, t_dlist *fields)
{
	char	*dup;

	if (fields && !*(char *)(*tok)->content)
	{
		dup = ft_strdup((char *)fields->content);
		if (!dup)
			return (false);
		free((*tok)->content);
		(*tok)->content = dup;
		fields = fields->next;
	}
	while (fields)
	{
		if (!ft_insert_after(*tok, (char *)fields->content, tok))
			return (false);
		fields = fields->next;
	}
	return (true);
}


bool	ft_superglue_ifs(t_dlist **tok, char *value, size_t start, char **stop)
{
	t_ifs	*ifs;
	char	*pre;
	char	*suf;

	if (!tok || !*tok || !value || !stop || !*stop)
		return (free(value), false);
	ifs = ft_create_ifs(value);
	if (!ifs)
		return (free(value), false);
	pre = ft_substr((char *)(*tok)->content, 0, start);
	suf = ft_strdup(*stop);
	if (!pre || !suf || !ft_glue_prefix_first(*tok, ifs, pre, tok)
		|| !ft_apply_glue_ifs(tok, ifs->fields) || !ft_glue_suffix_last(tok,
			suf, stop, ifs->trail_sep))
		return (free(pre), free(suf), ft_free_ifs(ifs), free(value), false);
	if (!**stop)
		*stop = (char *)(*tok)->content + ft_strlen((char *)(*tok)->content);
	return (free(pre), free(suf), ft_free_ifs(ifs), free(value), true);
}

bool	ft_expand_nq(t_expand *e, t_data *data, t_dlist **tokens)
{
	e->stop = e->start + 1;
	e->name = ft_get_varname(e->str, &e->stop);
	if (!e->name)
		return (false);
	e->val = ft_getenv(e->name, data->env);
	if (!e->val)
		return (free(e->name), false);
	if (!ft_superglue_ifs(tokens, e->val, (size_t)(e->start - e->str),
			&e->stop))
		return (free(e->name), false);
	e->start = e->stop;
	e->str = (char *)(*tokens)->content;
	return (free(e->name), true);
}
