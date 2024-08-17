/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:43:33 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/17 13:40:39 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	shell_loop(t_shell *shell)
{
	char	*prompt;
	char	**cmd;
	t_token	*head;

	while (true)
	{
		prompt = readline(CYAN "msh> " RESET);
		if (prompt == NULL)
			handle_eof(shell);
		if (*prompt != '\0')
		{
			cmd = check_prompt(prompt);
			if (cmd != NULL)
			{
				head = lexer(prompt);
				expander(head, shell);
				parser(head);
				shell->cmd = cmd;
				shell->status = execute(shell);
				free_matrix(cmd);
				shell->cmd = NULL;
				free_tokens(head);
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
