/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_parsers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:46:25 by sgadinga          #+#    #+#             */
/*   Updated: 2025/01/16 12:07:44 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_parse_flags(const char **format, t_formatspec *fs)
{
	int	flag_i;

	flag_i = 0;
	while (ft_isflag(**format) && flag_i < 5)
	{
		if (!ft_strchr(fs->flags, **format))
			fs->flags[flag_i++] = **format;
		(*format)++;
	}
	fs->flags[flag_i] = '\0';
}

void	ft_parse_width(const char **format, t_formatspec *fs)
{
	while (ft_isdigit(**format))
		fs->width = fs->width * 10 + *(*format)++ - '0';
}

void	ft_parse_precision(const char **format, t_formatspec *fs)
{
	if (**format == '.')
	{
		(*format)++;
		fs->precision = 0;
		if (ft_isdigit(**format))
		{
			while (ft_isdigit(**format))
				fs->precision = fs->precision * 10 + *(*format)++ - '0';
		}
	}
}

int	ft_parse_specifier(const char **format, t_formatspec *fs)
{
	if (ft_isspec(**format))
	{
		fs->specifier = **format;
		return (1);
	}
	return (0);
}

void	ft_remove_flag(t_formatspec *fs, char flag)
{
	char	*flag_pos;

	flag_pos = ft_strchr(fs->flags, flag);
	if (flag_pos)
		ft_memmove(flag_pos, flag_pos + 1, ft_strlen(flag_pos));
}
