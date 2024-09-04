/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:31:48 by lgandari          #+#    #+#             */
/*   Updated: 2024/09/04 21:03:36 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

char	*create_filename(int temp_num);
void	handle_heredoc(t_command *cmd, t_shell *shell);
void	delete_heredoc_files(t_command *cmd);
void	check_expand_heredoc(t_lexer *node, t_shell *shell);

char	*expand_heredoc_line(char *line, t_shell *shell);

#endif
