/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:43:21 by lgandari          #+#    #+#             */
/*   Updated: 2025/03/04 22:53:03 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_shell(t_shell *shell)
{
	if (shell->env != NULL)
		free_matrix(shell->env);
	if (shell->path != NULL)
		free_matrix(shell->path);
}

void	exit_matrix(char *msg, char **matrix)
{
	if (matrix != NULL)
		free_matrix(matrix);
	print_error(msg, false);
}
