/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:54:42 by sgadinga          #+#    #+#             */
/*   Updated: 2024/12/25 21:09:20 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long	nbr;
	char	*res;
	int		n_digits;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	nbr = n;
	n_digits = count_digits(n);
	res = (char *)malloc(n_digits + 1);
	if (!res)
		return (NULL);
	res[n_digits] = '\0';
	if (nbr < 0)
	{
		res[0] = '-';
		nbr = -nbr;
	}
	while (nbr > 0)
	{
		res[(n_digits--) - 1] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (n == 0)
		res[0] = '0';
	return (res);
}
