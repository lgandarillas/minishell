/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 14:02:25 by aquinter          #+#    #+#             */
/*   Updated: 2025/03/04 22:53:20 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	unset_env(t_shell *shell, char **env, size_t index)
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
		if (i != index)
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
	int	index;

	index = get_index(env, var);
	if (!unset_env(shell, env, index))
		print_error(MEM_ERROR, false);
	free_matrix(env);
	return (true);
}
