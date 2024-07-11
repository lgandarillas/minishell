/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 19:41:42 by aquinter          #+#    #+#             */
/*   Updated: 2024/07/09 20:29:30 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	ft_setenv(char **env, char *var, char *val)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	len = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0)
		{
			tmp = ft_strjoin(var, val);
			if (!tmp)
				return (false);
			free(env[i]);
			env[i] = tmp;
		}
		i++;
	}
	return (true);
}
