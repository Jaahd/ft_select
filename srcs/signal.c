#include <signal.h>
#include "ft_select.h"

void			sig_winsize(int sig)
{
	(void)sig;
	get_s_win();
}

void			sig_ctrl_d(int sig)
{
	(void)sig;
}

void			sig_ctrl_c(int sig)
{
	(void)sig;
}

int				manage_signal()
{
	signal(SIGWINCH, sig_winsize);
	signal(SIGQUIT, sig_ctrl_d);
	signal(SIGTSTP, sig_ctrl_z);
	signal(SIGCONT, sig_fg);
	signal(SIGINT, sig_ctrl_c);
	return (0);
}
