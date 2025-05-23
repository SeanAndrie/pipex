/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 01:21:33 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/23 15:05:22 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/ft_printf.h"
# include <errno.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	struct s_command	*head;
	int					n_cmds;
	int					infile;
	int					outfile;
	int					**pipes;
	int					last_exit;
}						t_pipex;

typedef struct s_command
{
	char				*cmd;

	struct s_command	*prev;
	struct s_command	*next;
}						t_command;

void					error(char *type, char *message, char *exit_code,
							t_pipex *px);

// here_doc
int						process_heredoc(char *limiter);
void					normal_or_heredoc(t_pipex *px, int *ac, char ***av);

// Pipe Execution
void					run_pipex(t_pipex *px, char **envp);

// Command Operations
int						count_cmds(t_command *head);
void					free_cmds(t_command *head);
t_command				*create_cmd_list(int ac, char **av);

// Pipex Utilies
void					free_pipes(int **pipes, int n_cmds);
void					close_pipes(int **pipes, int n_cmds);
void					*free_pipex(t_pipex *px);
t_pipex					*init_pipex(int ac, char **av);

// Path Utilities
void					*free_array(char **array);
char					*find_path(char **envp);
char					*ft_strjoinv(int n, ...);
char					*find_cmd_path(char *cmd, char **envp);

#endif
