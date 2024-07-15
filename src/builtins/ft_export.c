/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:03:56 by aquinter          #+#    #+#             */
/*   Updated: 2024/07/15 22:30:14 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

static bool	manage_var(t_shell *shell, char *input)
{
	char	*var;
	char	*value;

	if (valid_id(input))
	{
		value = ft_strchr(input, '=') + 1;
		var = ft_substr(input, 0, value - input);
		if (!var)
			print_error(MEM_ERROR);
		if (ft_getenv(shell->env, var) != NULL)
		{
			if (!ft_setenv(shell->env, var, value))
				print_error(MEM_ERROR);
		}
		else
		{
			if (!ft_addenv(shell, shell->env, var, value))
				print_error(MEM_ERROR);
		}
		free(var);
		return (true);
	}
	return (false);
}

int	ft_export(t_shell *shell)
{
	int		i;
	bool	ret;

	i = 1;
	ret = SUCCESS;
	if (!shell->cmd[1])
		return (ft_env(shell->env));
	else
	{
		while (shell->cmd[i] != NULL)
		{
			if (!manage_var(shell, shell->cmd[i]))
				ret = FAILURE;
			i++;
		}
	}
	return (ret);
}
