#include <term.h> //pour tgetent
#include <termios.h>
#include "ft_select.h"
#include "libft.h"

int		putchr_max_len_fd(char *str)
{
//	if (DEBUG == 1)
		ft_putendl("putchr_max_len_fd");
	int				i;
	int				col_size;

	i = 0;
	col_size = get_stuff()->nb_elt > fct_size()->ws_row ? get_stuff()->col_size - 3 : fct_size()->ws_col - 3;
	while (i < (col_size))
	{
		ft_putchar_fd(str[i], get_stuff()->fd);
		i++;
	}
	ft_putstr_fd("...", get_stuff()->fd);
	return (0);
}

int				get_col_size()
{
	if (DEBUG == 1)
		ft_putendl("get_col_size");
	int				col_width;

	get_stuff()->nb_col = get_stuff()->nb_elt / fct_size()->ws_row;
	if (get_stuff()->nb_elt % fct_size()->ws_row != 0)
		get_stuff()->nb_col++;
	col_width = fct_size()->ws_col / get_stuff()->nb_col;
	if (col_width > 20 && col_width >  get_stuff()->max_len)
		col_width = get_stuff()->max_len;
	else if (col_width < 20 && get_stuff()->max_len > 20)
		col_width = 20;
	else if (col_width < 20 && get_stuff()->max_len < 20)
		col_width = get_stuff()->max_len;
	get_stuff()->col_size = col_width + 2;
//	printf("**********************nb elt {%d} // col_width {%d} // max_len {%d} // col_size {%d}**************************\n", get_stuff()->nb_elt, col_width, get_stuff()->max_len, get_stuff()->col_size);
	return (0);
}

int				manage_display(int j, int k, t_cduo *tmp)
{
	if (DEBUG == 1)
		ft_putendl("\t\tmanage_display");
	int				len;

	len = 0;
	tputs(tgoto(tgetstr("cm", NULL), (k * (get_stuff()->col_size)), j), 1, ft_putchr);
	if (fct_size()->ws_col - ((k * (get_stuff()->col_size)) + get_stuff()->col_size) >= 0)
	{
		if (tmp->select == TRUE)
			ft_putstr_fd("\033[7m", get_stuff()->fd);
		if (tmp->cursor == TRUE)
			ft_putstr_fd("\033[31;1;4m", get_stuff()->fd);
		len = ft_strlen(tmp->name);
		if ((get_stuff()->nb_elt <= fct_size()->ws_row && len > fct_size()->ws_col) || (len > get_stuff()->col_size && get_stuff()->nb_elt > fct_size()->ws_row))
			putchr_max_len_fd(tmp->name);
		else
			tputs(tmp->name, 1, ft_putchr);
		ft_putstr_fd("\033[0m", get_stuff()->fd);
	}
	else
	{
		tputs(tgoto(tgetstr("cm", NULL), fct_size()->ws_col - 5, fct_size()->ws_row), 1, ft_putchr);
		tputs("[...]", 1, ft_putchr);
	}
	return (0);
}

int				manage_win_size()
{
	if (DEBUG == 1)
		ft_putendl("manage_win_size");
	int				nb_min_row;

	nb_min_row = get_stuff()->nb_elt > 20 ? 20 : get_stuff()->nb_elt;
	if (fct_size()->ws_col - get_stuff()->col_size < 0)
		tputs("Window too small !", 1, ft_putchr);
	if (fct_size()->ws_row < nb_min_row || fct_size()->ws_col < get_stuff()->col_size)
	{
		clr_screen();
		tputs(tgoto(tgetstr("cm", NULL), (fct_size()->ws_col - 18) / 2, nb_min_row / 2), 1, ft_putchr);
		tputs("WINDOW TOO SMALL !!", 1, ft_putchr);
	}
	return (0);
}

int				manage_columns()
{
	if (DEBUG == 1)
		ft_putendl("\t\t\t\t\tmanage columns");
	t_cduo			*tmp;
	int				i;
	int				j;
	int				k;

	get_col_size();
	i = 0;
	k = 0;
	tmp = get_stuff()->lst_param;
	while (tmp->first_disp != TRUE)
		tmp = tmp->next;
	if (tmp->first == FALSE)
		i++;
	while ((i += tmp->first) < 2)
	{
		tmp->col_nb = k;
		j = 0;
		while(j < fct_size()->ws_row)
		{
			manage_win_size();
			manage_display(j, k, tmp);
			tmp = tmp->next;
			j++;
			if (tmp->first == TRUE)
				break ;
		}
		k++;
	}
	return (0);
}

int				print_return(char **ret)
{
	if (DEBUG == 1)
		ft_putendl("print return");
	int					i;

	i = 0;

	while (ret[i] != NULL)
	{
		ft_putstr_fd(ret[i], 1);
		ft_putchar_fd(' ', 1);
		i++;
	}
	free_tab(&ret);
	return (0);
}
