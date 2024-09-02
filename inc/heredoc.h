/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:31:48 by lgandari          #+#    #+#             */
/*   Updated: 2024/09/02 18:36:31 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

char	*create_filename(int temp_num);
void	handle_heredoc(t_command *cmd);
void	delete_heredoc_files(t_command *cmd);
int		count_heredocs(t_lexer *node);

#endif
