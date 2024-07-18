/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:31:40 by aquinter          #+#    #+#             */
/*   Updated: 2024/07/18 18:36:59 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_builtins
{
	/* data */
}	t_builtins;

typedef struct s_shell	t_shell;

int	ft_cd(char **env, char **cmd);
int	ft_pwd(char **cmd);
int	ft_export(t_shell *shell);
int	ft_env(char **env, char **cmd);
int	ft_unset(t_shell *shell);
int	ft_echo(t_shell *shell);
int	ft_exit(t_shell *shell);

#endif