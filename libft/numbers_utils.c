/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:50:45 by xiribar           #+#    #+#             */
/*   Updated: 2025/10/15 13:50:46 by xiribar          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nb_len(long value, int base_len)
{
	int	counter;

	counter = 0;
	if (value < 0)
		value *= -1;
	while (value > 0)
	{
		counter++;
		value /= base_len;
	}
	return (counter);
}

int	ft_lnb_len(unsigned long value, int base_len)
{
	int	counter;

	counter = 0;
	while (value > 0)
	{
		counter++;
		value /= base_len;
	}
	return (counter);
}

int	ft_putptr_base(unsigned long value, char *base, int flag)
{
	unsigned long	base_len;
	int				counter;

	if (!value && flag == 1)
		return (ft_putnstr("(nil)", ft_strlen("(nil)")));
	base_len = ft_strlen(base);
	counter = 0;
	counter += ft_lnb_len(value, base_len);
	if (flag)
		counter += ft_putstr("0x");
	if (value >= base_len)
	{
		ft_putptr_base(value / base_len, base, 0);
		ft_putptr_base(value % base_len, base, 0);
	}
	else
		ft_putchar(base[value]);
	return (counter);
}

int	ft_putu_base(unsigned int value, char *base)
{
	unsigned int	base_len;
	int				counter;

	if (!value)
		return (ft_putchar('0'));
	base_len = ft_strlen(base);
	counter = 0;
	counter += ft_lnb_len(value, base_len);
	if (value >= base_len)
	{
		ft_putu_base(value / base_len, base);
		ft_putu_base(value % base_len, base);
	}
	else
		ft_putchar(base[value]);
	return (counter);
}

int	ft_putd_base(int value, char *base)
{
	long	base_len;
	long	nl;
	int		counter;

	if (!value)
		return (ft_putchar('0'));
	nl = value;
	base_len = ft_strlen(base);
	counter = 0;
	counter += ft_nb_len(nl, base_len);
	if (nl < 0)
	{
		counter += ft_putchar('-');
		nl = -nl;
	}
	if (nl >= base_len)
	{
		ft_putd_base(nl / base_len, base);
		ft_putd_base(nl % base_len, base);
	}
	else
		ft_putchar(base[nl]);
	return (counter);
}
