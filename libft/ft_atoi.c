/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:09:22 by xiribar           #+#    #+#             */
/*   Updated: 2025/09/30 15:13:41 by xiribar          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	integer;
	int	counter;
	int	sign;	

	sign = 1;
	counter = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	while (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		counter++;
		nptr++;
	}
	if (counter >= 2)
		return (0);
	integer = 0;
	while (ft_isdigit(*nptr))
	{
		integer *= 10;
		integer += (*nptr - '0');
		nptr++;
	}
	return (integer * sign);
}
