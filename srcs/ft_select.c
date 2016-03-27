#include <term.h> //pour tgetent
#include <termios.h> // pour tcgetattr / tcsetattr
#include <stdlib.h> // pour getenv
#include <unistd.h> // pour close
#include "ft_select.h"
#include "libft.h"

int				manage_error(int i)
{
	if (DEBUG == 1)
		ft_putendl("manage error");
	if (i == 1)
		ft_putendl("ft_select: can't initialize termcap");
	termcap_reset();
	return (-1);
}

int				main(int ac, char **av)
{
	t_cduo				*lst_param;
	char				**ret;
	int					max_len;
	int					fd;

	lst_param = NULL;
	ret = NULL;
	manage_signal();
	fd = get_s_win();
	if (termcap_init() == -1)
		manage_error(1);
	max_len = fill_list(&lst_param, ac, av);
	while (1)
	{
		clr_screen();
		manage_columns(lst_param, max_len);
		if ((ret = fct_read(&lst_param)) != NULL)
			break ;
	}
	close(fd);
	if (ret != NULL)
		print_return(ret);
	termcap_reset();
	return (0);
}
