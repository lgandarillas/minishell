/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:54:04 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/15 17:05:58 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
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
	return (print_error("Var not found.\n"));
}
*/

void	get_path(t_shell *shell, char **env)
{
	int		index;
	char	**directories;
	char	*path;
	int		i;

	index = get_index(env, "PATH=");
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
