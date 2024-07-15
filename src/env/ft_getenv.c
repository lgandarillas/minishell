/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 19:41:42 by aquinter          #+#    #+#             */
/*   Updated: 2024/07/15 16:37:19 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_getenv(char **env, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0)
			return (env[i] + len);
		i++;
	}
	return (NULL);
}
