/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 09:47:38 by xiribar           #+#    #+#             */
/*   Updated: 2025/10/04 09:47:39 by xiribar          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_split(char **strs, size_t used)
{
	size_t	index;

	index = 0;
	while (index < used)
	{
		free(strs[index]);
		index++;
	}
	free(strs);
}

size_t	count_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s == '\0')
			break ;
		count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

char	*dup_word(char const *start, size_t len)
{
	char	*word;
	size_t	index;

	word = malloc(len + 1);
	if (!word)
		return (NULL);
	index = 0;
	while (index < len)
	{
		word[index] = start[index];
		index++;
	}
	word[index] = '\0';
	return (word);
}

int	extract_word(char const **s, char c, char **slot)
{
	size_t		len;
	char const	*start;

	while (**s && **s == c)
		(*s)++;
	if (**s == '\0')
		return (0);
	start = *s;
	len = 0;
	while ((*s)[len] && (*s)[len] != c)
		len++;
	*slot = dup_word(start, len);
	if (!*slot)
		return (-1);
	*s += len;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char		**strs;
	size_t		i;
	size_t		words;
	int			status;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	strs = malloc((words + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	i = 0;
	while (i < words)
	{
		status = extract_word(&s, c, &strs[i]);
		if (status < 0)
			return (free_split(strs, i), NULL);
		if (status == 0)
			break ;
		i++;
	}
	strs[i] = NULL;
	return (strs);
}
