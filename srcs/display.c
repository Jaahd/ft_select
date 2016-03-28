#include <term.h> //pour tgetent
#include <termios.h>
#include "ft_select.h"
#include "libft.h"

int		putchr_max_len_fd(char *str)
{
	int				i;

	i = 0;
	while (i < (get_stuff()->col_size - 3))
	{
		ft_putchar_fd(str[i], get_stuff()->fd);
		i++;
	}
	ft_putstr_fd("...", get_stuff()->fd);
	return (0);
}

int				get_col_size()
{
	int				col_width;

	get_stuff()->nb_col = get_stuff()->nb_elt / fct_size()->ws_row;
	if (get_stuff()->nb_elt % fct_size()->ws_row != 0)
		get_stuff()->nb_col++;
	col_width = fct_size()->ws_col / get_stuff()->nb_col;
	col_width = col_width < 20 ? 20 : col_width;
	if (get_stuff()->max_len < col_width - 2)
		get_stuff()->col_size = get_stuff()->max_len;
	else if (get_stuff()->max_len >= col_width - 2)
		get_stuff()->col_size = col_width - 2;
	printf("**********************col_width {%d} // max_len {%d} // col_size {%d}**************************\n", col_width, get_stuff()->max_len, get_stuff()->col_size);
	return (0);
}

int				manage_display(int j, int k, t_cduo *tmp)
{
	int				displayed_col;

	displayed_col = 0;
	if (fct_size()->ws_col - get_stuff()->col_size < 0)
		tputs("Window too small !", 1, ft_putchr);
	tputs(tgoto(tgetstr("cm", NULL), (k * (get_stuff()->col_size + 2)), j), 1, ft_putchr);
	if (fct_size()->ws_col - ((k * (get_stuff()->col_size + 2)) + get_stuff()->max_len) >= 0)
	{
		if (tmp->select == TRUE)
			ft_putstr("\033[7m");
		if (tmp->cursor == TRUE)
			ft_putstr("\033[4m");
		if (ft_strlen(tmp->name) > get_stuff()->col_size)
			putchr_max_len_fd(tmp->name);
		else
			tputs(tmp->name, 1, ft_putchr);
		ft_putstr("\033[0m");
	}
	else
	{
		tputs(tgoto(tgetstr("cm", NULL), fct_size()->ws_col - 5, fct_size()->ws_row), 1, ft_putchr);
		tputs("[...]", 1, ft_putchr);
	}
	displayed_col = fct_size()->ws_col / (get_stuff()->col_size + (k * 2));
	if (tmp->cursor == TRUE && tmp->no_elt > (displayed_col * fct_size()->ws_row))
	{}
	return (0);
}

int				manage_columns()
{
	if (DEBUG == 1)
		ft_putendl("manage columns");
	t_cduo			*tmp;
	int				i;
	int				j;
	int				k;

	get_col_size();
	i = 0;
	k = 0;
	tmp = get_stuff()->lst_param;
	while ((i += tmp->first) < 2)
	{
		tmp->col_nb = k;
		j = 0;
		while(j < fct_size()->ws_row)
		{
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

	ft_putendl_fd("((blabla))\n", 0);
	while (ret[i] != NULL)
	{
		ft_putstr_fd(ret[i], 0);
		ft_putchar_fd(' ', 0);
		i++;
	}
	ft_putchar_fd('\n', 0);
	return (0);
}
