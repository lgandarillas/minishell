/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 21:38:38 by aquinter          #+#    #+#             */
/*   Updated: 2024/07/04 22:20:50 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"



void cd(char *operands)
{
	printf("%s\n", operands);
	if (!operands)
		printf("%d\n", chdir(getenv("HOME")));
	else if (ft_strcmp("-", operands) == 0)
		printf("%d\n", chdir(getenv("OLD_PWD")));
	else
		printf("%d\n", chdir(operands));
}
