/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:55:43 by sgadinga          #+#    #+#             */
/*   Updated: 2025/01/16 03:51:09 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_len(char *s)
{
	int	s_len;

	if (!s)
		s = "(null)";
	s_len = (int)ft_strlen(s);
	write(1, s, s_len);
	return (s_len);
}

int	ft_parse_str(t_formatspec *fs, char *s)
{
	int	len;
	int	str_len;
	int	n_char;

	if (!s)
	{
		if (fs->precision < 5 && fs->precision > -1)
			s = "\0";
		else
			s = "(null)";
	}
	str_len = (int)ft_strlen(s);
	if (fs->precision >= 0 && fs->precision < str_len)
		n_char = fs->precision;
	else
		n_char = str_len;
	len = 0;
	if (fs->width > n_char && !ft_strchr(fs->flags, '-'))
		len += ft_width_padding(fs->width, n_char, ' ');
	write(1, s, n_char);
	len += n_char;
	if (fs->width > n_char && ft_strchr(fs->flags, '-'))
		len += ft_width_padding(fs->width, n_char, ' ');
	return (len);
}
