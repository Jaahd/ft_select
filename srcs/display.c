#include <term.h> //pour tgetent
#include <termios.h>
#include "ft_select.h"
#include "libft.h"

int				manage_columns(t_cduo *lst_param, int max_len)
{
	if (DEBUG == 1)
		ft_putendl("manage columns");
	t_cduo			*tmp;
	int				row;
	int				col;
	int				i;
	int				j;
	int				k;

	row = fct_size()->ws_row;
	col = fct_size()->ws_col;
	i = 0;
	k = 0;
	tmp = lst_param;
	while ((i += tmp->first) < 2)
	{
		j = 0;
		while(j < row)
		{
		tputs(tgoto(tgetstr("cm", NULL), (k * (max_len + 2)), j), 1, ft_putchr);
			if (tmp->select == TRUE)
				ft_putstr("\033[7m");
			if (tmp->cursor == TRUE)
				ft_putstr("\033[4m");
			tputs(tmp->name, 1, ft_putchr);
			ft_putstr("\033[0m");
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
