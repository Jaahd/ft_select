/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tbl_to_duo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 10:47:52 by avacher           #+#    #+#             */
/*   Updated: 2016/01/10 12:01:07 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_duo				*tbl_to_duo(char **tbl, char c)
{
	int				i;
	char			*tmp_name;
	char			*tmp_value;
	t_duo			*lst;

	lst = NULL;
	i = 0;
	while (tbl[i])
	{
		tmp_name = srch_begining(tbl[i], c);
		tmp_value = srch_value(tbl[i], c);
		duo_pushback(&lst, tmp_name, tmp_value);
		i++;
	}
	return (lst);
}
