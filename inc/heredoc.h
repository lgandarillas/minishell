/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:31:48 by lgandari          #+#    #+#             */
/*   Updated: 2024/11/13 22:55:02 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

char	*create_filename(int temp_num);
bool	handle_heredoc(t_command *cmd, t_shell *shell);
void	delete_heredoc_files(t_command *cmd);
void	check_expand_heredoc(t_lexer *node, t_shell *shell);
int		handle_hd_eof(char *delimiter);
int		handle_hd_signal_status(char *line, t_shell *shell);

char	*expand_heredoc_line(char *line, t_shell *shell);

#endif
