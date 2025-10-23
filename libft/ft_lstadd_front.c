/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:34:25 by xiribar           #+#    #+#             */
/*   Updated: 2025/10/02 14:34:28 by xiribar          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new || !lst)
		return ;
	new->next = *lst;
	*lst = new;
}

// int main()
// {
//     t_list  *temp;
//     t_list  *lst;
//     t_list  *new;
//     lst = ft_lstnew("FIRST");
//     new = ft_lstnew("NEW");
//     ft_lstadd_front(&lst, new);
//     printf("%s", (char *)lst->content);
//     temp = lst->next;
//     printf("%s", (char *)temp->content);
// }