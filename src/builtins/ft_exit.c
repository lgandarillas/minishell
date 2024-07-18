/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:40:43 by aquinter          #+#    #+#             */
/*   Updated: 2024/07/18 20:08:53 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

	/*
	Sintaxis: exit N

    Si N no está definido:
        Retornar el código de estado del último comando ejecutado.
    
    Convertir N a un número y verificar si está dentro del rango de un `long`.
    
    Si N es un número válido y está dentro de LONG_MIN y LONG_MAX:
        Si N está dentro del rango válido (0 a 255 ambos incluidos):
            Retornar N como código de estado.
        Si N está fuera del rango válido:
            Retornar N % 256 como código de estado.
    
    Si N no es un número entero válido o está fuera de LONG_MIN y LONG_MAX:
        Mostrar mensaje de error "numeric argument required".
	
	*/

unsigned long long	ft_atoulonglong(const char *nptr)
{
	unsigned long long 	res;
	int			sign;

	res = 0;
	sign = 1;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '+')
		nptr++;
	else if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	if (*nptr == '+' || *nptr == '-')
		return (0);
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + *nptr - '0';
		nptr++;
	}
	return (res * sign);
}

int	ft_exit(t_shell *shell)
{
	unsigned long long	nbr;
	bool negative;
	char	*str;

	negative = false;
	str = shell->cmd[1];
	if (str[0] == '-')
	{
		if (ft_strlen(str) > 20)
		{
			printf("Error\n");
			return (FAILURE);
		}
		negative = true;
		str++;
	}
	else if (ft_strlen(str) > 19)
	{
		printf("Error\n");
		return (FAILURE);
	}
	nbr = ft_atolonglong((const char *) str);
	if (negative == true && nbr > (unsigned long long)LLONG_MIN)
		printf("Error\n");
	else if (!negative && nbr > (unsigned long long)LLONG_MAX)
		printf("Error\n");
	else
		printf("Success\n");
	return (SUCCESS);
}