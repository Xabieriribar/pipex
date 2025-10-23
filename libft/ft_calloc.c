/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:36:18 by xiribar           #+#    #+#             */
/*   Updated: 2025/10/01 11:36:24 by xiribar          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*allocated;
	unsigned int	i;

	i = 0;
	allocated = malloc(nmemb * size);
	if (!allocated)
		return (NULL);
	while (i < nmemb * size)
		allocated[i++] = 0;
	return (allocated);
}

// int main()
// {
// 	void *str1 = calloc(0,0);
// 	if (str1 == NULL)
// 		return (printf("it failed"));
// 	void *str = ft_calloc(0,0);
// 	if (str == NULL)
// 		return (printf("mine failed"));
// }