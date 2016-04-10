#include "libft.h"
#include "ft_select.h"

static char			**enter_key_bis(char **ret)
{
	if (DEBUG == 1)
		ft_putendl("enter_key_bis");
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

char				**enter_key()
{
	if (DEBUG == 1)
		ft_putendl("enter_key");
	char				**ret;
	t_cduo				*tmp;
	int					i;

	tmp = get_stuff()->lst_param;
	i = tmp->select;
	ret = NULL;
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
/*
int					space_key()
{
	if (DEBUG == 1)
		ft_putendl("space_key");
	t_cduo				*tmp;

	tmp = get_stuff()->lst_param;
	while (tmp->cursor == FALSE)
		tmp = tmp->next;
	tmp->select = tmp->select == TRUE ? FALSE : TRUE;
	tmp->cursor = FALSE;
	tmp->next->cursor = TRUE;
	return (0);
}
*/
int					esc_key()
{
	if (DEBUG == 1)
		ft_putendl("esc_key");
	termcap_reset();
	exit(EXIT_SUCCESS);
	return (0);
}

int					suppr_key()
{
	if (DEBUG == 1)
		ft_putendl("suppr_key");
	t_cduo				*tmp;

	tmp = get_stuff()->lst_param;
	while (tmp->cursor == FALSE)
		tmp = tmp->next;
	if (tmp->first == TRUE)
	{
		tmp->next->first = TRUE;
		tmp->next->first_disp = TRUE;
		get_stuff()->lst_param = tmp->next;
	}
	tmp->next->prev = tmp->prev;
	tmp->prev->next = tmp->next;
	tmp->next->cursor = TRUE;
	tmp->next = NULL;
	tmp->prev = NULL;
	free(tmp->name);
	free(tmp);
	tmp = NULL;
	get_stuff()->nb_elt -= 1;
	if (get_stuff()->nb_elt == 0)
		esc_key();
//	printf("\t\t\t\t\t((%s))\n", get_stuff()->lst_param->name);
	return (0);
}
