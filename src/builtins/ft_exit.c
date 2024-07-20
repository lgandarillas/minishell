/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:40:43 by aquinter          #+#    #+#             */
/*   Updated: 2024/07/20 12:47:36 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	exit_error(char *str)
{
	ft_putstr_fd("msh: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	exit_status(char *str)
{
	int					sign;
	unsigned long long	nbr;

	if (!ft_strdigit(str))
		exit_error(str);
	sign = 1;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	if (ft_strlen(str) > 19)
		exit_error(str);
	nbr = ft_atoulonglong((const char *) str);
	if (sign == -1 && nbr > (unsigned long long)LLONG_MIN)
		exit_error(str);
	if (sign == 1 && nbr > (unsigned long long)LLONG_MAX)
		exit_error(str);
	nbr *= sign;
	if ((long long) nbr >= 0 && (long long) nbr <= 255)
		exit(nbr);
	exit(nbr % 256);
}

int	ft_exit(t_shell *shell)
{
	char	*str;
	int		status;

	if (ft_arrlen((void **)shell->cmd) > 2)
	{
		ft_putstr_fd("msh: exit: too many arguments\n", STDERR_FILENO);
		return (FAILURE);
	}
	str = shell->cmd[1];
	status = shell->status;
	free_shell(shell);
	printf("exit\n");
	if (!str)
		exit(status);
	exit_status(str);
	return (SUCCESS);
}
