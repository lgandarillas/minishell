/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:01:05 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/04 19:27:00 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_shell(t_shell *shell)
{
	shell->status = 0;
	shell->env = NULL;
}

static char	**create_env(void)
{
	char	**env;
	char	*cwd;

	env = ft_calloc(3, sizeof(char *));
	if (env == NULL)
		print_error("Error. Malloc failed.\n");
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		free_matrix(env);
		print_error("Error. getcwd() failed.\n");
	}
	env[0] = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (!env[0])
	{
		free_matrix(env);
		print_error("Error. Malloc failed.\n");
	}
	env[1] = ft_strdup("SHLVL=1");
	if (!env[1])
	{
		free_matrix(env);
		print_error("Error. Malloc failed.\n");
	}
	printf("%s\n%s\n", env[0], env[1]);
	return (env);
}

void	init_env(t_shell *shell, char **envp)
{
	if (!*envp)
	{
		shell->env = create_env();
	}
	//else
	//{
	//	//shell->env = manage_env()
	//}
}
