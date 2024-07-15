/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:40:32 by aquinter          #+#    #+#             */
/*   Updated: 2024/07/15 19:14:38 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	unset_error(char *var)
{
	ft_putstr_fd("msh: unset: `", STDERR_FILENO);
	ft_putstr_fd(var, STDERR_FILENO);
	ft_putstr_fd("\': not a valid identifier\n", STDERR_FILENO);
	return (false);
}

static bool	valid_id(char *var)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(var[i]) && var[i] != '_')
		return (unset_error(var));
	i++;
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (unset_error(var));
		i++;
	}
	return (true);
}

int	ft_unset(t_shell *shell)
{
	int		i;
	int		ret;
	char	*var;

	i = 1;
	ret = SUCCESS;
	while (shell->cmd[i] != NULL)
	{
		if (!valid_id(shell->cmd[i]))
			ret = FAILURE;
		else
		{
			var = ft_strjoin(shell->cmd[i], "=");
			if (!var)
				malloc_error();
			if (ft_getenv(shell->env, var))
				ft_delenv(shell, shell->env, var);
			free(var);
		}
		i++;
	}
	return (ret);
}
