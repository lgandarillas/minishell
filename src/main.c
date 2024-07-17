/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:43:33 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/17 19:22:31 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	execute_builtin(t_shell *shell)
{
	if (ft_strcmp(*(shell->cmd), "echo") == 0)
		return (ft_echo(shell));
	if (ft_strcmp(*(shell->cmd), "cd") == 0)
		return (ft_cd(shell->env, shell->cmd));
	if (ft_strcmp(*(shell->cmd), "pwd") == 0)
		return (ft_pwd(shell->cmd));
	if (ft_strcmp(*(shell->cmd), "export") == 0)
		return (ft_export(shell));
	if (ft_strcmp(*(shell->cmd), "unset") == 0)
		return (ft_unset((shell)));
	if (ft_strcmp(*(shell->cmd), "env") == 0)
		return (ft_env(shell->env, shell->cmd));
	if (ft_strcmp(*(shell->cmd), "exit") == 0)
		return (SUCCESS);
	return (FAILURE);
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
