/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cduo_pushback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 10:47:52 by avacher           #+#    #+#             */
/*   Updated: 2016/01/10 12:01:07 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft.h"

static t_cduo		*cduo_new(char *name)
{
	if (DEBUG == 1)
		ft_putendl("cduo new");
	t_cduo			*new;

	if ((new = (t_cduo *)malloc(sizeof(t_cduo))) == NULL)
		return (NULL);
	new->name = NULL;
	new->first = FALSE;
	new->select = FALSE;
	new->cursor = FALSE;
	if (name == NULL)
		return (NULL);
	new->name = ft_strdup(name);
	return (new);
}

int					cduo_pushback(t_cduo **lst, char *name, int no_elt)
{
	if (DEBUG == 1)
		ft_putendl("cduo pushbk");
	t_cduo			*tmp;

	tmp = *lst;
	if (tmp == NULL)
	{
		*lst = cduo_new(name);
		(*lst)->first = TRUE;
		(*lst)->cursor = TRUE;
		(*lst)->no_elt = no_elt;
		(*lst)->next = *lst;
		(*lst)->prev = *lst;
		return (0);
	}
	while (tmp->next->first != TRUE)
		tmp = tmp->next;
	tmp->next = cduo_new(name);
	tmp->next->prev = tmp;
	tmp->next->next = *lst;
	(*lst)->prev = tmp->next;
	return (0);
}
