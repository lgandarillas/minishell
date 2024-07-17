/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:14:49 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/17 19:17:30 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	get_pwd(t_shell *shell, char **env)
{
	int	index;

	index = get_index(env, "PWD=");
	shell->pwd = ft_strdup(env[index] + 4);
}

void	get_oldpwd(t_shell *shell, char **env)
{
	int	index;

	index = get_index(env, "OLDPWD=");
	shell->oldpwd = ft_strdup(env[index] + 7);
}

int	ft_pwd(char **cmd)
{
	char	*cwd;

	if (ft_arrlen((void **)cmd) > 1)
	{
		ft_putstr_fd("msh: pwd: too many arguments\n", STDERR_FILENO);
		return (FAILURE);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("msh: pwd: ");
		return (FAILURE);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (SUCCESS);
}
