#include "ft_select.h"
#include "libft.h"

int				down_arrow(int i)
{
	t_cduo				*tmp;
	int					result;
	int					pos;
	int					displayed_col;

	pos = 0;
	displayed_col = fct_size()->ws_col / get_stuff()->col_size;
	tmp = get_stuff()->lst_param;
	while (tmp->cursor == FALSE)
	{
		if (tmp->first_disp == TRUE)
			pos = tmp->no_elt;
		tmp = tmp->next;
	}
	if (i == 1)
		tmp->select = tmp->select == TRUE ? FALSE : TRUE;
	tmp->cursor = FALSE;
	tmp->next->cursor = TRUE;
	result = fct_size()->ws_row * displayed_col;
	if (tmp->next->no_elt >= (result + pos) && tmp->next->first == FALSE)
	{
		tmp = get_stuff()->lst_param;
		while(tmp->first_disp != TRUE)
			tmp = tmp->next;
		pos = tmp->no_elt;
		tmp->first_disp = FALSE;
		while (tmp->no_elt < (pos + fct_size()->ws_row))
			tmp = tmp->next;
		tmp->first_disp = TRUE;
	}
	else if (tmp->next->first == TRUE)
	{
		tmp->next->first_disp = TRUE;
		tmp = get_stuff()->lst_param;
		while (tmp->next->first_disp == TRUE)
			tmp = tmp->next;
		tmp->next->first_disp = FALSE;
	}
	return (0);
}

int				up_arrow()
{
	t_cduo				*tmp;
	int					pos;
	int					next_pos;
	int					displayed_col;

	pos = 0;
	next_pos = 0;
	displayed_col = fct_size()->ws_col / get_stuff()->col_size;
	tmp = get_stuff()->lst_param;
	while (tmp->cursor == FALSE)
		tmp = tmp->prev;
	tmp->cursor = FALSE;
	tmp->prev->cursor = TRUE;
	if (tmp->first == FALSE && tmp->first_disp == TRUE && displayed_col < get_stuff()->nb_col)
	{
		pos = tmp->no_elt;
		tmp->first_disp = FALSE;
		next_pos = pos - fct_size()->ws_row < 1 ? 1 : pos - fct_size()->ws_row;
		while (tmp->no_elt != next_pos)
			tmp = tmp->prev;
		tmp->first_disp = TRUE;
	}
	else if (tmp->first == TRUE && tmp->first_disp == TRUE && displayed_col < get_stuff()->nb_col)
	{
		tmp->first_disp = FALSE;
		while (tmp->no_elt != (((get_stuff()->nb_col - displayed_col) * fct_size()->ws_row) + 1))
			tmp = tmp->prev;
		tmp->first_disp = TRUE;
	}
	return (0);
}
