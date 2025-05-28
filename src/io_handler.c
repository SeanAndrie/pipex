/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:31:16 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/28 16:20:21 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	set_infile(t_pipex *px)
{
	int	fd;

	if (px->here_doc != -1)
		fd = dup(px->here_doc);
	else
		fd = open(px->infile, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror(px->infile);
		fd = open("/dev/null", O_RDONLY);
		if (fd < 0)
		{
			cleanup_fds(px, 1);
			exit_on_err("dup2", "/dev/null fallback failed.", 1);
		}
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		cleanup_fds(px, 1);
		exit_on_err("dup2", "infile failed.", 1);
	}
	if (px->here_doc == -1)
		close(fd);
}

void	set_outfile(t_pipex *px)
{
	int	fd;

	if (px->here_doc != -1)
		fd = open(px->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(px->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror(px->outfile);
		cleanup_fds(px, 1);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		cleanup_fds(px, 1);
		exit_on_err("dup2", "outfile failed.", 1);
	}
	close(fd);
}
