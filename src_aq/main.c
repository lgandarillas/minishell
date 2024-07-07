/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:43:33 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/07 15:18:58 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	execute_builtin(t_shell *shell)
{
	if (ft_strcmp(*(shell->cmd), "echo") == 0)
		return (true);
	else if (ft_strcmp(*(shell->cmd), "cd") == 0)
		return (cd(shell->env, shell->cmd));
	else if (ft_strcmp(*(shell->cmd), "pwd") == 0)
		return (pwd(shell->env));
	else if (ft_strcmp(*(shell->cmd), "export") == 0)
		return (true);
	else if (ft_strcmp(*(shell->cmd), "unset") == 0)
		return (true);
	else if (ft_strcmp(*(shell->cmd), "env") == 0)
		return (true);
	else if (ft_strcmp(*(shell->cmd), "exit") == 0)
		return (true);
	return (false);
}

static void	shell_loop(t_shell *shell)
{
	char	*prompt;
	char	**cmd;

	while (true)
	{
		prompt = readline("msh>");
		if (!prompt)
			print_error("Malloc failed.\n");
		cmd = ft_split(prompt, ' ');
		free(prompt);
		if (!cmd)
			print_error("Malloc failed.\n");
		if (ft_strcmp("break", *cmd) != 0)
		{
			shell->cmd = cmd;
			execute_builtin(shell);
			free_matrix(cmd);
		}
		else
		{
			free_matrix(cmd);
			break ;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (argc != 1)
		print_error("Error. Exec minishell with no arguments.\n");
	init_shell(&shell);
	init_env(&shell, envp);
	shell_loop(&shell);
	free_shell(&shell);
	(void)argv;
	return (0);
}
