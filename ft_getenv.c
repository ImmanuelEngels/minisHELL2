#include "minishell.h"

char	*ft_get_varname(char *str, char **end)
{
	char	*p;

	if (!str || !end || !*end)
		return (ft_strdup(""));
	p = *end;
	if (!*p || (!ft_isalpha((unsigned char)*p) && *p != '_'))
	{
		if (*p == '?')
		{
			(*end)++;
			return (ft_strdup("?"));
		}
		return (ft_strdup(""));
	}
	while (**end && (ft_isalnum((unsigned char)**end) || **end == '_'))
		(*end)++;
	return (ft_substr(str, (size_t)(p - str), (size_t)(*end - p)));
}

char	*ft_getenv(char *name, char **env)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(name);
	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], name, len) && env[i][len] == '=')
			return (ft_strdup(env[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}
