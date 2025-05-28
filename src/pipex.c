/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:51:50 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/28 14:44:48 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	main(int ac, char **av, char **env)
{
	t_pipex	*px;
	int		status;

	if (ac != 5)
		exit_on_err("usage", "./pipex infile cmd1 cmd2 outfile", 1);
	px = init_pipex(ac, av);
	if (!px)
		exit_on_err("init", "Initialization failed.", 1);
	parent_process(px, env);
	status = px->last_exit;
	free_pipex(px);
	exit(status);
}
