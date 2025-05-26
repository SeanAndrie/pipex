/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:57:29 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/26 20:13:34 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(int **pipes, int n_cmds)
{
	int	i;

	i = 0;
	while (i < n_cmds - 1)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		i++;
	}
}

void	close_files(int *infile, int *outfile)
{
	if (*infile >= 0 && *infile != STDIN_FILENO)
		close(*infile);
	if (*outfile >= 0 && *outfile != STDOUT_FILENO)
		close(*outfile);
	*infile = -1;
	*outfile = -1;
}

void	*free_pipex(t_pipex *px)
{
	if (!px)
		return (NULL);
	close_files(&px->infile, &px->outfile);
	if (px->head)
		free_cmds(px->head);
	if (px->pipes)
		free(px->pipes);
	if (px->pids)
		free(px->pids);
	free(px);
	return (NULL);
}

void	error(char *type, char *message, char *exit_code, t_pipex *px)
{
	if (px)
		free_pipex(px);
	ft_putstr_fd(type, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(message, 2);
	if (exit_code)
		exit(ft_atoi(exit_code));
}

int	**create_pipes(int n_cmds)
{
	int	i;
	int	*fds;
	int	**pipes;

	pipes = malloc((sizeof(int *) * (n_cmds - 1)) + (sizeof(int) * 2 * (n_cmds
					- 1)));
	if (!pipes)
		return (NULL);
	fds = (int *)(pipes + (n_cmds - 1));
	i = -1;
	while (++i < (n_cmds - 1))
	{
		pipes[i] = &fds[i * 2];
		if (pipe(pipes[i]) == -1)
			return (close_pipes(pipes, i), free(pipes), NULL);
	}
	return (pipes);
}
