/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:32:34 by aquinter          #+#    #+#             */
/*   Updated: 2024/08/06 19:03:18 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	init_signals(void);
void	handle_eof(t_shell *shell);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);

#endif