/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:32:34 by aquinter          #+#    #+#             */
/*   Updated: 2024/11/13 19:58:40 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	init_signals(void);
void	init_child_signals(void);
void	init_heredoc_signals(void);
void	ignore_signals(void);
void	handle_sigint(int sig);
void	handle_heredoc_sigint(int sig);
void	handle_eof(t_shell *shell);
void	handle_sigquit(int sig);

#endif