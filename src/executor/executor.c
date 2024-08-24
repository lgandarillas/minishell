/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:40:33 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/24 14:08:01 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execute_builtin(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->builtins[i].name != NULL)
	{
		if (ft_strcmp(shell->token->argv[0], shell->builtins[i].name) == 0)
			return (shell->builtins[i].func(shell));
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
	if (access(shell->token->argv[0], X_OK) == SUCCESS)
		execve(shell->token->argv[0], shell->token->argv, shell->env);
	while (shell->path[i] != NULL)
	{
		tmp = build_cmd(shell->path[i], shell->token->argv[0]);
		if (!tmp)
			print_error("error cmd");
		if (access(tmp, X_OK) == SUCCESS)
			execve(tmp, shell->token->argv, shell->env);
		free(tmp);
		i++;
	}
	print_error_cmd(shell->token->argv[0]);
	exit(EXIT_FAILURE);
}

int	execute(t_shell *shell)
{
	int		status;
	int		pid;

	if (!shell->cmd[0])
		return (SUCCESS);
	while (shell->token)
	{
		if (shell->token->is_command)
		{
			if (shell->token->is_builtin)
				status = execute_builtin(shell);
			else
			{
				pid = fork();
				if (pid == -1)
					printf("Error creating fork\n");
				if (pid == 0)
					execute_cmd(shell);
				wait(&status);
			}
		}
		shell->token = shell->token->next;
	}
	return (status);
}
