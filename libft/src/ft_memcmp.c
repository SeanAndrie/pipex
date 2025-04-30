/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:43:54 by sgadinga          #+#    #+#             */
/*   Updated: 2024/12/18 14:32:43 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*b_s1;
	const unsigned char	*b_s2;

	b_s1 = (const unsigned char *)s1;
	b_s2 = (const unsigned char *)s2;
	while (n--)
	{
		if (*b_s1 != *b_s2)
			return (*b_s1 - *b_s2);
		b_s1++;
		b_s2++;
	}
	return (0);
}
