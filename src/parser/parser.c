/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 20:41:15 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/23 19:56:37 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**parser(char *prompt)
{
	char	**cmd;

	add_history(prompt);
	prompt = ft_strtrim(prompt, " ");
	if (!check_prompt_errors(prompt))
		return (free(prompt), NULL);
	cmd = ft_split(prompt, ' ');
	free(prompt);
	if (!cmd)
		print_error("Malloc failed.\n");
	return (cmd);
}
