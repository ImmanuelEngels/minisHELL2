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

static size_t		ft_count_words_f(char const *s, bool (*f)(unsigned char))
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (f(*s))
			s++;
		if (*s)
			count++;
		while (*s && !f(*s))
			s++;
	}
	return (count);
}

static char const	*ft_strchr_if_f(char const *s, bool (*f)(unsigned char), bool b)
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

char	**ft_split_f(char const *s, bool (*f)(unsigned char))
{
	char		**arr;
	char const	*end;
	char		**temp;

	if (!s)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (ft_count_words_f(s, f) + 1));
	if (!arr)
		return (NULL);
	temp = arr;
	while (*s)
	{
		s = ft_strchr_if_f(s, f, 1);
		if (!*s)
			break ;
		end = ft_strchr_if_f(s, f, 0);
		*arr = ft_substr(s, 0, end - s);
		if (!*arr)
			return (ft_free_arrp(&temp));
		s = end;
		arr++;
	}
	*arr = NULL;
	return (temp);
}
