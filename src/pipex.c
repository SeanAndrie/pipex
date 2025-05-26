/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 01:11:16 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/26 20:06:37 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*init_pipex(int ac, char **av)
{
	t_pipex	*px;

	px = ft_calloc(1, sizeof(t_pipex));
	if (!px)
		return (NULL);
	px->infile = open(av[1], O_RDONLY);
	if (px->infile < 0)
	{
		perror(av[1]);
		px->infile = open("/dev/null", O_RDONLY);
		if (!px->infile)
			error("pipex", "/dev/null fallback failed.", "1", px);
	}
	px->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (px->outfile < 0)
		return (perror(av[ac - 1]), free_pipex(px));
	px->head = create_cmd_list(ac, av);
	if (!px->head)
		return (free_pipex(px));
	px->n_cmds = count_cmds(px->head);
	px->pipes = create_pipes(px->n_cmds);
	if (!px->pipes)
		return (free_pipex(px));
	return (px);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	*px;
	int		status;

	if (!envp || !*envp)
		error("pipex", "Environment is not set.", "1", NULL);
	if (ac != 5)
		error("pipex", "usage: ./pipex infile cmd1 cmd2 outfile", "1", NULL);
	px = init_pipex(ac, av);
	if (!px)
		exit(1);
	run_pipex(px, envp);
	status = px->last_exit;
	free_pipex(px);
	exit(status);
}
