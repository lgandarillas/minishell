/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:01:05 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/10 20:42:12 by aquinter         ###   ########.fr       */
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
		exit_matrix("Error. getcwd() failed.\n", env);
	env[0] = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (!env[0])
		exit_matrix("Error. Malloc failed.\n", env);
	env[1] = ft_strdup("SHLVL=1");
	if (!env[1])
		exit_matrix("Error. Malloc failed.\n", env);
	printf("%s\n%s\n", env[0], env[1]);
	return (env);
}

// static void	update_env(t_shell *shell, char **envp)
// {
// 	char	**env_cpy;
// 	size_t	i;

// 	i = 0;
// 	while (envp[i] != NULL)
// 		i++;
// 	env_cpy = ft_calloc(sizeof(char *), i + 1);
// 	if (!env_cpy)
// 		print_error("Error. Malloc failed.\n");
// 	i = 0;
// 	while (envp[i] != NULL)
// 	{
// 		env_cpy[i] = ft_strdup(envp[i]);
// 		if (!env_cpy[i])
// 			exit_matrix("Error. Malloc failed.\n", env_cpy);
// 		i++;
// 	}
// 	shell->env = env_cpy;
// }

void	init_env(t_shell *shell, char **envp)
{
	if (!*envp)
		shell->env = create_env();
	else
		update_env(shell, envp, NULL);
}
