#include <term.h> //pour tgetent
#include <termios.h> // pour tcgetattr / tcsetattr
#include <stdlib.h> // pour getenv / exit
#include "ft_select.h"
#include "libft.h"

int				disable_keyboard(void)
{
	if (DEBUG == 1)
		ft_putendl("disable_keyboard");
	char	*str;

	if (tgetstr("ks", NULL) == NULL)
		return (-1);
	if ((str = tgetstr("ki", NULL)) == NULL)
		return (-1);
	tputs(str, 1, ft_putchr);
	return (0);
}

int				display_cursor(void)
{
	if (DEBUG == 1)
		ft_putendl("display_cursor");
	char	*str;

	if ((str = tgetstr("ve", NULL)) == NULL)
		return (-1);
	tputs(str, 1, ft_putchr);
	return (0);
}

void			termcap_reset()
{
	if (DEBUG == 1)
		ft_putendl("termcap_reset");
	clr_screen();
	display_cursor();
	disable_keyboard();
	tcgetattr(0, get_term());
	get_term()->c_lflag |= (ICANON | ECHO);
	tcsetattr(0, 0, get_term());
	free_lst_param();
	close(get_stuff()->fd);
	exit(EXIT_SUCCESS);
}
