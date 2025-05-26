/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:12:14 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/26 20:38:07 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_for_children(t_pipex *px)
{
	int	i;
	int	status;

	i = 0;
	while (i < px->n_cmds)
	{
		waitpid(px->pids[i], &status, 0);
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
	if (!args || !args[0])
		return (free_array(args), 0);
	if (ft_strchr(args[0], '/'))
	{
		if (!access(args[0], X_OK))
			execve(args[0], args, envp);
		perror("access/execve");
		return (free_array(args), 0);
	}
	cmd_path = find_cmd_path(args[0], envp);
	if (!cmd_path)
		return (free_array(args), 0);
	if (execve(cmd_path, args, envp) == -1)
		return (perror("execve"), free_array(args), free(cmd_path), 0);
	return (1);
}

void	setup_redirections(t_pipex *px, int i)
{
	if (i == 0)
	{
		if (dup2(px->infile, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
	else
	{
		if (dup2(px->pipes[i - 1][0], STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
	if (i < px->n_cmds - 1)
	{
		if (dup2(px->pipes[i][1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);	
	}
	else
	{
		if (dup2(px->outfile, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
}

void	child_process(t_pipex *px, t_command *node, char **envp, int i)
{
	setup_redirections(px, i);
	close_files(&px->infile, &px->outfile);
	close_pipes(px->pipes, px->n_cmds);
	if (!execute_w_execve(node->cmd, envp))
	{
		if (errno == ENOENT)
			error("pipex", "Command not found.", "127", px);
		else if (errno == EACCES)
			error("pipex", "Permission denied.", "126", px);
		else
			error("pipex", "Execution failed.", "1", px);
	}
}

void	run_pipex(t_pipex *px, char **envp)
{
	int			i;
	t_command	*curr;

	px->pids = malloc(sizeof(pid_t) * px->n_cmds);
	if (!px->pids)
		error("pipex", "malloc failed.", "1", px);
	i = 0;
	curr = px->head;
	while (curr)
	{
		px->pids[i] = fork();
		if (px->pids[i] < 0)
			error("pipex", "fork failed", "1", px);
		else if (px->pids[i] == 0)
			child_process(px, curr, envp, i);
		curr = curr->next;
		i++;
	}
	close_files(&px->infile, &px->outfile);
	close_pipes(px->pipes, px->n_cmds);
	wait_for_children(px);
}
