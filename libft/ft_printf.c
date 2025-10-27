/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:47:14 by xiribar           #+#    #+#             */
/*   Updated: 2025/10/14 12:47:15 by xiribar          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_parser(char c, va_list ap)
{
	char	*base_hex_l;
	char	*base_hex_u;
	char	*base_dec;

	base_hex_l = "0123456789abcdef";
	base_hex_u = "0123456789ABCDEF";
	base_dec = "0123456789";
	if (c == 'c')
		return (ft_putchar(va_arg(ap, int)));
	else if (c == 's')
		return ((ft_putstr(va_arg(ap, char *))));
	else if (c == 'p')
		return (ft_putptr_base(va_arg(ap, unsigned long), base_hex_l, 1));
	else if (c == 'd' || c == 'i')
		return (ft_putd_base(va_arg(ap, int), base_dec));
	else if (c == 'u')
		return (ft_putu_base(va_arg(ap, unsigned int), base_dec));
	else if (c == 'x')
		return (ft_putu_base(va_arg(ap, unsigned int), base_hex_l));
	else if (c == 'X')
		return (ft_putu_base(va_arg(ap, unsigned int), base_hex_u));
	else if (c == '%')
		return (ft_putchar('%'));
	else
		return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list			args;
	unsigned char	*s;
	unsigned int	chars_written;

	if (!format)
		return (0);
	s = (unsigned char *)format;
	chars_written = 0;
	va_start(args, format);
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			chars_written += ft_parser(*s, args);
		}
		else
			chars_written += ft_putchar(*s);
		s++;
	}
	va_end(args);
	return (chars_written);
}
