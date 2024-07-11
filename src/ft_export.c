/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:03:56 by aquinter          #+#    #+#             */
/*   Updated: 2024/07/10 21:11:44 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static bool	export_error(char *var)
{
	ft_putstr_fd("msh: export: `", STDERR_FILENO);
	ft_putstr_fd(var, STDERR_FILENO);
	ft_putstr_fd("\': not a valid identifier\n", STDERR_FILENO);
	return (false);
}

static bool	valid_id(char *var)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(var[i]) && var[i] != '_')
		return (export_error(var));
	i++;
	while (var[i])
	{
		if (var[i] == '=')
			return (true);
		else if (!ft_isalnum(var[i]) && var[i] != '_')
			return (export_error(var));
		i++;
	}
	return (true);
}

bool	ft_export(t_shell *shell, char **env, char **cmd)
{
	int		i;
	char	*value;
	char	*var;

	i = 1;
	value = NULL;
	if (!cmd[1])
		return (ft_env(env));
	else
	{
		while (cmd[i] != NULL)
		{
			value = ft_strchr(cmd[i], '=');
			var = ft_substr(cmd[i], 0, (value) - cmd[i]);
			if (!var)
			{
				ft_putstr_fd("msh: malloc error", STDERR_FILENO);
				return (false);
			}
			if (valid_id(cmd[i]))
				ft_addenv(shell, shell->env, var, value);
			free(var);
			i++;
		}
	}
	return (true);
}
