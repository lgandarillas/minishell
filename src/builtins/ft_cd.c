/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 21:38:38 by aquinter          #+#    #+#             */
/*   Updated: 2024/07/15 17:54:25 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	cd_error(char **env, char **cmd)
{
	char	*var;
	char	*error_msg;

	ft_putstr_fd("msh: cd: ", STDERR_FILENO);
	if (!cmd[1])
	{
		var = "HOME=";
		error_msg = "HOME not set\n";
	}
	else if (ft_strcmp("-", cmd[1]) == 0)
	{
		var = "OLDPWD=";
		error_msg = "OLDPWD not set\n";
	}
	else
	{
		perror(cmd[1]);
		return (FAILURE);
	}
	if (!ft_getenv(env, var))
		ft_putstr_fd(error_msg, STDERR_FILENO);
	else
		perror(ft_getenv(env, var));
	return (FAILURE);
}

static bool	update_dirs(char **env)
{
	char	*cwd;

	if (!ft_setenv(env, "OLDPWD=", ft_getenv(env, "PWD=")))
	{
		ft_putstr_fd("msh: malloc error", STDERR_FILENO);
		return (false);
	}
	cwd = getcwd(NULL, 0);
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

int	ft_cd(char **env, char **cmd)
{
	int	ret;

	if (ft_arrlen((void **)cmd) > 2)
	{
		ft_putstr_fd("msh: cd: too many arguments\n", STDERR_FILENO);
		return (FAILURE);
	}
	if (!cmd[1])
		ret = chdir(ft_getenv(env, "HOME="));
	else if (ft_strcmp("-", cmd[1]) == 0)
		ret = chdir(ft_getenv(env, "OLDPWD="));
	else
		ret = chdir(cmd[1]);
	if (ret == -1)
		return (cd_error(env, cmd));
	if (!update_dirs(env))
		return (FAILURE);
	if (cmd[1] && ft_strcmp("-", cmd[1]) == 0)
		printf("%s\n", ft_getenv(env, "PWD="));
	return (SUCCESS);
}
