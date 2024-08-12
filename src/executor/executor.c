/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:40:33 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/12 18:03:31 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	init_builtins(t_builtin *builtins)
{
	builtins[0].name = "echo";
	builtins[0].func = ft_echo;
	builtins[1].name = "cd";
	builtins[1].func = ft_cd;
	builtins[2].name = "pwd";
	builtins[2].func = ft_pwd;
	builtins[3].name = "export";
	builtins[3].func = ft_export;
	builtins[4].name = "unset";
	builtins[4].func = ft_unset;
	builtins[5].name = "env";
	builtins[5].func = ft_env;
	builtins[6].name = "exit";
	builtins[6].func = ft_exit;
	builtins[7].name = NULL;
	builtins[7].func = NULL;
}

bool	is_builtin(char *cmd)
{
	int			i;
	t_builtin	builtins[8];

	i = 0;
	init_builtins(builtins);
	while (builtins[i].name != NULL)
	{
		if (ft_strcmp(cmd, builtins[i].name) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	execute_builtin(t_shell *shell)
{
	int			i;
	t_builtin	builtins[8];

	i = 0;
	init_builtins(builtins);
	while (builtins[i].name != NULL)
	{
		if (ft_strcmp(shell->cmd[0], builtins[i].name) == 0)
			return (builtins[i].func(shell));
		i++;
	}
	return (FAILURE);
}

char	*build_cmd(char *path, char *cmd)
{
	char	*command;
	
	command = ft_strjoin(path, cmd);
	if (!command)
		return (NULL);
	return (command);
}

void	print_error_cmd(char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
}

void	execute_cmd(t_shell *shell)
{
	int		i;
	char	*tmp;

	i = 0;
	if (access(shell->cmd[0], X_OK) == SUCCESS)
		execve(shell->cmd[0], shell->cmd, shell->env);
	while (shell->path[i] != NULL)
	{
		tmp = build_cmd(shell->path[i], shell->cmd[0]);
		if (!tmp)
			print_error("error cmd");
		if (access(tmp, X_OK) == SUCCESS)
			execve(tmp, shell->cmd, shell->env);
		free(tmp);
		i++;
	}
	print_error_cmd(shell->cmd[0]);
	exit(EXIT_FAILURE);
}

int	execute(t_shell *shell)
{
	int		status;
	int		pid;

	if (is_builtin(shell->cmd[0]))
		return (execute_builtin(shell));
	pid = fork();
	if (pid == -1)
		printf("Error creating fork\n");
	if (pid == 0)
		execute_cmd(shell);
	wait(&status);
	return (status);
}
