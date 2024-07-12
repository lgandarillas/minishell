/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:56:40 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/12 20:11:39 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	get_pwd_index(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
			return (i);
		else
			i++;
	}
	return (print_error("PWD not found.\n"));
}

static int	get_oldpwd_index(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
			return (i);
		else
			i++;
	}
	return (print_error("PWD not found.\n"));
}

void	get_pwd(t_shell *shell, char **env)
{
	int	index;

	index = get_pwd_index(env);
	shell->pwd = ft_strdup(env[index] + 4);
}

void	get_oldpwd(t_shell *shell, char **env)
{
	int	index;

	index = get_oldpwd_index(env);
	shell->oldpwd = ft_strdup(env[index] + 7);
}
