/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:54:03 by sgadinga          #+#    #+#             */
/*   Updated: 2025/04/03 21:56:45 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_overflow(int n, char digit, int sign)
{
	int	next_digit;

	next_digit = digit - '0';
	if (sign == 1 && (n > INT_MAX / 10 || (n == INT_MAX / 10
				&& next_digit > INT_MAX % 10)))
		return (INT_MAX);
	if (sign == -1 && (n > -(INT_MIN / 10) || (n == -(INT_MIN / 10)
				&& next_digit > -(INT_MIN % 10))))
		return (INT_MIN);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	long	res;
	int		sign;
	int		check;

	res = 0;
	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr && ft_isdigit(*nptr))
	{
		check = check_overflow(res, *nptr, sign);
		if (check != 0)
			return (check);
		res = res * 10 + *nptr - '0';
		nptr++;
	}
	return ((int)(res * sign));
}
