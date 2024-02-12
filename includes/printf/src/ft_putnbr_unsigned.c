/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:09:46 by omfelk            #+#    #+#             */
/*   Updated: 2023/10/21 10:33:20 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	ft_write(unsigned int n)
{
	char	c;

	if (n > 9)
	{
		ft_write((n / 10));
		ft_write((n % 10));
	}
	else
	{
		c = n + '0';
		write(1, &c, 1);
	}
}

int	ft_putnbr_unsigned(unsigned int n)
{
	int		i;

	i = 0;
	ft_write(n);
	if (n == 0)
		i++;
	while (n > 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}
