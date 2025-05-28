/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:14:56 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/27 23:18:05 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	*free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return (NULL);
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
	return (NULL);
}

static char	*find_path_var(char **env)
{
	while (*env)
	{
		if (!ft_strncmp("PATH=", *env, 5))
			return (ft_strdup(*env + 5));
		env++;
	}
	return (NULL);
}

char	*find_cmd_path(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*path_var;
	char	*cmd_path;

	if (!cmd || !*cmd || !env || !*env)
		return (NULL);
	path_var = find_path_var(env);
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	free(path_var);
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		cmd_path = ft_strvjoin(2, "/", paths[i], cmd);
		if (!cmd_path)
			return (free_tokens(paths));
		if (!access(cmd_path, X_OK))
			return (free_tokens(paths), cmd_path);
		free(cmd_path);
	}
	return (free_tokens(paths));
}
