/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:14:49 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/25 15:16:20 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(t_shell *shell)
{
	char	*cwd;

	if (ft_arrlen((void **)shell->cmd) > 1)
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
