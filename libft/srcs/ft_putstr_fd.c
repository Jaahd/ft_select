/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 18:07:10 by avacher           #+#    #+#             */
/*   Updated: 2015/12/11 11:57:33 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char const *s, int fd)
{
	size_t	cpt;

	cpt = 0;
	while (s && s[cpt] != '\0')
	{
		ft_putchar_fd(s[cpt], fd);
		cpt++;
	}
}
