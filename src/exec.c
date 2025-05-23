/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:12:14 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/23 15:25:29 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	wait_for_children(t_pipex *px, pid_t *pids)
{
	int	i;
	int	status;

	i = 0;
	while (i < px->n_cmds)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			px->last_exit = WEXITSTATUS(status);
		i++;
	}
}

int	execute_w_execve(char *cmd, char **envp)
{
	char	**args;
	char	*cmd_path;

	if (!cmd || !envp)
		return (0);
	args = ft_split(cmd, ' ');
	if (!args)
		return (0);
	cmd_path = find_cmd_path(args[0], envp);
	if (!cmd_path)
	{
		free_array(args);
		return (0);
	}
	if (execve(cmd_path, args, envp) == -1)
		return (free(cmd_path), free_array(args), 0);
	return (free(cmd_path), free_array(args), 1);
}

void	child_process(t_pipex *px, t_command *node, char **envp, int i)
{
	int	err;

	if (i == 0)
		dup2(px->infile, STDIN_FILENO);
	else
		dup2(px->pipes[i - 1][0], STDIN_FILENO);
	if (i < px->n_cmds - 1)
		dup2(px->pipes[i][1], STDOUT_FILENO);
	else
		dup2(px->outfile, STDOUT_FILENO);
	close_pipes(px->pipes, px->n_cmds);
	if (!execute_w_execve(node->cmd, envp))
	{
		err = errno;
		if (err == ENOENT)
			error("pipex", "Command not found.", "127", px);
		else if (err == EACCES)
			error("pipex", "Permission denied.", "126", px);
		else
			error("pipex", "Execution failed.", "1", px);
	}
}

void	run_pipex(t_pipex *px, char **envp)
{
	int			i;
	t_command	*curr;
	pid_t		*pids;

	pids = malloc(sizeof(pid_t) * px->n_cmds);
	if (!pids)
		error("pipex", "PID array malloc failed.", "1", px);
	i = 0;
	curr = px->head;
	while (curr)
	{
		pids[i] = fork();
		if (pids[i] < 0)
		{
			free(pids);
			error("pipex", "Fork failed", "1", px);
		}
		else if (pids[i] == 0)
			child_process(px, curr, envp, i);
		curr = curr->next;
		i++;
	}
	close_pipes(px->pipes, px->n_cmds);
	wait_for_children(px, pids);
	free(pids);
}
