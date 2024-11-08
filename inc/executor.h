/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:42:25 by lgandari          #+#    #+#             */
/*   Updated: 2024/11/04 22:26:30 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

typedef struct s_command	t_command;

typedef struct s_multiple_cmds
{
	int		i;
	int		tube[2];
	pid_t	*pids;
}	t_multiple_cmds;

int				execute_builtin(t_shell *shell);
int				execute(t_shell *shell);
int				get_num_cmds(t_command *cmd_node);
int				open_files(t_command *cmd_node);
int				close_files(t_command *cmd_node);

int				handle_dup(int *std_fds);
int				restore_std_fds(int *std_fds);
int				handle_one_builtin(t_shell *shell);
void			execute_cmd(t_shell *shell);
int				handle_one_child_process(t_shell *shell, int *std_fds);
int				handle_one_cmd(t_shell *shell);
int				handle_multiple_cmds(t_shell *shell, t_command *cmd_node);

int				execution_failure(pid_t *pids);
int				wait_processes(t_shell *shell, pid_t *pids);
void			free_multiple_cmds(t_multiple_cmds *vars);
t_multiple_cmds	*init_multiple_cmds(t_shell *shell);

#endif