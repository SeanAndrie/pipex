/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:49:10 by sgadinga          #+#    #+#             */
/*   Updated: 2025/01/17 16:45:43 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putuint_len(unsigned int n)
{
	int	len;

	len = 0;
	if (n / 10 > 0)
		len += ft_putuint_len(n / 10);
	len += ft_putchar_len(n % 10 + '0');
	return (len);
}

static int	ft_count_digits_unsigned(unsigned int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

int	ft_parse_uint(t_formatspec *fs, unsigned int n)
{
	int	len;
	int	n_digits;
	int	total_len;

	len = 0;
	n_digits = ft_count_digits_unsigned(n);
	total_len = n_digits;
	if (fs->precision > n_digits)
		total_len += (fs->precision - n_digits);
	len += ft_right_justify(fs, &total_len);
	if (fs->precision > n_digits)
		len += ft_width_padding(fs->precision, n_digits, '0');
	if (!(n == 0 && fs->precision == 0))
		len += ft_putuint_len(n);
	else if (fs->precision == 0 && fs->width > 0)
		len += ft_putchar_len(' ');
	len += ft_left_justify(fs, &len);
	return (len);
}
