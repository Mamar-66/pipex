/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:36:18 by omfelk            #+#    #+#             */
/*   Updated: 2023/10/23 11:55:39 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include <stdarg.h>
#include <limits.h>

int	type_format(va_list args, const char format)
{
	int		size;

	size = 0;
	if (format == 'c')
		size += ft_putchar(va_arg(args, int));
	else if (format == 'p')
		size += ft_putptr(va_arg(args, unsigned long long), "0123456789abcdef");
	else if (format == 's')
		size += ft_putstr(va_arg(args, char *));
	else if (format == 'd' || format == 'i')
		size += ft_putnbr(va_arg(args, int));
	else if (format == 'u')
		size += ft_putnbr_unsigned(va_arg(args, unsigned int));
	else if (format == 'x')
		size += ft_putnbr_base(va_arg(args, int), "0123456789abcdef");
	else if (format == 'X')
		size += ft_putnbr_base(va_arg(args, int), "0123456789ABCDEF");
	else if (format == '%')
		size += ft_putchar('%');
	return (size);
}

int	ft_printf(const char *text, ...)
{
	va_list		args;
	int			i;
	int			total_size;

	i = 0;
	total_size = 0;
	va_start(args, text);
	while (text[i])
	{
		if (text[i] == '%')
			total_size += type_format(args, text[i++ + 1]);
		else
			total_size += ft_putchar(text[i]);
		i++;
	}
	va_end(args);
	return (total_size);
}
/*
int	main(void)
{
	int		v;
	int		f;

	v = 0;
	f = 0;
	char	*c;

	c = NULL;
	f = ft_printf("f : caract = %c string =  %s ptr = %p\n", 'c', c, NULL);
	f += ft_printf("f : d = %d i = %i u %u\n", 0, INT_MIN, 0);
	f += ft_printf("f : x = %x X = %X le %%\n", 255, 255);
	v = printf("v : caract = %c string =  %s ptr = %p\n", 'c', c, NULL);
	v += printf("v : d = %d i = %i u %u\n", 0, INT_MIN, 0);
	v += printf("v : x = %x X = %X le %%\n", 255, 255);
	printf("f = %d\n", f);
	printf("v = %d\n", v);
	return (0);
}*/
