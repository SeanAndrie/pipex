/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:23:34 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/26 11:55:08 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*free_array(char **array)
{
	int	i;

	if (!array)
		return (NULL);
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	return (NULL);
}

char	*ft_strjoinv(int n, ...)
{
	int		i;
	char	*res;
	va_list	args;
	size_t	total_len;

	if (n <= 0)
		return (NULL);
	va_start(args, n);
	total_len = 0;
	i = -1;
	while (++i < n)
		total_len += ft_strlen(va_arg(args, char *));
	va_end(args);
	res = malloc(total_len + 1);
	if (!res)
		return (NULL);
	res[0] = '\0';
	va_start(args, n);
	i = -1;
	while (++i < n)
		ft_strlcat(res, va_arg(args, char *), total_len + 1);
	va_end(args);
	return (res);
}

char	*find_path(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_strdup(envp[i] + 5));
	}
	return (NULL);
}

char	*find_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	**array;
	char	*full_path;

	if (!cmd || !envp)
		return (NULL);
	path = find_path(envp);
	if (!path)
		return (NULL);
	array = ft_split(path, ':');
	free(path);
	if (!array)
		return (NULL);
	i = -1;
	while (array[++i])
	{
		full_path = ft_strjoinv(3, array[i], "/", cmd);
		if (!full_path)
			return (free_array(array));
		if (access(full_path, X_OK) == 0)
			return (free_array(array), full_path);
		free(full_path);
	}
	return (free_array(array));
}
