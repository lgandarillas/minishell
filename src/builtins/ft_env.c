/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:19:21 by aquinter          #+#    #+#             */
/*   Updated: 2024/07/22 17:53:13 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (SUCCESS);
}

int	ft_env(t_shell *shell)
{
	if (ft_arrlen((void **)shell->cmd) > 1)
	{
		ft_putstr_fd("msh: env: too many arguments\n", STDERR_FILENO);
		return (FAILURE);
	}
	return (print_env(shell->env));
}
