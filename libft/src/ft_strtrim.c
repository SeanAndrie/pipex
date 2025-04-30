/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:28:21 by sgadinga          #+#    #+#             */
/*   Updated: 2024/12/26 17:29:41 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(const char *set, int c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(const char *s, const char *set)
{
	const char	*start;
	const char	*end;
	char		*res;
	size_t		len;

	if (!s)
		return (NULL);
	if (!set)
		return (ft_strdup(s));
	start = s;
	while (*start && in_set(set, *start))
		start++;
	end = s + ft_strlen(s) - 1;
	while (end > start && in_set(set, *end))
		end--;
	len = end - start + 1;
	if (len == 0)
		return (ft_strdup(""));
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (len--)
		res[len] = start[len];
	return (res);
}
