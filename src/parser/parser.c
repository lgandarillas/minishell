/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 20:41:15 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/15 16:36:44 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**parser(char *prompt)
{
	char	**cmd;

	add_history(prompt);
	prompt = ft_strtrim(prompt, " ");
	cmd = ft_split(prompt, ' ');
	free(prompt);
	if (!cmd)
		print_error("Malloc failed.\n");
	return (cmd);
}
