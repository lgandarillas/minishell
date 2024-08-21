/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 19:06:55 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/21 17:34:26 by lgandari         ###   ########.fr       */
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
	if (quote != 0)
		return (false);
	return (true);
}

static bool	check_prompt_errors(char *prompt)
{
	if (!check_quotes(prompt))
	{
		ft_putstr_fd("Error. Invalid quotes.\n", STDERR_FILENO);
		return (false);
	}
	else
		return (true);
}

bool	check_prompt(char *prompt)
{
	add_history(prompt);
	prompt = ft_strtrim(prompt, " ");
	if (*prompt == '\0' || !check_prompt_errors(prompt))
	{
		free(prompt);
		return (false);
	}
	else
	{
		free(prompt);
		return (true);
	}
}
