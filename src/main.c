/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:43:33 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/15 21:35:32 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	execute_builtin(t_shell *shell)
{
	if (ft_strcmp(*(shell->cmd), "echo") == 0)
		return (ft_echo(shell));
	else if (ft_strcmp(*(shell->cmd), "cd") == 0)
		return (ft_cd(shell->env, shell->cmd));
	else if (ft_strcmp(*(shell->cmd), "pwd") == 0)
		return (ft_pwd(shell->env));
	else if (ft_strcmp(*(shell->cmd), "export") == 0)
		return (ft_export(shell));
	else if (ft_strcmp(*(shell->cmd), "unset") == 0)
		return (ft_unset((shell)));
	else if (ft_strcmp(*(shell->cmd), "env") == 0)
		return (ft_env(shell->env));
	else if (ft_strcmp(*(shell->cmd), "exit") == 0)
		return (true);
	return (false);
}

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
			if (ft_strcmp("exit", *cmd) != 0)
			{
				shell->cmd = cmd;
				shell->status = execute_builtin(shell);
				free_matrix(cmd);
				shell->cmd = NULL;
			}
			else
			{
				free_matrix(cmd);
				return ;
			}
		}
		else
			free(prompt);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (argc != 1 || !argv[0])
		print_error("Error. Exec minishell with no arguments.\n");
	init_shell(&shell, envp);
	shell_loop(&shell);
	free_shell(&shell);
	return (0);
}
