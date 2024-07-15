/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:34:17 by aquinter          #+#    #+#             */
/*   Updated: 2024/07/15 16:37:08 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	update_env(t_shell *shell, char **env, char *new_var)
{
	char	**env_cpy;
	size_t	len;
	size_t	line;
	size_t	i;

	line = 2;
	len = ft_arrlen((void **)env);
	if (new_var == NULL)
		line--;
	env_cpy = ft_calloc(sizeof(char *), len + line);
	if (!env_cpy)
		return (false);
	i = 0;
	while (i < len)
	{
		env_cpy[i] = ft_strdup(env[i]);
		if (!env_cpy[i])
			return (free_matrix(env_cpy), false);
		i++;
	}
	if (new_var != NULL)
		env_cpy[len] = new_var;
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
