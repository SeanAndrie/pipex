/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 01:11:16 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/23 14:55:57 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
