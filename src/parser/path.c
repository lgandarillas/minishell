/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:54:04 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/23 19:56:32 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_index(char **env, const char *var)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
			return (i);
		else
			i++;
	}
	return (-1);
}

void	get_path(t_shell *shell)
{
	int		index;
	char	**directories;
	char	*path;
	int		i;

	index = get_index(shell->env, "PATH=");
	directories = ft_split(shell->env[index] + 5, ':');
	i = 0;
	while (directories[i])
	{
		path = ft_strjoin(directories[i], "/");
		free(directories[i]);
		directories[i] = path;
		i++;
	}
	shell->path = directories;
}
