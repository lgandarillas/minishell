/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:43:33 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/04 18:19:44 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	shell_loop(void)
{
	char	*prompt;

	while (1)
	{
		prompt = readline("msh>");
		if (!prompt)
			print_error("Malloc failed.\n");
		printf("%s\n", prompt);
		free(prompt);
	}
}

int	main(int argc, char **argv)//, char **envp)
{
	t_shell	shell;

	if (argc != 1)
		print_error("Error. Exec minishell with no arguments.\n");
	init_shell(&shell);
	//init_envp(&envp);
	shell_loop();
	(void)argv;
	return (0);
}
