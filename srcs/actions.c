#include "libft.h"
#include "ft_select.h"

static char			**enter_key_bis(char **ret)
{
	int					j;
	t_cduo				*tmp;

	j = 0;
	tmp = get_stuff()->lst_param;
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

char				**enter_key(int buff)
{
	char				**ret;
	t_cduo				*tmp;
	int					i;

	tmp = get_stuff()->lst_param;
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
	ret = enter_key_bis(ret);
	return (ret);
}

int					space_key(int buff)
{
	t_cduo				*tmp;

	tmp = get_stuff()->lst_param;
	if (buff != SPACE)
		return (-1);
	while (tmp->cursor == FALSE)
		tmp = tmp->next;
	tmp->select = tmp->select == TRUE ? FALSE : TRUE;
	tmp->cursor = FALSE;
	tmp->next->cursor = TRUE;
	return (0);
}

int					esc_key(int buff)
{
	t_cduo				*tmp;

	tmp = get_stuff()->lst_param;
	if (buff != ESCAPE || (tmp == NULL && buff != DELETE && buff != BACKSPACE))
		return (-1);
	termcap_reset();
	return (0);
}

int					suppr_key(int buff)
{
	t_cduo				*tmp;

	if (buff != DELETE && buff != BACKSPACE)
		return (-1);
	tmp = get_stuff()->lst_param;
	while (tmp->cursor == FALSE)
		tmp = tmp->next;
	if (tmp->first == TRUE)
	{
		tmp->next->first = TRUE;
		get_stuff()->lst_param = tmp->next;
	}
	tmp->next->prev = tmp->prev;
	tmp->prev->next = tmp->next;
	tmp->next->cursor = TRUE;
	tmp->next = NULL;
	tmp->prev = NULL;
	free(tmp->name);
	free(tmp);
	get_stuff()->nb_elt -= 1;
	if (get_stuff()->lst_param == NULL)
		esc_key(buff);
	return (0);
}
