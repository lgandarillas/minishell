/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:54:04 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/12 19:34:25 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	get_path_index(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (i);
		else
			i++;
	}
	return (print_error("Path not found.\n"));
}

void	get_path(t_shell *shell, char **env)
{
	int		index;
	char	**directories;
	char	*path;
	int		i;

	index = get_path_index(env);
	directories = ft_split(env[index] + 5, ':');
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
