#include "libft.h"
#include "ft_select.h"

static char			**enter_key_bis(char **ret, t_cduo **lst_param)
{
	int					j;
	t_cduo				*tmp;

	j = 0;
	tmp = *lst_param;
	if (tmp->select == TRUE)
	{
		if ((ret[j] = ft_strdup(tmp->name)) == NULL)
			return (NULL);
		j++;
	}
	while (tmp->next->first != TRUE)
	{
		if (tmp->next->select == TRUE)
		{
			if ((ret[j] = ft_strdup(tmp->next->name)) == NULL)
				return (NULL);
			j++;
		}
		tmp = tmp->next;
	}
	ret[j] = NULL;
	return (ret);
}

char				**enter_key(int buff, t_cduo **lst_param)
{
	char				**ret;
	t_cduo				*tmp;
	int					i;

	tmp = *lst_param;
	i = tmp->select;
	ret = NULL;
	if (buff != RETURN)
		return (NULL);
	while (tmp->next->first != TRUE)
	{
		if (tmp->next->select == TRUE)
			i++;
		tmp = tmp->next;
	}
	if ((ret = (char **)malloc(sizeof(char*) * (i + 1))) == NULL)
		return (NULL);
	ret = enter_key_bis(ret, lst_param);
	return (ret);
}

int					space_key(int buff, t_cduo **lst_param)
{
	t_cduo				*tmp;

	tmp = *lst_param;
	if (buff != SPACE)
		return (-1);
	while (tmp->cursor == FALSE)
		tmp = tmp->next;
	tmp->select = tmp->select == TRUE ? FALSE : TRUE;
	tmp->cursor = FALSE;
	tmp->next->cursor = TRUE;
	return (0);
}

int					esc_key(int buff, t_cduo **lst_param, t_termios *term)
{
	t_cduo				*tmp;

	tmp = *lst_param;
	if (buff != ESCAPE || (tmp == NULL && buff != DELETE && buff != BACKSPACE))
		return (-1);
	while (tmp != NULL)
	{
		tmp->next->prev = tmp->prev;
		tmp->prev->next = tmp->next;
		tmp->next = NULL;
		tmp->prev = NULL;
		free(tmp->name);
		free(tmp);
		tmp = tmp->next;
	}
	termcap_reset(term);
	exit(1);
	return (0);
}

int					suppr_key(int buff, t_cduo **lst_param, t_termios *term)
{
	t_cduo				*tmp;

	tmp = *lst_param;
	if (buff != DELETE && buff != BACKSPACE)
		return (-1);
	while (tmp->cursor == FALSE)
		tmp = tmp->next;
	tmp->next->prev = tmp->prev;
	tmp->prev->next = tmp->next;
	tmp->prev->next->cursor = TRUE;
	tmp->next = NULL;
	tmp->prev = NULL;
	free(tmp->name);
	free(tmp);
	tmp->nb_elt -= 1;
	if (tmp == NULL)
		esc_key(buff, lst_param, term);
	return (0);
}
