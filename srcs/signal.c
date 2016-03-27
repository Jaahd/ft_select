#include <signal.h>
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
/*
void			sig_interrupt(int sig)
{
	if (DEBUG == 1)
		ft_putendl("sig_interrupt");
	(void)sig;
}

void			sig_continue(int sig)
{
	if (DEBUG == 1)
		ft_putendl("sig_continue");
	(void)sig;
}
*/
void			sig_exit_pgm(int sig)
{
	if (DEBUG == 1)
		ft_putendl("sig_exit_pgm");
	(void)sig;
	termcap_reset();
}

void			manage_signal()
{
	if (DEBUG == 1)
		ft_putendl("manage_signal");
	signal(SIGWINCH, sig_winsize);
//	signal(SIGTSTP, sig_interrupt);
//	signal(SIGCONT, sig_continue);
	signal(SIGINT, sig_exit_pgm);
	signal(SIGQUIT, sig_exit_pgm);
	signal(SIGTERM, sig_exit_pgm);
	signal(SIGKILL, sig_exit_pgm);
}
