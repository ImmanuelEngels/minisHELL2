#include "../libft.h"

int	ft_dlstsize(t_dlist *dlst)
{
	int		size;
	t_dlist	*p;

	size = 0;
	p = dlst;
	if (!dlst)
		return (0);
	while (p)
	{
		size++;
		p = p->next;
	}
	return (size);
}
