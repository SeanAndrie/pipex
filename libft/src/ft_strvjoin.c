/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strvjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:50:09 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/27 18:21:30 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_total_len(int n, va_list args)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (++i < n)
		len += ft_strlen(va_arg(args, char *));
	return (len);
}

char	*ft_strvjoin(int n, char *sep, ...)
{
	int		i;
	char	*res;
	va_list	args;
	int		total_len;

	va_start(args, sep);
	total_len = get_total_len(n, args) + n - 1;
	res = ft_calloc(sizeof(char), (total_len + 1));
	if (!res)
		return (NULL);
	va_end(args);
	i = -1;
	va_start(args, sep);
	while (++i < n)
	{
		ft_strlcat(res, va_arg(args, char *), total_len + 1);
		if (i != n)
			ft_strlcat(res, sep, total_len + 1);
	}
	va_end(args);
	return (res);
}
