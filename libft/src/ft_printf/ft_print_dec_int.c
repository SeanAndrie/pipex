/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_dec_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:23:39 by sgadinga          #+#    #+#             */
/*   Updated: 2025/01/17 16:45:18 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putdi_len(int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
		return (ft_putstr_len("2147483648"));
	if (n < 0)
		n = -n;
	if (n / 10 > 0)
		len += ft_putdi_len(n / 10);
	len += ft_putchar_len(n % 10 + '0');
	return (len);
}

static int	ft_count_digits_signed(int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
		n = -n;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static int	ft_apply_sign(t_formatspec *fs, int n)
{
	if (n < 0)
		return (ft_putchar_len('-'));
	else if (ft_strchr(fs->flags, '+'))
		return (ft_putchar_len('+'));
	else if (ft_strchr(fs->flags, ' ') && n >= 0)
		return (ft_putchar_len(' '));
	return (0);
}

static int	ft_pad_and_justify(t_formatspec *fs, int n, int n_digits,
		int total_len)
{
	int	len;

	len = 0;
	if (ft_strchr(fs->flags, '0') && fs->precision < 0 && !ft_strchr(fs->flags,
			'-'))
	{
		len += ft_apply_sign(fs, n);
		len += ft_width_padding(fs->width, total_len, '0');
	}
	else
	{
		len += ft_right_justify(fs, &total_len);
		len += ft_apply_sign(fs, n);
	}
	if (fs->precision > n_digits)
		len += ft_width_padding(fs->precision, n_digits, '0');
	if (!(n == 0 && fs->precision == 0))
		len += ft_putdi_len(n);
	else if (fs->precision == 0 && fs->width > 0)
		len += ft_putchar_len(' ');
	len += ft_left_justify(fs, &total_len);
	return (len);
}

int	ft_parse_dec_int(t_formatspec *fs, int n)
{
	int	len;
	int	n_digits;
	int	total_len;

	if (n == INT_MIN)
		return (ft_putstr_len("-2147483648"));
	len = 0;
	n_digits = ft_count_digits_signed(n);
	total_len = n_digits;
	if (fs->precision > n_digits)
		total_len += (fs->precision - n_digits);
	if (n < 0 || ft_strchr(fs->flags, '+'))
		total_len++;
	len += ft_pad_and_justify(fs, n, n_digits, total_len);
	return (len);
}
