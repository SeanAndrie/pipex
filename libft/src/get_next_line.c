/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 21:09:19 by sgadinga          #+#    #+#             */
/*   Updated: 2025/03/31 15:25:45 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*alloc_line(t_list **head)
{
	char	*nl_pos;
	t_list	*curr;
	char	*line;
	size_t	len;

	if (!head || !*head)
		return (NULL);
	len = 0;
	curr = *head;
	while (curr)
	{
		nl_pos = ft_strchr(curr->buffer, '\n');
		if (nl_pos)
		{
			len += (nl_pos - curr->buffer) + 1;
			break ;
		}
		len += curr->length;
		curr = curr->next;
	}
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	line[len] = '\0';
	return (line);
}

char	*extract_line(t_list **head)
{
	t_list	*curr;
	char	*line;
	char	*ptr;
	char	*buffer;

	line = alloc_line(head);
	if (!line)
		return (NULL);
	curr = *head;
	ptr = line;
	while (curr)
	{
		buffer = curr->buffer;
		while (*buffer)
		{
			*ptr++ = *buffer;
			if (*buffer == '\n')
				return (*ptr = '\0', line);
			buffer++;
		}
		curr = curr->next;
	}
	*ptr = '\0';
	return (line);
}

int	is_newline(t_list *head)
{
	while (head && head->next)
		head = head->next;
	return (head && ft_strchr(head->buffer, '\n'));
}

void	read_line(t_list **head, int fd)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return ;
	while (!is_newline(*head))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			clear_list(head);
			return ;
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		append_node(head, buffer);
	}
	free(buffer);
}

char	*get_next_line(int fd)
{
	static t_list	*remain;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	read_line(&remain, fd);
	line = extract_line(&remain);
	if (!line)
		return (NULL);
	update_remainder(&remain);
	return (line);
}
