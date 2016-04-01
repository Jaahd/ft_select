#include "ft_select.h"

int				down_arrow()
{
	t_cduo				*tmp;
	int					result;
	int					a;
	int					b;
	int					pos;
	int					first_disp;

	first_disp = 0;
	tmp = get_stuff()->lst_param;
	while (tmp->cursor == FALSE)
	{
		if (tmp->first_disp == TRUE)
			first_disp = tmp->no_elt;
		tmp = tmp->next;
	}
	tmp->cursor = FALSE;
	tmp->next->cursor = TRUE;
	a = get_stuff()->col_size;
	b = fct_size()->ws_col / a;
	result = fct_size()->ws_row * b;
	if (tmp->next->no_elt == (result + first_disp) && tmp->next->first == FALSE)
	{
		tmp = get_stuff()->lst_param;
		while(tmp->first_disp != TRUE)
			tmp = tmp->next;
		tmp->first_disp = FALSE;
		pos = tmp->no_elt;
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
	if (tmp->first == FALSE && tmp->first_disp == TRUE && (fct_size()->ws_row * (fct_size()->ws_col / get_stuff()->col_size)) < get_stuff()->nb_elt)
	{
		pos = tmp->no_elt;
		printf("toto pouet\n");
		tmp->first_disp = FALSE;
		printf("-------------------------------------------no elt (%d) *** {%d} *** (%d) *******************************\n", tmp->no_elt, fct_size()->ws_row, pos - fct_size()->ws_row);
		tmp = get_stuff()->lst_param;
		next_pos = pos - fct_size()->ws_row < 1 ? 1 : pos - fct_size()->ws_row;
		while (tmp->no_elt != next_pos)
			tmp = tmp->next;
		tmp->first_disp = TRUE;
	}
	else if (tmp->first_disp == TRUE && tmp->first == TRUE && displayed_col < get_stuff()->nb_col)
	{
		if (tmp->first == TRUE)
			printf("*********************************************************((%d))*******************\n", tmp->no_elt);
		tmp->first_disp = FALSE;
		while (tmp->no_elt != ((get_stuff()->nb_col - displayed_col) * fct_size()->ws_row))
			tmp = tmp->next;
		tmp->first_disp = TRUE;
	}
	return (0);
}

