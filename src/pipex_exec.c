/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:42:08 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/29 20:47:29 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	wait_for_children(t_pipex *px)
{
	int	i;
	int	status;

	i = -1;
	while (++i < px->n_cmds)
	{
		waitpid(px->pids[i], &status, 0);
		if (WIFEXITED(status))
			px->last_exit = WEXITSTATUS(status);
	}
}

int	exec_w_execve(char *cmd, char **env)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(cmd, ' ');
	if (!args)
		return (0);
	if (!*args)
		return (free_tokens(args), 0);
	if (ft_strchr(*args, '/'))
	{
		if (access(*args, X_OK) == -1)
			return (errno = ENOENT, free_tokens(args), 0);
		execve(*args, args, env);
		return (free_tokens(args), 0);
	}
	cmd_path = find_cmd_path(*args, env);
	if (!cmd_path)
		return (errno = ENOENT, free_tokens(args), 0);
	execve(cmd_path, args, env);
	return (free(cmd_path), free_tokens(args), 0);
}

void	set_redirections(t_pipex *px, int curr_i)
{
	if (curr_i == 0)
		set_infile(px);
	else
	{
		if (dup2(px->pipes[curr_i - 1][0], STDIN_FILENO) == -1)
			(cleanup_fds(px, 1), exit_on_err("dup2", "read failed.", 1));
	}
	if (curr_i < px->n_cmds - 1)
	{
		if (dup2(px->pipes[curr_i][1], STDOUT_FILENO) == -1)
			(cleanup_fds(px, 1), exit_on_err("dup2", "write failed.", 1));
	}
	else
		set_outfile(px);
}

void	create_child(t_pipex *px, char *cmd, char **env, int curr_i)
{
	set_redirections(px, curr_i);
	close_pipes(px);
	if (px->here_doc != -1)
		(close(px->here_doc), px->here_doc = -1);
	if (!exec_w_execve(cmd, env))
	{
		cleanup_fds(px, 1);
		if (errno == ENOENT)
			exit_on_err(NULL, "Command not found.", 127);
		else if (errno == EACCES)
			exit_on_err(NULL, "Permission denied.", 126);
		exit(1);
	}
}

void	parent_process(t_pipex *px, char **env)
{
	int			i;
	t_command	*curr;

	px->pids = ft_calloc(px->n_cmds, sizeof(pid_t));
	if (!px->pids)
		return ;
	i = 0;
	curr = px->head;
	while (curr)
	{
		px->pids[i] = fork();
		if (px->pids[i] == -1)
		{
			free_pipex(px);
			exit_on_err(NULL, "fork failed.", 1);
		}
		if (px->pids[i] == 0)
			create_child(px, curr->name, env, i);
		curr = curr->next;
		i++;
	}
	cleanup_fds(px, 0);
	wait_for_children(px);
}
