/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:57:04 by sgadinga          #+#    #+#             */
/*   Updated: 2024/12/25 21:00:16 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*b_d;
	unsigned char	*b_s;

	b_d = (unsigned char *)dest;
	b_s = (unsigned char *)src;
	while (n--)
		*b_d++ = *b_s++;
	return (dest);
}
