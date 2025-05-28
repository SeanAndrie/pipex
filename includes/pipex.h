/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:52:08 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/28 15:40:28 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <libft.h>
# include <stdarg.h>
# include <stdio.h>
# include <sys/wait.h>

# define STDIN_FILENO 0
# define STDOUT_FILENO 1
# define STDERR_FILENO 2
# define MAX_HEREDOC_SIZE 65536

typedef struct s_command
{
	char				*name;
	struct s_command	*next;
}						t_command;

typedef struct s_pipex
{
	char				*infile;
	char				*outfile;
	pid_t				*pids;
	int					n_cmds;
	int					**pipes;
	int					here_doc;
	int					last_exit;
	struct s_command	*head;
}						t_pipex;

// here_doc
void					cleanup_fds(t_pipex *px, int free_px);
void					normal_or_heredoc(t_pipex *px, int *ac, char ***av);

// Pipex Execution
void					parent_process(t_pipex *px, char **env);

// Pipex Utilities
t_pipex					*init_pipex(int ac, char **av);
void					*free_pipex(t_pipex *px);
void					create_pipes(t_pipex *px);
void					close_pipes(t_pipex *px);

// I/O Handling
void					set_infile(t_pipex *px);
void					set_outfile(t_pipex *px);

// Path Utilities
void					*free_tokens(char **tokens);
char					*find_cmd_path(char *cmd, char **env);

// Command Utilities
void					free_commands(t_command *head);
int						count_commands(t_command *head);
t_command				*create_commands(int ac, char **av);

// Debug
void					print_env(char **env);
void					print_pipex_attr(t_pipex *px);
void					print_commands(t_command *head);
void					exit_on_err(char *context, char *message, int code);

#endif
