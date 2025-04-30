/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:52:57 by sgadinga          #+#    #+#             */
/*   Updated: 2024/12/17 16:20:38 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	needle_len;

	if (!haystack || !needle)
		return (NULL);
	if (needle[0] == '\0')
		return ((char *)haystack);
	needle_len = ft_strlen(needle);
	if (needle_len > n)
		return (NULL);
	i = 0;
	while (haystack[i] && i <= n - needle_len)
	{
		j = 0;
		while (needle[j] && haystack[i + j] == needle[j])
		{
			if (needle[j + 1] == '\0')
				return ((char *)&haystack[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
