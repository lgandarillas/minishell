/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 20:41:15 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/18 18:32:07 by lgandari         ###   ########.fr       */
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
	return (-1);
}

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

static bool	check_closing_tokens(char *prompt)
{
	int	len;

	if (!prompt || !*prompt)
		return (false);
	len = ft_strlen(prompt);
	if (prompt[0] == '|')
		return (false);
	if (prompt[len-1] == '|' || prompt[len - 1] == '<' || prompt[len - 1] == '>')
		return (false);
	return (true);
}

char	**parser(char *prompt)
{
	char	**cmd;

	add_history(prompt);
	prompt = ft_strtrim(prompt, " ");
	if (!check_quotes(prompt))
		printf("Error. Invalid quotes.\n");
	if (!check_closing_tokens(prompt))
		printf("Error. Invalid closing tokens.\n");
	cmd = ft_split(prompt, ' ');
	free(prompt);
	if (!cmd)
		print_error("Malloc failed.\n");
	return (cmd);
}
