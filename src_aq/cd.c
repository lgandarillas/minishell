/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 21:38:38 by aquinter          #+#    #+#             */
/*   Updated: 2024/07/07 15:19:48 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	update_dirs(char **env)
{
	char	*cwd;

	if (!ft_setenv(env, "OLDPWD=", ft_getenv(env, "PWD=")))
	{
		ft_putstr_fd("msh: malloc error", STDERR_FILENO);
		return (false);
	}
	cwd = getcwd(NULL, sizeof(NULL));
	if (!cwd)
	{
		perror("msh: getcwd: ");
		return (false);
	}
	if (!ft_setenv(env, "PWD=", cwd))
	{
		ft_putstr_fd("msh: malloc error", STDERR_FILENO);
		free(cwd);
		return (false);
	}
	free(cwd);
	return (true);
}

bool	cd(char **env, char **cmd)
{
	int		ret_chdir;

	if (!cmd[1])
		ret_chdir = chdir(ft_getenv(env, "HOME="));
	else if (ft_strcmp("-", cmd[1]) == 0)
		ret_chdir = chdir(ft_getenv(env, "OLDPWD="));
	else
		ret_chdir = chdir(cmd[1]);
	if (ret_chdir == -1)
	{
		ft_putstr_fd("msh: cd: ", STDERR_FILENO);
		if (!cmd[1])
			ft_putstr_fd("HOME not set\n", STDERR_FILENO);
		else if (ft_strcmp("-", cmd[1]) == 0)
			ft_putstr_fd("OLDPWD not set\n", STDERR_FILENO);
		else
			perror(cmd[1]);
		return (false);
	}
	if (!update_dirs(env))
		return (false);
	if (cmd[1] && ft_strcmp("-", cmd[1]) == 0)
		printf("%s\n", ft_getenv(env, "PWD="));
	return (true);
}
