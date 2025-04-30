/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:51:05 by sgadinga          #+#    #+#             */
/*   Updated: 2024/12/18 13:45:50 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	s_len;
	char	*res;

	if (!s)
		return (NULL);
	s_len = ft_strlen((char *)s);
	res = malloc(s_len + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s, s_len + 1);
	return (res);
}
