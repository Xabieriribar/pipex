/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:08:35 by xiribar           #+#    #+#             */
/*   Updated: 2025/10/04 12:08:38 by xiribar          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_size(int n)
{
	long	nl;
	int		size;

	nl = n;
	if (nl == 0)
		return (1);
	size = 0;
	if (nl < 0)
	{
		nl *= -1;
		size++;
	}
	while (nl > 0)
	{
		nl /= 10;
		size++;
	}
	return (size);
}

char	*fill_array(char *ascii, long	*nl)
{
	ascii[0] = '-';
	*nl *= -1;
	return (ascii);
}

char	*ft_itoa(int n)
{
	long	nl;
	int		size;
	int		last;
	char	*ascii;

	nl = n;
	size = ft_size(nl);
	last = size;
	ascii = malloc((size * sizeof(char)) + 1);
	if (!ascii)
		return (NULL);
	if (nl < 0)
		fill_array(ascii, &nl);
	while (size > 0)
	{
		if (ascii[size - 1] == '-')
			break ;
		ascii[size - 1] = ((nl % 10) + '0');
		nl /= 10;
		size--;
	}
	ascii[last] = '\0';
	return (ascii);
}
// int main()
//  {
//      printf("Size: %d", ft_size(-423));
//      char    *itoa = ft_itoa(10);
//      printf("Itoa: %s\n", itoa);
// 	 free(itoa);
// }