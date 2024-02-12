/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:49:41 by omfelk            #+#    #+#             */
/*   Updated: 2023/10/21 10:54:15 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static unsigned int	baselen_verif(char *base)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = 1;
	while (base[j] != '\0')
	{
		if (base[j] == '+' || base[j] == '-')
			return (0);
		while (base[i] != '\0')
		{
			if (i == j)
				i++;
			if (base[j] == base[i])
				return (0);
			i++;
		}
		i = 0;
		j++;
	}
	if (j > 1)
		return (j);
	else
		return (0);
}

static int	conver(unsigned int len, unsigned long long nb,
									char *text, int *size)
{
	if (nb >= (unsigned int)len)
	{
		conver(len, nb / len, text, size);
		conver(len, nb % len, text, size);
	}
	else
	{
		write(1, &text[nb], 1);
		*size += 1;
	}
	return (*size);
}

int	ft_putptr(unsigned long long nbr, char *base)
{
	unsigned int	len;
	int				size;

	if (nbr == 0)
	{
		size = ft_putstr("(nil)");
		return (size);
	}
	size = ft_putstr("0x");
	len = baselen_verif(base);
	if (len != 0)
		conver(len, nbr, base, &size);
	return (size);
}
