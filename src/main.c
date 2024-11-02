/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:43:33 by lgandari          #+#    #+#             */
/*   Updated: 2024/10/26 21:16:07 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	process_prompt(t_shell *shell, char *prompt)
{
	t_lexer	*lexer_node;

	if (check_prompt(prompt) == true)
	{
		lexer_node = lexer(prompt);
		expander(lexer_node, shell);
		shell->status = parser(lexer_node, shell);
		if (shell->status == 0)
		{
			shell->cmd_node = prepare_cmd(lexer_node, shell);
			handle_heredoc(shell->cmd_node, shell);
			shell->status = execute(shell);
			shell->cmd = NULL;
			free_command_nodes(shell->cmd_node, shell);
		}
		if (shell->expand_heredoc)
			free(shell->expand_heredoc);
		free_tokens(lexer_node);
	}
}

static void	shell_loop(t_shell *shell)
{
	char		*prompt;

	while (true)
	{
		prompt = readline(CYAN "msh> " RESET);
		if (prompt == NULL)
			handle_eof(shell);
		if (*prompt != '\0')
			process_prompt(shell, prompt);
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
