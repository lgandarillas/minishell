/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:29:46 by aquinter          #+#    #+#             */
/*   Updated: 2024/08/06 19:02:22 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_eof(t_shell *shell)
{
	free_shell(shell);
	printf("exit\n");
	exit(EXIT_SUCCESS);
}