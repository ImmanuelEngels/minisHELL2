/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imengels <imengels@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:32:44 by imengels          #+#    #+#             */
/*   Updated: 2025/05/07 16:32:46 by imengels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char const	*ft_strchr_if_f(char const *s, bool (*f)(unsigned char),
		bool b)
{
	while (*s)
	{
		if (f(*s) && !b)
			return (s);
		else if (!f(*s) && b)
			return (s);
		s++;
	}
	return (s);
}

t_dlist	*ft_dlist_split_f(const char *s, bool (*f)(unsigned char), bool *err)
{
	t_dlist	*list;
	t_dlist	*node;
	char	*field;

	*err = true;
	if (!s || !f)
		return (NULL);
	list = NULL;
	while (*s)
	{
		s = ft_strchr_if_f(s, f, true);
		if (!*s)
			break ;
		field = ft_substr(s, 0, (size_t)(ft_strchr_if_f(s, f, false) - s));
		if (!field)
			return (ft_dlstclear(&list, free), NULL);
		node = ft_dlstnew(field);
		if (!node)
			return (free(field), ft_dlstclear(&list, free), NULL);
		ft_dlstadd_back(&list, node);
		s = ft_strchr_if_f(s, f, false);
	}
	*err = false;
	return (list);
}
