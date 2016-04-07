#include <term.h> //pour tgetent
#include <termios.h> // pour tcgetattr / tcsetattr
#include <stdlib.h> // pour getenv
#include <unistd.h> // pour close
#include "ft_select.h"
#include "libft.h"

#include <signal.h>

int				manage_error(int i)
{
	if (DEBUG == 1)
		ft_putendl("manage error");
	if (i == 1)
		ft_putendl("ft_select: can't initialize termcap");
	if (i == 2)
		ft_putendl("ft_select: usage: ./ft_select arg_1 [arg_2] [...] [arg_n]");
	termcap_reset();
	exit(EXIT_FAILURE);
	return (-1);
}

void			free_lst_param()
{
	if (DEBUG == 1)
		ft_putendl("free_lst_param");
	t_cduo				*tmp;

	if (get_stuff()->lst_param == NULL)
		return ;
	tmp = get_stuff()->lst_param;
	while (tmp != NULL && get_stuff()->nb_elt > 0)
	{
		tmp->next->prev = tmp->prev;
		tmp->prev->next = tmp->next;
		tmp->next = NULL;
		tmp->prev = NULL;
		free(tmp->name);
		free(tmp);
		tmp = tmp->next;
	}
}

int				main(int ac, char **av)
{
	t_cduo				*lst_param;
	char				**ret;

	if (ac == 1)
		manage_error(2);
	lst_param = NULL;
	ret = NULL;
	if (termcap_init() == -1)
		manage_error(1);
	get_stuff()->max_len = fill_list(&lst_param, ac, av);
	while (1)
	{
		clr_screen();
		manage_columns();
		if ((ret = fct_read()) != NULL)
			break ;
	}
	termcap_reset();
	if (ret != NULL)
		print_return(ret);
	return (0);
}
