/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:58:53 by avacher           #+#    #+#             */
/*   Updated: 2015/11/27 17:49:57 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_putunbr(unsigned int n)
{
	if (n > 9)
		ft_putunbr(n / 10);
	ft_putchar((n % 10) + '0');
}

void			ft_putnbr(int n)
{
	if (n < 0)
	{
		ft_putchar('-');
		ft_putunbr(-n);
	}
	else
		ft_putunbr(n);
}
