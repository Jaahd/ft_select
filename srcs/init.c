#include <term.h> //pour tgetent / tgetstr / tputs
#include <termios.h> // pour tcgetattr / tcsetattr
#include <stdlib.h> // pour getenv
#include <fcntl.h> // pour open
#include "ft_select.h"
#include "libft.h"

static int		enable_keyboard(void)
{
	if (DEBUG == 1)
		ft_putendl("enable_keyboard");
	char	*str;

	if (tgetstr("ks", NULL) == NULL)
		return (-1);
	if ((str = tgetstr("ke", NULL)) == NULL)
		return (-1);
	tputs(str, 1, ft_putchr);
	return (0);
}

static int		hide_cursor(void)
{
	if (DEBUG == 1)
		ft_putendl("hide_cursor");
	char	*str;

	if ((str = tgetstr("vi", NULL)) == NULL)
		return (-1);
	tputs(str, 1, ft_putchr);
	return (0);
}

int				termcap_init()
{
	if (DEBUG == 1)
		ft_putendl("termcap_init");
	char				*name_term;

//	manage_signal();
	if ((get_stuff()->fd = open(ttyname(0), O_WRONLY)) == -1)
		return (-1);
	if ((name_term = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, name_term) == -1)
		return (-1);
	if (tcgetattr(0, get_term()) == -1)
		return (-1);
	get_term()->c_lflag &= ~(ICANON | ECHO); // mode canonique
	get_term()->c_cc[VMIN] = 1;
	get_term()->c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, get_term()) == -1)
		return (-1);
	hide_cursor();
	enable_keyboard();
	get_s_win();
	return (0);
}
