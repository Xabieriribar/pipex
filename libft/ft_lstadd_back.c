/* ************************************************************************** */
/*                                                                            */
/*          :::      ::::::::   */ /*   ft_strlcat.c    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:34:25 by xiribar           #+#    #+#             */
/*   Updated: 2025/10/02 14:34:28 by xiribar          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_node;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_node = ft_lstlast(*lst);
	last_node->next = new;
}
// int main()
// {
//     t_list  *temp;
//     t_list  *lst;
//     t_list  *new;
//     lst = ft_lstnew("LAST");
//     new = ft_lstnew("NEW");
//     ft_lstadd_back(&lst, new);
//     printf("%s", (char *)lst->content);
//     temp = lst->next;
//     printf("%s", (char *)temp->content);
// }