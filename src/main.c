/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:43:33 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/30 17:54:57 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	shell_loop(t_shell *shell)
{
	char		*prompt;
	t_lexer		*lexer_node;
	//t_command	*cmd_node;

	while (true)
	{
		prompt = readline(CYAN "msh> " RESET);
		if (prompt == NULL)
			handle_eof(shell);
		if (*prompt != '\0')
		{
			if (check_prompt(prompt) == true)
			{
				lexer_node = lexer(prompt);
				expander(lexer_node, shell);
				shell->status = parser(lexer_node, shell);
				//cmd_node = prepare_cmd(lexer_node);
				if (shell->status == 0)
				{
					shell->cmd = lexer_node->argv;
					shell->lexer_node = lexer_node;
					shell->status = execute(shell);
					shell->cmd = NULL;
				}
				free_tokens(lexer_node);
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
