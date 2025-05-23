/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 03:29:05 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/23 23:30:15 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(int **pipes, int n_cmds)
{
	int	i;

	i = 0;
	while (i < n_cmds - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	*free_pipex(t_pipex *px)
{
	if (px->infile >= 0)
		close(px->infile);
	if (px->outfile >= 0)
		close(px->outfile);
	if (px->head)
		free_cmds(px->head);
	if (px->pipes)
		free(px->pipes);
	free(px);
	return (NULL);
}

int	**create_pipes(int n_cmds)
{
	int	i;
	int	*fds;
	int	**pipes;

	pipes = malloc(sizeof(int *) * (n_cmds - 1) + sizeof(int) * 2 * (n_cmds
				- 1));
	if (!pipes)
		return (NULL);
	fds = (int *)(pipes + (n_cmds - 1));
	i = -1;
	while (++i < (n_cmds - 1))
	{
		pipes[i] = &fds[i * 2];
		if (pipe(pipes[i]) == -1)
			return (free(pipes), NULL);
	}
	return (pipes);
}

t_pipex	*init_pipex(int ac, char **av)
{
	t_pipex	*px;

	px = malloc(sizeof(t_pipex));
	if (!px)
		return (NULL);
	normal_or_heredoc(px, &ac, &av);
	if (px->infile < 0)
	{
		perror(av[1]);
		px->infile = open("/dev/null", O_RDONLY);
		if (px->infile < 0)
			return (perror("/dev/null"), free_pipex(px));
	}
	if (px->outfile < 0)
		return (perror(av[ac - 1]), free_pipex(px));
	px->head = create_cmd_list(ac, av);
	if (!px->head)
		return (free_pipex(px));
	px->last_exit = 0;
	px->n_cmds = count_cmds(px->head);
	px->pipes = create_pipes(px->n_cmds);
	if (!px->pipes)
		return (free_pipex(px));
	return (px);
}
