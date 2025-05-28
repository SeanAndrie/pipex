/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:17:41 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/28 16:22:18 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	cleanup_fds(t_pipex *px, int free_px)
{
	if (px)
	{
		close_pipes(px);
		if (px->here_doc != -1)
		{
			close(px->here_doc);
			px->here_doc = -1;
		}
		if (free_px)
			free_pipex(px);
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
}

void	close_pipes(t_pipex *px)
{
	int	i;

	if (!px || !px->pipes)
		return ;
	i = -1;
	while (++i < px->n_cmds - 1)
	{
		if (px->pipes[i][0] != -1)
		{
			close(px->pipes[i][0]);
			px->pipes[i][0] = -1;
		}
		if (px->pipes[i][1] != -1)
		{
			close(px->pipes[i][1]);
			px->pipes[i][1] = -1;
		}
	}
}

void	*free_pipex(t_pipex *px)
{
	if (!px)
		return (NULL);
	if (px->infile)
		free(px->infile);
	if (px->outfile)
		free(px->outfile);
	if (px->head)
		free_commands(px->head);
	if (px->pipes)
	{
		close_pipes(px);
		free(px->pipes);
	}
	if (px->pipes)
		free(px->pids);
	free(px);
	return (NULL);
}

void	create_pipes(t_pipex *px)
{
	int	i;
	int	*fds;
	int	n_pipes;

	n_pipes = px->n_cmds - 1;
	px->pipes = malloc((sizeof(int *) * n_pipes) + (sizeof(int) * 2 * n_pipes));
	if (!px->pipes)
		return ;
	fds = (int *)(px->pipes + n_pipes);
	i = -1;
	while (++i < n_pipes)
	{
		px->pipes[i] = &fds[i * 2];
		if (pipe(px->pipes[i]) == -1)
		{
			close_pipes(px);
			free_pipex(px);
			return ;
		}
	}
}

t_pipex	*init_pipex(int ac, char **av)
{
	t_pipex	*px;

	px = ft_calloc(1, sizeof(t_pipex));
	if (!px)
		return (free_pipex(px));
	normal_or_heredoc(px, &ac, &av);
	if (px->here_doc == -1)
	{
		px->infile = ft_strdup(av[0]);
		if (!px->infile)
			return (free_pipex(px));
	}
	px->outfile = ft_strdup(av[ac - 1]);
	if (!px->outfile)
		return (free_pipex(px));
	px->head = create_commands(ac - 1, av + 1);
	if (!px->head)
		return (free_pipex(px));
	px->n_cmds = count_commands(px->head);
	create_pipes(px);
	if (!px->pipes)
		return (free_pipex(px));
	return (px);
}
