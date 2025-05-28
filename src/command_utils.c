/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:11:13 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/28 03:30:38 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static t_command	*create_command(char *name)
{
	t_command	*cmd;

	if (!name)
		return (NULL);
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->name = ft_strdup(name);
	if (!cmd->name)
		return (NULL);
	cmd->next = NULL;
	return (cmd);
}

static void	append_command(t_command **head, t_command *cmd)
{
	t_command	*last;

	if (!cmd)
		return ;
	if (!*head)
	{
		*head = cmd;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = cmd;
}

void	free_commands(t_command *head)
{
	t_command	*next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head);
		head = next;
	}
}

int	count_commands(t_command *head)
{
	int			count;
	t_command	*curr;

	if (!head)
		return (0);
	count = 0;
	curr = head;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	return (count);
}

t_command	*create_commands(int ac, char **av)
{
	t_command	*head;
	t_command	*cmd;
	int			i;

	i = 0;
	head = NULL;
	while (i < ac - 1)
	{
		if (!av[i] || !*av[i])
		{
			i++;
			continue ;
		}
		cmd = create_command(av[i]);
		if (!cmd)
			return (free_commands(head), NULL);
		append_command(&head, cmd);
		i++;
	}
	return (head);
}
