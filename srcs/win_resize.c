#include <stdlib.h>
#include <unistd.h> // pour ttyname
#include <fcntl.h> // pour open
#include <sys/ioctl.h> // pour ioctl
#include "ft_select.h"
#include "libft.h"

int				manage_columns()
{

	return (0);
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
	int				fd;

	fd = open(ttyname(0), O_WRONLY);
	ioctl(fd, TIOCGWINSZ, fct_size());
	return (0);
}
