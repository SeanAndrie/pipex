/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 23:04:48 by sgadinga          #+#    #+#             */
/*   Updated: 2025/01/17 16:49:49 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_gethex_str(unsigned long n, char *base)
{
	int		i;
	char	*res;
	char	*ret;

	if (n == 0)
		return (ft_strdup("0"));
	res = ft_calloc(17, sizeof(char));
	if (!res)
		return (NULL);
	i = 15;
	while (n > 0)
	{
		res[i--] = base[n % 16];
		n /= 16;
	}
	ret = ft_strdup(&res[i + 1]);
	free(res);
	return (ret);
}

static int	ft_apply_prefix(t_formatspec *fs, unsigned long n)
{
	int	len;

	len = 0;
	if ((fs->specifier == 'p' || ft_strchr(fs->flags, '#')) && n != 0)
	{
		if (fs->specifier == 'p' || fs->specifier == 'x')
			len += ft_putstr_len("0x");
		else if (fs->specifier == 'X')
			len += ft_putstr_len("0X");
	}
	return (len);
}

char	*ft_get_base(t_formatspec *fs)
{
	if (fs->specifier == 'p' || fs->specifier == 'x')
		return (HEX_LWR);
	else
		return (HEX_UPR);
}

static int	ft_pad_and_justify(t_formatspec *fs, unsigned long n, int n_char,
		int total_len)
{
	int	len;

	len = 0;
	if (fs->specifier == 'p' && n == 0)
		total_len = ft_strlen(NULLPTR);
	len += ft_right_justify(fs, &total_len);
	if (n != 0 || fs->specifier == 'p')
		len += ft_apply_prefix(fs, n);
	if (fs->precision > n_char)
		len += ft_width_padding(fs->precision, n_char, '0');
	return (len);
}

int	ft_parse_hex(t_formatspec *fs, void *ptr)
{
	int				len;
	char			*hex_str;
	unsigned long	n;
	int				n_char;
	int				total_len;

	len = 0;
	ft_set_hex_n(fs, ptr, &n);
	ft_set_hex_str(fs, &hex_str, n);
	n_char = ft_strlen(hex_str);
	total_len = n_char;
	if (fs->precision > n_char)
		total_len += (fs->precision - n_char);
	if (fs->specifier == 'p' || (ft_strchr(fs->flags, '#') && n != 0))
		total_len += 2;
	len += ft_pad_and_justify(fs, n, n_char, total_len);
	if (!(n == 0 && fs->precision == 0))
		len += ft_putstr_len(hex_str);
	else if (fs->precision == 0 && fs->width > 0)
		len += ft_putchar_len(' ');
	if (fs->specifier == 'p' && n == 0)
		total_len = ft_strlen(NULLPTR);
	len += ft_left_justify(fs, &total_len);
	free(hex_str);
	return (len);
}
