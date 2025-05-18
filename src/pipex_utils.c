/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:39:48 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/18 17:46:11 by sgadinga         ###   ########.fr       */
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

void	free_pipes(int **pipes, int n_cmds)
{
	int	i;

	i = 0;
	while (i < n_cmds - 1)
		free(pipes[i++]);
	free(pipes);
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
		free_pipes(px->pipes, px->n_cmds);
	free(px);
	return (NULL);
}

int	**create_pipes(int n_cmds)
{
	int	i;
	int	**pipes;

	pipes = malloc(sizeof(int *) * (n_cmds - 1));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < n_cmds - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) == -1)
			return (free_pipes(pipes, i + 1), NULL);
		i++;
	}
	return (pipes);
}

t_pipex	*init_pipex(int ac, char **av)
{
	t_pipex	*px;

	px = malloc(sizeof(t_pipex));
	if (!px)
		return (NULL);
	px->infile = open(av[1], O_RDONLY);
	if (px->infile < 0)
	{
		perror(av[1]);
		px->infile = open("/dev/null", O_RDONLY);
		if (px->infile < 0)
			error("infile", "/dev/null fallback failed.", "1");
	}
	px->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
