/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:43:33 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/04 17:10:01 by lgandari         ###   ########.fr       */
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
			print_error("Malloc failed.\n", -1);
		printf("%s\n", prompt);
		free(prompt);
	}
}

int	main(int argc, char **argv)//, char **envp)
{
	t_shell	*shell;

	if (argc != 1|| argv[1] != NULL)
		print_error("Error. Exec minishell with no arguments.\n", -1);
	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		print_error("Malloc failed.\n", -1);
	init_shell(shell);
	shell_loop();
	printf("Test\n");
	return (0);
}
