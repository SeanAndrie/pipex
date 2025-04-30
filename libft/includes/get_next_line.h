/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 21:09:32 by sgadinga          #+#    #+#             */
/*   Updated: 2025/03/31 15:19:51 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	char			*buffer;
	size_t			length;
	struct s_list	*next;
}					t_list;

char				*get_next_line(int fd);
char				*ft_strchr(const char *s, int c);
void				append_node(t_list **head, char *buffer);
void				update_remainder(t_list **head);
void				clear_list(t_list **head);

#endif