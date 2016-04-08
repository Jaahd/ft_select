#include <term.h> //pour tgetent / tgetstr / tputs
#include <termios.h> // pour tcgetattr / tcsetattr
#include <stdlib.h> // pour getenv
#include <signal.h>
#include <fcntl.h> // pour open
#include "ft_select.h"
#include "libft.h"

void			sig_winsize(int sig)
{
	if (DEBUG == 1)
		ft_putendl("sig_winsize");
	(void)sig;
	get_s_win();
	clr_screen();
	manage_columns();
}

void			sig_interrupt(int sig)
{
	if (DEBUG == 1)
		ft_putendl("sig_interrupt");
	char			cp[2];
	
	(void)sig;
	cp[0] = get_term()->c_cc[VSUSP];
	cp[1] = 0;
	clr_screen();
	tputs(tgetstr("te", NULL), 1, ft_putchr);
	display_cursor();
	disable_keyboard();
	tcgetattr(get_stuff()->fd, get_term());
	get_term()->c_lflag |= (ICANON | ECHO);
	tcsetattr(get_stuff()->fd, 0, get_term());
	close(get_stuff()->fd);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGCONT, sig_continue);
	ioctl(0, TIOCSTI, cp);
}

void			sig_continue(int sig)
{
	if (DEBUG == 1)
		ft_putendl("sig_continue");
	(void)sig;
	get_stuff()->fd = open(ttyname(0), O_WRONLY);
	get_term()->c_lflag &= ~(ICANON | ECHO);
	get_term()->c_cc[VMIN] = 1;
	get_term()->c_cc[VTIME] = 0;
	tcsetattr(get_stuff()->fd, TCSADRAIN, get_term());
	hide_cursor();
	enable_keyboard();
	tputs(tgetstr("ti", NULL), 1, ft_putchr);
	clr_screen();
	get_s_win();
	manage_columns();
	signal(SIGTSTP, sig_interrupt);
}

void			sig_exit_pgm(int sig)
{
	if (DEBUG == 1)
		ft_putendl("sig_exit_pgm");
	(void)sig;
	termcap_reset();
	exit(EXIT_FAILURE);
}

void			manage_signal()
{
	if (DEBUG == 1)
		ft_putendl("manage_signal");
	signal(SIGWINCH, sig_winsize);
	signal(SIGTSTP, sig_interrupt);
	signal(SIGCONT, sig_continue);
	signal(SIGINT, sig_exit_pgm);
	signal(SIGQUIT, sig_exit_pgm);
	signal(SIGTERM, sig_exit_pgm);
	signal(SIGKILL, sig_exit_pgm);
}
