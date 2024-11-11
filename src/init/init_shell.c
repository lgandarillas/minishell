/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:01:05 by lgandari          #+#    #+#             */
/*   Updated: 2024/11/11 18:45:32 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	update_shlvl(t_shell *shell)
{
	char	*new_shlvl;
	char	*shlvl_str;
	int		shlvl;

	shlvl_str = ft_getenv(shell->env, "SHLVL=");
	if (shlvl_str == NULL)
	{
		if (!ft_setenv(shell->env, "SHLVL=", "1"))
			return (false);
		return (true);
	}
	shlvl = ft_atoi(shlvl_str);
	shlvl++;
	new_shlvl = ft_itoa(shlvl);
	if (!*new_shlvl)
		return (false);
	if (!ft_setenv(shell->env, "SHLVL=", new_shlvl))
	{
		free(new_shlvl);
		return (false);
	}
	free(new_shlvl);
	return (true);
}

static char	**create_env(void)
{
	char	**env;
	char	*cwd;

	env = ft_calloc(4, sizeof(char *));
	if (!env)
		print_error(MEM_ERROR);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		exit_matrix(MEM_ERROR, env);
	env[0] = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (!env[0])
		exit_matrix(MEM_ERROR, env);
	env[1] = ft_strdup("SHLVL=1");
	if (!env[1])
		exit_matrix(MEM_ERROR, env);
	env[2] = ft_strdup("PATH=");
	if (!env[2])
		exit_matrix(MEM_ERROR, env);
	return (env);
}

static void	init_env(t_shell *shell, char **envp)
{
	if (!*envp)
		shell->env = create_env();
	else
	{
		update_env(shell, envp, NULL);
		update_shlvl(shell);
	}
}

static void	print_welcome(void)
{
	printf("█▀▄▀█ █ █▄░█ █ █▀ █░█ █▀▀ █░░ █░░\n");
	printf("█░▀░█ █ █░▀█ █ ▄█ █▀█ ██▄ █▄▄ █▄▄\n");
	printf("By: @aquinter && @lgandari\n");
}

void	init_shell(t_shell *shell, char **envp)
{
	shell->status = 0;
	shell->num_cmds = 0;
	shell->env = NULL;
	shell->cmd = NULL;
	shell->path = NULL;
	shell->lexer_node = NULL;
	shell->cmd_node = NULL;
	print_welcome();
	init_env(shell, envp);
	init_builtins(shell);
	get_path(shell);
}
