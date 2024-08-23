/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 19:06:55 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/21 18:02:28 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	check_quotes(char *prompt)
{
	int	i;
	int	quote;

	if (!prompt || !*prompt)
		return (false);
	i = 0;
	quote = 0;
	while (prompt[i])
	{
		if ((prompt[i] == 34 || prompt[i] == 39) && quote == 0)
			quote = prompt[i];
		else if (prompt[i] == quote)
			quote = 0;
		i++;
	}
	if (quote == 0)
		return (true);
	else
		return (false);
}

bool	check_prompt(char *prompt)
{
	add_history(prompt);
	prompt = ft_strtrim(prompt, " ");
	if (*prompt == '\0')
	{
		free(prompt);
		return (false);
	}
	if (!check_quotes(prompt))
	{
		ft_putstr_fd("msh: syntax error: unmatched quotes\n", STDERR_FILENO);
		free(prompt);
		return (false);
	}
	free(prompt);
	return (true);
}
