#include <term.h> //pour tgetent
#include "ft_select.h"
#include "libft.h"

int				aff_params(t_cduo *lst_param)
{
	if (DEBUG == 1)
		ft_putendl("aff params");
	int					i;
	t_cduo				*tmp;

	i = 0;
	tmp = lst_param;
	if (tmp->nb_elt > fct_size()->ws_row)
	{
		manage_columns();
		return (0);
	}
	while ((i += tmp->first) < 2)
	{
		if (tmp->select == TRUE)
			ft_putstr("\033[7m");
		if (tmp->cursor == TRUE)
			ft_putstr("\033[4m");
		tputs(tmp->name, 1, ft_putchr);
		tputs("\n", 1, ft_putchr);
		ft_putstr("\033[0m");
		tmp = tmp->next;
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
		ft_putstr_fd(ret[i], 0);
		ft_putchar_fd(' ', 0);
		i++;
	}
	ft_putchar_fd('\n', 0);
	return (0);
}
