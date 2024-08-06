/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 21:38:38 by aquinter          #+#    #+#             */
/*   Updated: 2024/08/06 14:22:21 by aquinter         ###   ########.fr       */
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
		ft_putstr_fd(MEM_ERROR, STDERR_FILENO);
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
		ft_putstr_fd(MEM_ERROR, STDERR_FILENO);
		free(cwd);
		return (false);
	}
	free(cwd);
	return (true);
}

int	ft_cd(t_shell *shell)
{
	int	ret;

	if (ft_arrlen((void **)shell->cmd) > 2)
	{
		ft_putstr_fd("msh: cd: too many arguments\n", STDERR_FILENO);
		return (FAILURE);
	}
	if (!shell->cmd[1])
		ret = chdir(ft_getenv(shell->env, "HOME="));
	else if (ft_strcmp("-", shell->cmd[1]) == 0)
		ret = chdir(ft_getenv(shell->env, "OLDPWD="));
	else
		ret = chdir(shell->cmd[1]);
	if (ret == -1)
		return (cd_error(shell->env, shell->cmd));
	if (!update_dirs(shell->env))
		return (FAILURE);
	if (shell->cmd[1] && ft_strcmp("-", shell->cmd[1]) == 0)
		printf("%s\n", ft_getenv(shell->env, "PWD="));
	return (SUCCESS);
}
