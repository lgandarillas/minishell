/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:19:21 by aquinter          #+#    #+#             */
/*   Updated: 2024/07/17 19:19:45 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env(char **env, char **cmd)
{
	int	i;

	if (cmd && ft_arrlen((void **)cmd) > 1)
	{
		ft_putstr_fd("msh: env: too many arguments\n", STDERR_FILENO);
		return (FAILURE);
	}
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (SUCCESS);
}
