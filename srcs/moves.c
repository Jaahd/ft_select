#include "ft_select.h"

int				down_arrow()
{
	t_cduo				*tmp;

	tmp = get_stuff()->lst_param;
	while (tmp->cursor == FALSE)
		tmp = tmp->next;
	tmp->cursor = FALSE;
	tmp->next->cursor = TRUE;
	return (0);
}

int				up_arrow()
{
	t_cduo				*tmp;

	tmp = get_stuff()->lst_param;
	while (tmp->cursor == FALSE)
		tmp = tmp->prev;
	tmp->cursor = FALSE;
	tmp->prev->cursor = TRUE;
	return (0);
}

