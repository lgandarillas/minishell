/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:34:17 by aquinter          #+#    #+#             */
/*   Updated: 2024/07/18 22:13:22 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	update_env(t_shell *shell, char **env, char *new_var)
{
	char	**env_cpy;
	char	**new_env;
	size_t	len;
	size_t	i;

	len = ft_arrlen((void **)env);
	env_cpy = ft_matrixdup(env);
	if (!env_cpy)
		return (false);
	if (new_var)
	{
		new_env = ft_calloc(sizeof(char *), len + 2);
		if (!new_env)
			return (free_matrix(env_cpy), false);
		i = -1;
		while (++i < len)
			new_env[i] = env_cpy[i];
		new_env[len] = new_var;
		free(env_cpy);
		env_cpy = new_env;
	}
	shell->env = env_cpy;
	return (true);
}

bool	ft_addenv(t_shell *shell, char **env, char *var, char *val)
{
	char	*new_var;

	new_var = NULL;
	if (val)
	{
		new_var = ft_strjoin(var, val);
		if (!new_var)
			return (false);
	}
	if (!update_env(shell, env, new_var))
	{
		if (new_var != NULL)
			free(new_var);
		return (false);
	}
	free_matrix(env);
	return (true);
}
