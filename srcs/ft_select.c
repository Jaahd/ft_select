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
	termcap_reset();
	return (-1);
}

void			free_lst_param()
{
	if (DEBUG == 1)
		ft_putendl("free_lst_param");
	t_cduo				*tmp;

	tmp = get_stuff()->lst_param;
	while (tmp)
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

	lst_param = NULL;
	ret = NULL;
	//signal(SIGINT, sig_exit_pgm);
	if (termcap_init() == -1)
		manage_error(1);
	get_stuff()->max_len = fill_list(&lst_param, ac, av);
	while (1)
	{
//		clr_screen();
		manage_columns();
		if ((ret = fct_read()) != NULL)
			break ;
	}
	if (ret != NULL)
		print_return(ret);
	termcap_reset();
	return (0);
}
