/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 02:07:10 by sgadinga          #+#    #+#             */
/*   Updated: 2025/03/12 17:16:09 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"

# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>

# if defined(__linux__)
#  define NULLPTR "(nil)"
# elif defined(__APPLE__)
#  define NULLPTR "0x0"
# endif

# define HEX_UPR "0123456789ABCDEF"
# define HEX_LWR "0123456789abcdef"

typedef struct s_formatspec
{
	char		flags[6];
	int			width;
	int			precision;
	char		specifier;
}				t_formatspec;

int				ft_printf(const char *format, ...);

// ft_format_spec
int				ft_isflag(int c);
int				ft_isspec(int c);
t_formatspec	*ft_create_fs(const char **format);

// ft_format_parsers
void			ft_parse_flags(const char **format, t_formatspec *fs);
void			ft_parse_width(const char **format, t_formatspec *fs);
void			ft_parse_precision(const char **format, t_formatspec *fs);
int				ft_parse_specifier(const char **format, t_formatspec *fs);
void			ft_remove_flag(t_formatspec *fs, char flag);

// ft_format_utils
int				ft_width_padding(int width, int len, int value);
int				ft_right_justify(t_formatspec *fs, int *total_len);
int				ft_left_justify(t_formatspec *fs, int *total_len);
void			ft_set_hex_n(t_formatspec *fs, void *ptr, unsigned long *n);
void			ft_set_hex_str(t_formatspec *fs, char **hex_res,
					unsigned long n);

// ft_print_char
int				ft_putchar_len(int c);
int				ft_parse_char(t_formatspec *fs, int c);

// ft_print_str
int				ft_putstr_len(char *s);
int				ft_parse_str(t_formatspec *fs, char *s);

// ft_print_dec_int
int				ft_parse_dec_int(t_formatspec *fs, int n);

// ft_print_uint
int				ft_parse_uint(t_formatspec *fs, unsigned int n);

// ft_print_hex
char			*ft_get_base(t_formatspec *fs);
char			*ft_gethex_str(unsigned long n, char *base);
int				ft_parse_hex(t_formatspec *fs, void *ptr);

#endif
