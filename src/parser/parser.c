/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 20:41:15 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/15 17:05:31 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_index(char **env, const char *var)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
			return (i);
		else
			i++;
	}
	return (print_error("Var not found.\n"));
}

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
