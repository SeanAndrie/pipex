/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:52:28 by sgadinga          #+#    #+#             */
/*   Updated: 2024/12/19 11:36:48 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*b_s;

	b_s = (unsigned char *)s;
	while (n--)
	{
		if (*b_s == (unsigned char)c)
			return ((void *)b_s);
		b_s++;
	}
	return (NULL);
}
