/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:03:08 by sgadinga          #+#    #+#             */
/*   Updated: 2024/12/25 20:06:47 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*b_d;
	unsigned char	*b_s;

	b_d = (unsigned char *)dest;
	b_s = (unsigned char *)src;
	if (b_d < b_s || b_d >= b_s + n)
		ft_memcpy(dest, src, n);
	else
	{
		while (n--)
			*(b_d + n) = *(b_s + n);
	}
	return (dest);
}
