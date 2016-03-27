#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <stdio.h>
# include <sys/ioctl.h>
# include <termios.h>

# define DEBUG 1

# define BUFF_SIZE 2048
# define TRUE 1
# define FALSE 0
# define UP_ARROW 4283163
# define DOWN_ARROW 4348699
# define SPACE 32
# define DELETE 2117294875
# define BACKSPACE 127
# define RETURN 10
# define ESCAPE 27
//# define RIGHT_ARROW 4414235
//# define LEFT_ARROW 4479771

typedef struct			termios t_termios;
typedef struct			winsize t_winsize;

typedef struct			s_cduo
{
	char				*name;
	int					first;
	int					select;
	int					cursor;
	int					nb_elt;
	int					max_len;
	struct s_cduo		*prev;
	struct s_cduo		*next;
}						t_cduo;

int						cduo_pushback(t_cduo **lst_param, char *name);

/*
** first_steps.c
*/
void					clr_screen();
int						fill_list(t_cduo **lst_param, int ac, char **av);
char					**fct_read(t_cduo **lst_param);

/*
** init.c
*/
int						termcap_init();

/*
** reset.c
*/
int						termcap_reset();

/*
** display.c
*/
int						manage_columns(t_cduo *lst_param, int max_len);
int						print_return(char **ret);

/*
** moves.c
*/
int						down_arrow(int buff, t_cduo **lst_param);
int						up_arrow(int buff, t_cduo **lst_param);

/*
** actions.c
*/
char					**enter_key(int buff, t_cduo **lst_param);
int						space_key(int buff, t_cduo **lst_param);
int						esc_key(int buff, t_cduo **lst_param);
int						suppr_key(int buff, t_cduo **lst_param);

/*
** win_resize.c
*/
t_winsize				*fct_size();
int						get_s_win();
t_cduo					*get_cduo();
t_termios				*get_term();

/*
** signal
*/
int						manage_signal();

#endif
