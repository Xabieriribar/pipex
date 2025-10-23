/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:10:31 by xiribar           #+#    #+#             */
/*   Updated: 2025/10/01 11:10:33 by xiribar          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
// int main()
// {
//     t_list  *temp; 
//     t_list  *new;

//     temp = ft_lstnew("hola");
//     new = ft_lstnew("adios");
//     ft_lstadd_back(&temp, new);
//     int size = ft_lstsize(temp);
//     printf("%d", size);
// }