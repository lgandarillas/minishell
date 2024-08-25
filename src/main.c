/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:43:33 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/25 15:10:25 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	shell_loop(t_shell *shell)
{
	char	*prompt;
	t_lexer	*node;

	while (true)
	{
		prompt = readline(CYAN "msh> " RESET);
		if (prompt == NULL)
			handle_eof(shell);
		if (*prompt != '\0')
		{
			if (check_prompt(prompt) == true)
			{
				node = lexer(prompt);
				expander(node, shell);
				shell->status = parser(node, shell);
				if (shell->status == 0)
				{
					shell->cmd = node->argv;
					shell->node = node;
					shell->status = execute(shell);
					shell->cmd = NULL;
				}
				free_tokens(node);
			}
		}
		free(prompt);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (argc != 1 || !argv[0])
		print_error("Error. Usage: ./minishell\n");
	init_shell(&shell, envp);
	shell_loop(&shell);
	free_shell(&shell);
	return (0);
}
