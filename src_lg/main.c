/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:43:33 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/04 16:34:14 by lgandari         ###   ########.fr       */
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
	if (argc != 1|| argv[1] != NULL)
		print_error("Error. Exec minishell with no arguments.\n", -1);
	shell_loop();
	printf("Test\n");
	return (0);
}
