/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:44:33 by xiribar           #+#    #+#             */
/*   Updated: 2025/10/01 11:44:36 by xiribar          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*temp_dest;
	const char	*temp_src;

	temp_src = (const char *)src;
	temp_dest = (char *)dest;
	if (temp_dest < temp_src)
	{
		while (n > 0)
		{
			*temp_dest++ = *temp_src++;
			n--;
		}
	}
	else if (temp_dest > temp_src)
	{
		temp_dest += n - 1;
		temp_src += n - 1;
		while (n > 0)
		{
			*temp_dest-- = *temp_src--;
			n--;
		}
	}
	return (dest);
}
