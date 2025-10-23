/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:37:21 by xiribar           #+#    #+#             */
/*   Updated: 2025/10/04 14:37:21 by xiribar          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char    f(unsigned int index, char c)
// {
//    if (index == 1000000)
//     return (c);
//    return (c += 32);
// }

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*string_f;
	char	*string_temp;
	int		index;
	int		len;

	index = 0;
	len = ft_strlen(s);
	string_f = malloc(len + 1);
	if (!string_f)
		return (NULL);
	string_temp = string_f;
	while (s[index])
	{
		*string_f = f(index, s[index]);
		string_f++;
		index++;
	}
	*string_f = '\0';
	return (string_temp);
}
// int main()
// {
//     char *str = "ABCDEF";
//     char    *new = ft_strmapi(str, f);
//     printf("%s\n", new);
// }