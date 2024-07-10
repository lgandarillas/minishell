/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:31:40 by aquinter          #+#    #+#             */
/*   Updated: 2024/07/10 20:58:05 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_builtins
{
	/* data */
}	t_builtins;

typedef struct s_shell	t_shell;

bool	ft_cd(char **env, char **cmd);
bool	ft_pwd(char **env);
bool	ft_export(t_shell *shell, char **env, char **cmd);
bool	ft_env(char **env);

#endif