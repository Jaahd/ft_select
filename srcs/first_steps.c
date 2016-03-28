#include <unistd.h> // read
#include <term.h> //pour tgetent / tgetstr / tputs
#include "ft_select.h"
#include "libft.h"

static char			**get_input(int buff)
{
	if (DEBUG == 1)
		ft_putendl("get_input");
	char				**ret;

	ret = NULL;
	if (buff == DOWN_ARROW)
		down_arrow();
	if (buff == UP_ARROW)
		up_arrow();
	if (buff == SPACE)
		space_key();
	if (buff == DELETE || buff == BACKSPACE)
		suppr_key();
	if (buff == ESCAPE)
		esc_key();
	if (buff  == RETURN)
		ret = enter_key(buff);
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

int 			fill_list(t_cduo **lst_param, int ac, char **av)
{
	if (DEBUG == 1)
		ft_putendl("fill list");
	int					i;
	int					len;
	int					max_len;

	i = 1;
	len = 0;
	max_len = 0;
	while (i < ac)
	{
		cduo_pushback(lst_param, av[i], i + 1);
		len = ft_strlen(av[i]);
		if (len > 40)
			max_len = 40;
		else if (max_len < len)
			max_len = len;
		i++;
	}
	get_stuff()->nb_elt = i - 1;
	get_stuff()->lst_param = *lst_param;
	return (max_len);
}

char 				**fct_read()
{
	if (DEBUG == 1)
		ft_putendl("fct read");
	int					buff;
	char				**ret;

	buff = 0;
	ret = NULL;
	if (read(0, &buff, 4) == -1)
		return (NULL);//
	ret = get_input(buff);
	return (ret);
}
