/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:16:51 by sgadinga          #+#    #+#             */
/*   Updated: 2024/12/29 13:30:24 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s != '\0')
	{
		if (*s != c && in_word == 0)
		{
			count++;
			in_word = 1;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*alloc_word(const char **s, char c)
{
	const char	*start;
	int			len;
	char		*word;

	len = 0;
	while (**s && **s == c)
		(*s)++;
	start = *s;
	while (**s && **s != c)
	{
		(*s)++;
		len++;
	}
	word = ft_calloc(len + 1, sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, start, len + 1);
	return (word);
}

static void	*free_splits(char **splits, int i)
{
	while (--i >= 0)
		free(splits[i]);
	free(splits);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**splits;
	int		i;

	if (!s)
		return (NULL);
	splits = (char **)ft_calloc(count_words(s, c) + 1, sizeof(char *));
	if (!splits)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s != '\0')
		{
			splits[i] = alloc_word(&s, c);
			if (!splits[i])
				return (free_splits(splits, i));
			i++;
		}
	}
	return (splits);
}
