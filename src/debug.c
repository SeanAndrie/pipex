/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:24:28 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/28 01:35:55 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	exit_on_err(char *context, char *message, int code)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	if (context)
	{
		ft_putstr_fd(context, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(message, STDERR_FILENO);
	if (code >= 0)
		exit(code);
}

void	print_commands(t_command *head)
{
	t_command	*curr;

	if (!head)
		return ;
	curr = head;
	while (curr)
	{
		ft_printf("%s", curr->name);
		curr = curr->next;
		if (curr)
			ft_printf(" | ");
	}
	ft_printf("\n");
}

void	print_env(char **env)
{
	if (!env || !*env)
		return ;
	ft_printf("---- ENV VARIABLES ----\n");
	while (*env)
		ft_putendl_fd(*env++, 1);
}

void	print_pipex_attr(t_pipex *px)
{
	if (!px)
		return ;
	ft_printf("---- PIPEX ATTRIBUTES ----\n");
	ft_printf("infile:  %-s\n", px->infile);
	ft_printf("outfile: %-s\n", px->outfile);
	ft_printf("n_cmds:  %-d\n", px->n_cmds);
	ft_printf("command list: ");
	print_commands(px->head);
}
