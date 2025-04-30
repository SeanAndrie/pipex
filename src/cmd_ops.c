/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:24:08 by sgadinga          #+#    #+#             */
/*   Updated: 2025/04/15 17:04:51 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_cmds(t_command *head)
{
	t_command	*next;

	while (head)
	{
		next = head->next;
		free(head->cmd);
		free(head);
		head = next;
	}
}

t_command	*create_cmd(char *cmd)
{
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->cmd = ft_strdup(cmd);
	if (!node->cmd)
		return (free(node), NULL);
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	append_cmd(t_command **head, char *cmd)
{
	t_command	*last;
	t_command	*node;

	node = create_cmd(cmd);
	if (!node)
		return ;
	if (!*head)
	{
		*head = node;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = node;
	node->prev = last;
}

int	count_cmds(t_command *head)
{
	int	count;

	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}

t_command	*create_cmd_list(int ac, char **av)
{
	int			i;
	t_command	*head;

	head = NULL;
	i = 2;
	while (i < ac - 1)
	{
		append_cmd(&head, av[i]);
		i++;
	}
	return (head);
}
