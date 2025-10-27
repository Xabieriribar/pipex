/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:47:20 by xiribar           #+#    #+#             */
/*   Updated: 2025/10/14 12:47:21 by xiribar          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	size_t	len;

	if (!str)
		return (ft_putnstr("(null)", ft_strlen("(null)")));
	len = 0;
	while (*str)
	{
		ft_putchar(*str);
		str++;
		len++;
	}
	return (len);
}

int	ft_putnstr(char *str, size_t strlen)
{
	if (!str)
		return (0);
	return (write(1, str, strlen));
}
