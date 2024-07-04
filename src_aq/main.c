/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:43:33 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/04 22:16:01 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool execute_builtin(char **cmd)
{
	if (ft_strcmp(*cmd, "echo") == 0)
		return (true);
	else if (ft_strcmp(*cmd, "cd") == 0){
		cd(*(cmd + 1));
		return (true);
	}
	else if (ft_strcmp(*cmd, "pwd") == 0){
		printf("%s\n", getenv("PWD"));
		return (true);
	}
	else if (ft_strcmp(*cmd, "export") == 0)
		return (true);
	else if (ft_strcmp(*cmd, "unset") == 0)
		return (true);
	else if (ft_strcmp(*cmd, "env") == 0)
		return (true);
	else if (ft_strcmp(*cmd, "exit") == 0)
		return (true);
	return (false);
}

static void	shell_loop(void)
{
	char	*prompt;
	char	**cmd;
	// int		loops;

	// loops = 0;
	while (true)
	{
		prompt = readline("msh>");
		cmd = ft_split(prompt, ' ');
		if (!prompt)
			print_error("Malloc failed.\n");
		execute_builtin(cmd);
		free_matrix(cmd);
		free(prompt);
		// loops++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (argc != 1)
		print_error("Error. Exec minishell with no arguments.\n");
	init_shell(&shell);
	init_env(&shell, envp);
	shell_loop();
	free_shell(&shell);
	(void)argv;
	return (0);
}