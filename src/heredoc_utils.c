/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 02:00:19 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/29 20:38:31 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	is_delim(char *line, char *limiter)
{
	size_t	limit_len;

	limit_len = ft_strlen(limiter);
	if ((ft_strlen(line) - 1) == ft_strlen(limiter))
	{
		return ((limiter[0] == '\0' || limiter[0] == '\n')
			|| (limiter[0] != '\0' && !ft_strncmp(line, limiter,
					limit_len)));
	}
	return (0);
}

int	process_heredoc(char *limiter)
{
	int		fd[2];
	char	*line;
	int		total_len;

	if (pipe(fd) == -1)
		return (-1);
	total_len = 0;
	while (total_len < MAX_HEREDOC_SIZE)
	{
		ft_putstr_fd("heredoc> ", STDERR_FILENO);
		line = get_next_line(STDERR_FILENO);
		if (!line)
			break ;
		if (is_delim(line, limiter) || total_len > MAX_HEREDOC_SIZE)
		{
			free(line);
			break ;
		}
		total_len += ft_strlen(line);
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}

void	normal_or_heredoc(t_pipex *px, int *ac, char ***av)
{
	if (!ft_strncmp((*av)[1], "here_doc", 9))
	{
		if (*ac <= 5)
			(free_pipex(px), exit_on_err("here_doc", "Insufficient arguments.",
					1));
		px->here_doc = process_heredoc((*av)[2]);
		if (px->here_doc == -1)
			exit_on_err("here_doc", "here_doc failed.", 1);
		*av += 3;
		*ac -= 3;
	}
	else
	{
		px->here_doc = -1;
		*av += 1;
		*ac -= 1;
	}
}
