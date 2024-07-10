/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:34:17 by aquinter          #+#    #+#             */
/*   Updated: 2024/07/10 20:53:45 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	update_env(t_shell *shell, char **env, char *new_var)
{
	char	**env_cpy;
	size_t	len;
	size_t	line;
	size_t	i;

	line = 2;
	len = ft_arrlen((void **)env) + 1;
	if (new_var == NULL)
		line--;
	env_cpy = ft_calloc(sizeof(char *), len + line);
	if (!env_cpy)
		print_error("Error. Malloc failed.\n");
	i = 0;
	while (i < len - line)
	{
		env_cpy[i] = ft_strdup(env[i]);
		if (!env_cpy[i])
			exit_matrix("Error. Malloc failed.\n", env_cpy);
		i++;
	}
	if (new_var != NULL)
	{
		env_cpy[len - line] = new_var;
		free_matrix(env);	
	}
	shell->env = env_cpy;
}

void	ft_addenv(t_shell *shell, char *var, char *val)
{
	char	*new_var;

	new_var = NULL;
	if (val)
	{
		new_var = ft_strjoin(var, val);
		if (!new_var)
			return ;
	}
	update_env(shell, shell->env, new_var);
}