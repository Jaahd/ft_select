#include <unistd.h> // read
#include <term.h> //pour tgetent / tgetstr / tputs
#include "ft_select.h"
#include "libft.h"

static char			**get_input(int buff, t_cduo **lst_param, t_termios *term)
{
	if (DEBUG == 1)
		ft_putendl("fct read");
	char				**ret;

	down_arrow(buff, lst_param);
	up_arrow(buff, lst_param);
	space_key(buff, lst_param);
	suppr_key(buff, lst_param, term);
	esc_key(buff, lst_param, term);
	ret = enter_key(buff, lst_param);
	return (ret);
}

void			clr_screen()
{
	if (DEBUG == 1)
		ft_putendl("clr screen");
	char			 *str;

	str = tgetstr("cl", NULL);
	tputs(str, 1, ft_putchr);
}

int				fill_list(t_cduo **lst_param, int ac, char **av)
{
	if (DEBUG == 1)
		ft_putendl("fill list");
	int					i;
	int					len;

	i = 1;
	len = 0;
	while (i < ac)
	{
		cduo_pushback(lst_param, av[i]);
		if ((*lst_param)->max_len < (len = ft_strlen(av[i])))
			(*lst_param)->max_len = len < 40 ? len : 40;
		i++;
	}
	(*lst_param)->nb_elt = ac;
	return (0);
}

char 				**fct_read(t_cduo **lst_param, t_termios *term)
{
	if (DEBUG == 1)
		ft_putendl("fct read");
	int					buff;
	char				**ret;

	buff = 0;
	ret = NULL;
	if (read(0, &buff, 4) == -1)
		return (NULL);//
	ret = get_input(buff, lst_param, term);
	return (ret);
}
