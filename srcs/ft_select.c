#include <term.h> //pour tgetent
#include <termios.h> // pour tcgetattr / tcsetattr
#include <stdlib.h> // pour getenv
#include <fcntl.h> // pour open
#include <sys/ioctl.h> // pour ioctl
#include "ft_select.h"
#include "libft.h"

int		enable_keyboard(void)
{
	char	*str;

	if (tgetstr("ks", NULL) == NULL)
		return (-1);
	if ((str = tgetstr("ke", NULL)) == NULL)
		return (-1);
	tputs(str, 1, ft_putchr);
	return (0);
}

int		disable_keyboard(void)
{
	char	*str;

	if (tgetstr("ks", NULL) == NULL)
		return (-1);
	if ((str = tgetstr("ki", NULL)) == NULL)
		return (-1);
	tputs(str, 1, ft_putchr);
	return (0);
}

int		display_cursor(void)
{
	char	*str;

	if ((str = tgetstr("ve", NULL)) == NULL)
		return (-1);
	tputs(str, 1, ft_putchr);
	return (0);
}

int		hide_cursor(void)
{
	char	*str;

	if ((str = tgetstr("vi", NULL)) == NULL)
		return (-1);
	tputs(str, 1, ft_putchr);
	return (0);
}

int				termcap_init(struct termios *term)
{
	if (DEBUG == 1)
		ft_putendl("termcap_init");
	char				*name_term;

	if ((name_term = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, name_term) == -1)
		return (-1);
	if (tcgetattr(0, term) == -1)
		return (-1);
	term->c_lflag &= ~(ICANON | ECHO); // mode canonique
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, term) == -1)
		return (-1);
	hide_cursor();
	enable_keyboard();
	return (0);
}

int				termcap_reset(struct termios *term)
{
	if (DEBUG == 1)
		ft_putendl("termcap_reset");
	if (tcgetattr(0, term) == -1)
		return (-1);
	term->c_lflag = (ICANON | ECHO);
	if (tcsetattr(0, TCSANOW, term) == -1)
		return (-1);
	display_cursor();
	return (0);
}

int				manage_error(int i, struct termios *term)
{
	if (DEBUG == 1)
		ft_putendl("manage error");
	if (i == 1)
		ft_putendl("ft_select: can't initialize termcap");
	termcap_reset(term);
	return (-1);
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

	i = 1;
	while (i < ac)
	{
		cduo_pushback(lst_param, av[i]);
		i++;
	}
	return (0);
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

char				**get_input(int buff, t_cduo **lst_param, t_termios *term)
{
	if (DEBUG == 1)
		ft_putendl("fct read");
	char				*str;
	char				**ret;

	str = tgetstr("cl", NULL);
	down_arrow(buff, lst_param);
	up_arrow(buff, lst_param);
	space_key(buff, lst_param);
	suppr_key(buff, lst_param, term);
	esc_key(buff, lst_param, term);
	ret = enter_key(buff, lst_param);
	return (ret);
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

t_winsize		*fct_size()
{
	static t_winsize	*win_size = NULL;

	if (win_size == NULL)
		win_size = (t_winsize *)malloc(sizeof(t_winsize));
	return (win_size);
}

int				get_s_win()
{
	int				fd;

	fd = open(ttyname(0), O_WRONLY);
	ioctl(fd, TIOCGWINSZ, fct_size());
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
	printf("lignes [[%d]]\tcol {{%d}}\n", fct_size()->ws_row, fct_size()->ws_col);
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
