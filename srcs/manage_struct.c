#include <term.h> // pour tputs
#include <termios.h> // pour tgetstr
#include <stdlib.h>
#include <unistd.h> // pour ttyname
#include <sys/ioctl.h> // pour ioctl
#include "ft_select.h"
#include "libft.h"

t_glst			*get_stuff()
{
	if (DEBUG == 1)
		ft_putendl("get_stuff");
	static t_glst	*stuff = NULL;

	if (stuff == NULL)
		stuff = (t_glst *)malloc(sizeof(t_glst));
	return (stuff);
}

t_termios		*get_term()
{
	if (DEBUG == 1)
		ft_putendl("get_term");
	static t_termios	*term = NULL;

	if (term == NULL)
		term = (t_termios *)malloc(sizeof(t_termios));
	return (term);
}

t_winsize		*fct_size()
{
	if (DEBUG == 1)
		ft_putendl("fct size");
	static t_winsize	*win_size = NULL;

	if (win_size == NULL)
		win_size = (t_winsize *)malloc(sizeof(t_winsize));
	return (win_size);
}

int				get_s_win()
{
	if (DEBUG == 1)
		ft_putendl("get s win");

	ioctl(get_stuff()->fd, TIOCGWINSZ, fct_size());
	return (0);
}
