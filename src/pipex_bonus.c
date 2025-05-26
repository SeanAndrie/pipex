/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 00:57:27 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/26 13:08:21 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	process_heredoc(char *limiter)
{
	int		fd[2];
	char	*line;
	size_t	limit_len;

	if (pipe(fd) == -1)
		error("pipex", "Failed to create pipe.", "1", NULL);
	limit_len = ft_strlen(limiter);
	ft_putstr_fd("heredoc> ", 2);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (!ft_strncmp(line, limiter, limit_len) && line[limit_len] == '\n')
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd[1]);
		free(line);
		ft_putstr_fd("heredoc> ", 2);
	}
	close(fd[1]);
	return (fd[0]);
}

void	normal_or_heredoc(t_pipex *px, int *ac, char ***av)
{
	if (!ft_strncmp((*av)[1], "here_doc", 9))
	{
		px->infile = process_heredoc((*av)[2]);
		px->outfile = open((*av)[*ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		*ac -= 2;
		*av += 2;
	}
	else
	{
		px->infile = open((*av)[1], O_RDONLY);
		px->outfile = open((*av)[*ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
}

t_pipex	*init_pipex(int ac, char **av)
{
	t_pipex	*px;

	px = ft_calloc(1, sizeof(t_pipex));
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
	if (ac < 5)
	{
		ft_putstr_fd("pipex: usage:\n./pipex infile cmd1 cmd2 ... outfile\n",
			2);
		ft_putstr_fd("or\n./pipex here_doc LIMITER cmd1 ... outfile\n", 2);
		exit(1);
	}
	px = init_pipex(ac, av);
	if (!px)
		exit(1);
	run_pipex(px, envp);
	status = px->last_exit;
	free_pipex(px);
	exit(status);
}
