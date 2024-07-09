/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:03:56 by aquinter          #+#    #+#             */
/*   Updated: 2024/07/09 17:22:13 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// static bool	valid_identifier(char *var)
// {
// 	int	i;
	
// 	i = 0;
// 	if (!var)
// 		return (false);
// 	if (!ft_isalpha(var[i]) && var[i] != '_')
// 		return (false);
// 	i++;
// 	while (var[i])
// 	{
// 		if (!ft_isalnum(var[i]) && var[i] != '_')
// 			return(false);
// 		i++;
// 	}
// 	return (true);
// }

static void	handle_simple_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

bool export(char **env, char **cmd)
{
	int		i;
	char	*value;
	char	*var;

	i = 1;
	if (!cmd[1])
		handle_simple_env(env);
	else
	{
		while (cmd[i] != NULL)
		{
			value = ft_strchr(cmd[i], '=');
			if (!value)
				return (false);
			var = ft_substr(cmd[i], 0, (value) - cmd[i]);
			if (!var)
			{
				ft_putstr_fd("msh: malloc error", STDERR_FILENO);
				return (false);
			}
			printf("var: %s | value: %s\n", var, value + 1);
			free(var);
			// if (!valid_identifier(var))
			// {
			// 	ft_putstr_fd("bash: export: `", STDERR_FILENO);
			// 	ft_putstr_fd(cmd[i], STDERR_FILENO);
			// 	ft_putstr_fd("\': not a valid identifier\n", STDERR_FILENO);
			// }
			// else
				// printf("%s\n", cmd[i]);
			i++;
		}
	}
	return (true);
}