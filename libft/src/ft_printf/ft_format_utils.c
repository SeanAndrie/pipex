/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:23:47 by sgadinga          #+#    #+#             */
/*   Updated: 2025/01/17 16:52:31 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_width_padding(int width, int length, int value)
{
	int	len;

	len = 0;
	while (width-- > length)
		len += ft_putchar_len(value);
	return (len);
}

int	ft_right_justify(t_formatspec *fs, int *total_len)
{
	int	len;

	len = 0;
	if (fs->width > *total_len && !ft_strchr(fs->flags, '-'))
	{
		if (ft_strchr(fs->flags, '0') && fs->precision < 0)
			len += ft_width_padding(fs->width, *total_len, '0');
		else
			len += ft_width_padding(fs->width, *total_len, ' ');
	}
	return (len);
}

int	ft_left_justify(t_formatspec *fs, int *total_len)
{
	int	len;

	len = 0;
	if (fs->width > *total_len && ft_strchr(fs->flags, '-'))
		len += ft_width_padding(fs->width, *total_len, ' ');
	return (len);
}

void	ft_set_hex_n(t_formatspec *fs, void *ptr, unsigned long *n)
{
	if (fs->specifier == 'x' || fs->specifier == 'X')
		*n = (unsigned int)(unsigned long)ptr;
	else if (fs->specifier == 'p')
		*n = (unsigned long)ptr;
}

void	ft_set_hex_str(t_formatspec *fs, char **hex_str, unsigned long n)
{
	if (fs->specifier == 'p' && n == 0)
		*hex_str = ft_strdup(NULLPTR);
	else
		*hex_str = ft_gethex_str(n, ft_get_base(fs));
}
