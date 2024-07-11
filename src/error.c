/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:43:21 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/11 19:20:19 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_shell(t_shell *shell)
{
	if (shell->env != NULL)
		free_matrix(shell->env);
}

void	exit_matrix(char *msg, char **matrix)
{
	if (matrix != NULL)
		free_matrix(matrix);
	print_error(msg);
}
