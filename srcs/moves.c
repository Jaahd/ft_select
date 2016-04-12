#include "ft_select.h"
#include "libft.h"

int				down_arrow(int space)
{
	t_cduo				*tmp;
	int					pos;
	int					displayed_col;
	int					i;

	i = 0;
	pos = 0;
	displayed_col = fct_size()->ws_col / get_stuff()->col_size;
	tmp = get_stuff()->lst_param;
	while (tmp->first_disp != TRUE)
		tmp = tmp->next;
	pos = tmp->no_elt;
	tmp = get_stuff()->lst_param;
	while (tmp->cursor != TRUE)
		tmp = tmp->next;
	if (space == 1)
		tmp->select = tmp->select == TRUE ? FALSE : TRUE;
	tmp->cursor = FALSE;
	tmp->next->cursor = TRUE;
	if (tmp->next->no_elt >= (fct_size()->ws_row * displayed_col + pos)
			&& tmp->next->first == FALSE)
	{
		tmp->name = "*********trololo*********";
		tmp = get_stuff()->lst_param;
		while(tmp->first_disp != TRUE)
			tmp = tmp->next;
		tmp->first_disp = FALSE;
		while (tmp->no_elt < (pos + fct_size()->ws_row))
			tmp = tmp->next;
		tmp->first_disp = TRUE;
	}
	else if (tmp->next->first == TRUE)
	{
		tmp->name = "toto_pouet_lolilol";
		tmp = get_stuff()->lst_param;
		while (tmp->first_disp != TRUE)
			tmp = tmp->next;
		tmp->first_disp = FALSE;
		tmp = get_stuff()->lst_param;
		tmp->first_disp = TRUE;
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
