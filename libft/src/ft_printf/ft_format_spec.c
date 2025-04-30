/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_spec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:31:40 by sgadinga          #+#    #+#             */
/*   Updated: 2025/01/17 17:21:08 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_isflag(int c)
{
	return (c == '-' || c == '+' || c == '0' || c == ' ' || c == '#');
}

int	ft_isspec(int c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X' || c == '%');
}

void	ft_apply_flag_precedence(t_formatspec *fs)
{
	if (ft_strchr(fs->flags, '-'))
		ft_remove_flag(fs, '0');
	if (ft_strchr(fs->flags, '+'))
		ft_remove_flag(fs, ' ');
	if (fs->precision >= 0 && ft_strchr("diuxX", fs->specifier))
		ft_remove_flag(fs, '0');
}

t_formatspec	*ft_init_fs(void)
{
	t_formatspec	*fs;

	fs = malloc(sizeof(t_formatspec));
	if (!fs)
		return (NULL);
	fs->width = 0;
	fs->precision = -1;
	fs->specifier = '\0';
	ft_bzero(&fs->flags, 5);
	return (fs);
}

t_formatspec	*ft_create_fs(const char **format)
{
	t_formatspec	*fs;

	fs = ft_init_fs();
	if (!fs)
		return (NULL);
	if (!format || !*format || **format == '\0')
	{
		free(fs);
		return (NULL);
	}
	ft_parse_flags(format, fs);
	ft_apply_flag_precedence(fs);
	ft_parse_width(format, fs);
	ft_parse_precision(format, fs);
	if (ft_parse_specifier(format, fs) == 0)
	{
		free(fs);
		return (NULL);
	}
	return (fs);
}
