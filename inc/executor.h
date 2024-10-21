/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:42:25 by lgandari          #+#    #+#             */
/*   Updated: 2024/10/16 21:17:17 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

typedef struct s_command	t_command;

int	execute_builtin(t_shell *shell);
int	execute(t_shell *shell);
int	total_commands(t_command *cmd_node);
int	open_files(t_command *cmd_node);
int	close_files(t_command *cmd_node);

int		handle_dup(int *std_fds);
int		restore_std_fds(int *std_fds);
int		handle_one_builtin(t_shell *shell);
void	execute_cmd(t_shell *shell);
int		handle_one_child_process(t_shell *shell, int *std_fds);
int		handle_one_cmd(t_shell *shell);

#endif