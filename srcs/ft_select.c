#include <term.h> //pour tgetent
#include <termios.h> // pour tcgetattr / tcsetattr
#include <stdlib.h> // pour getenv
#include "ft_select.h"
#include "libft.h"

int				manage_error(int i, struct termios *term)
{
	if (DEBUG == 1)
		ft_putendl("manage error");
	if (i == 1)
		ft_putendl("ft_select: can't initialize termcap");
	termcap_reset(term);
	return (-1);
}


int				aff_params(t_cduo *lst_param)
{
	if (DEBUG == 1)
		ft_putendl("aff params");
	int					i;
	t_cduo				*tmp;

	i = 0;
	tmp = lst_param;
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

int				main(int ac, char **av)
{
	t_termios			term;
	t_cduo				*lst_param;
	char				**ret;
	int					i;

	lst_param = NULL;
	ret = NULL;
	get_s_win();
//	printf("lignes [[%d]]\tcol {{%d}}\n", fct_size()->ws_row, fct_size()->ws_col);
	if (termcap_init(&term) == -1)
		manage_error(1, &term);
	fill_list(&lst_param, ac, av);
	i = 0;
	while (1)
	{
		clr_screen();
		aff_params(lst_param);
		if ((ret = fct_read(&lst_param, &term)) != NULL)
			break ;
	}
	if (ret != NULL)
		print_return(ret);
	termcap_reset(&term);
	return (0);
}
