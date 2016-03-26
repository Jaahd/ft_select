#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <stdio.h>

# define DEBUG 0

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
	struct s_cduo		*prev;
	struct s_cduo		*next;
}						t_cduo;

int						cduo_pushback(t_cduo **lst, char *name);

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
int						esc_key(int buff, t_cduo **lst_param, t_termios *term);
int						suppr_key(int buff, t_cduo **lst_param, t_termios *t);


int						termcap_reset(struct termios *term);

#endif
