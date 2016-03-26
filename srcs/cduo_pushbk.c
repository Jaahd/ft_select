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

static void			*cduo_new(char *name)
{
	if (DEBUG == 1)
		ft_putendl("cduo new");

	get_cduo()->name = NULL;
	get_cduo()->first = FALSE;
	get_cduo()->select = FALSE;
	get_cduo()->cursor = FALSE;
	if (name == NULL)
		return (NULL);
	get_cduo()->name = ft_strdup(name);
}

int					cduo_pushback(char *name)
{
	if (DEBUG == 1)
		ft_putendl("cduo pushbk");
	t_cduo			*tmp;

	tmp = get_cduo();
	if (tmp == NULL)
	{
		cduo_new(name);
		get_cduo()->first = TRUE;
		get_cduo()->cursor = TRUE;
		get_cduo()->next = get_cduo();
		get_cduo()->prev = get_cduo();
		return (0);
	}
	while (tmp->next->first != TRUE)
		tmp = tmp->next;
	tmp->next = cduo_new(name);
	tmp->next->prev = tmp;
	tmp->next->next = get_cduo();
	(get_cduo())->prev = tmp->next;
	return (0);
}
