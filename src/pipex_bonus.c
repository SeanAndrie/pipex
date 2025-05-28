/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:31:33 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/28 14:57:46 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	main(int ac, char **av, char **env)
{
	t_pipex	*px;
	int		status;

	if (ac < 5)
	{
		ft_putstr_fd("pipex: usage:\n./pipex infile cmd1 cmd2 ... outfile\n",
			2);
		ft_putstr_fd("or\n./pipex here_doc LIMITER cmd1 ... outfile\n", 2);
		exit(1);
	}
	px = init_pipex(ac, av);
	if (!px)
		exit_on_err("init", "Initialization failed.", 1);
	parent_process(px, env);
	status = px->last_exit;
	free_pipex(px);
	exit(status);
}
