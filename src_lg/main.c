/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:43:33 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/04 19:36:43 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	shell_loop(void)
{
	char	*prompt;
	int		loops;

	loops = 0;
	//while (1)
	while (loops < 3)
	{
		prompt = readline("msh>");
		if (!prompt)
			print_error("Malloc failed.\n");
		printf("%s\n", prompt);
		free(prompt);
		loops++;
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
