/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:43:33 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/18 20:41:44 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	shell_loop(t_shell *shell)
{
	char		*prompt;
	char		**cmd;

	while (true)
	{
		prompt = readline(CYAN "msh> " RESET);
		if (*prompt != '\0')
		{
			cmd = parser(prompt);
			free(prompt);
			if (cmd != NULL && ft_strcmp("exit", *cmd) != 0)
			{
				shell->cmd = cmd;
				shell->status = execute_builtin(shell);
				free_matrix(cmd);
				shell->cmd = NULL;
			}
			else if (cmd != NULL)
				return (free_matrix(cmd));
		}
		else
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
