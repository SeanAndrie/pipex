/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:12:14 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/20 22:05:48 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *type, char *message, char *exit_code)
{
	ft_putstr_fd(type, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(message, 2);
	if (exit_code)
		exit(ft_atoi(exit_code));
}

void	wait_for_children(t_pipex *px)
{
	int	i;
	int	status;

	i = 0;
	while (i < px->n_cmds)
	{
		wait(&status);
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
		return (0);
	free(cmd_path);
	free_array(args);
	return (1);
}

void	child_process(t_pipex *px, t_command *node, char **envp, int i)
{
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
		free_pipex(px);
		if (errno == ENOENT)
			error("pipex", "Command not found.", "127");
		else if (errno == EACCES)
			error("pipex", "Permission denied.", "126");
		else
			error("pipex", "Execution failed.", "1");
	}
}

void	run_pipex(t_pipex *px, char **envp)
{
	int			i;
	pid_t		pid;
	t_command	*curr;

	i = 0;
	curr = px->head;
	while (curr)
	{
		pid = fork();
		if (pid < 0)
		{
			free_pipex(px);
			error("pipex", "Fork failed", "1");
		}
		else if (pid == 0)
			child_process(px, curr, envp, i);
		curr = curr->next;
		i++;
	}
	close_pipes(px->pipes, px->n_cmds);
	wait_for_children(px);
}
