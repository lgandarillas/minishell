/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:43:21 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/12 20:16:53 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_shell(t_shell *shell)
{
	if (shell->env != NULL)
		free_matrix(shell->env);
	if (shell->cmd != NULL)
		free_matrix(shell->cmd);
}

void	exit_matrix(char *msg, char **matrix)
{
	if (matrix != NULL)
		free_matrix(matrix);
	print_error(msg);
}

void	malloc_error(void)
{
	ft_putstr_fd("msh: malloc error\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}