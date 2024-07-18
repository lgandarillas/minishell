/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:40:43 by aquinter          #+#    #+#             */
/*   Updated: 2024/07/17 20:03:44 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_exit(t_shell *shell)
{
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
	return (SUCCESS);
}