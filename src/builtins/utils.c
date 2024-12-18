/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 21:42:06 by aquinter          #+#    #+#             */
/*   Updated: 2024/08/22 18:05:46 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

unsigned long long	ft_atoulonglong(const char *nptr)
{
	unsigned long long	res;

	res = 0;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + *nptr - '0';
		nptr++;
	}
	return (res);
}

bool	is_builtin(t_shell *shell, char *cmd)
{
	int	i;

	i = 0;
	while (shell->builtins[i].name != NULL)
	{
		if (ft_strcmp(cmd, shell->builtins[i].name) == 0)
			return (true);
		i++;
	}
	return (false);
}
