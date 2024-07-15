/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 14:02:25 by aquinter          #+#    #+#             */
/*   Updated: 2024/07/15 22:06:14 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	unset_env(t_shell *shell, char **env, char *var)
{
	char	**env_cpy;
	size_t	len;
	size_t	i;
	size_t	j;

	len = ft_arrlen((void **)env);
	env_cpy = ft_calloc(sizeof(char *), len);
	if (!env_cpy)
		return (false);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (ft_strcmp(env[i], var) != 0)
		{
			env_cpy[j] = ft_strdup(env[i]);
			if (!env_cpy[j])
				return (free_matrix(env_cpy), false);
			j++;
		}
		i++;
	}
	shell->env = env_cpy;
	return (true);
}

bool	ft_delenv(t_shell *shell, char **env, char *var)
{
	int		i;
	int		len;
	char	*line;

	i = 0;
	len = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0)
			line = env[i];
		i++;
	}
	if (!unset_env(shell, env, line))
		print_error(MEM_ERROR);
	free_matrix(env);
	return (true);
}
