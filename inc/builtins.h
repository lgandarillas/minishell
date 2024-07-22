/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:31:40 by aquinter          #+#    #+#             */
/*   Updated: 2024/07/22 17:53:20 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_builtins
{
	/* data */
}	t_builtins;

typedef struct s_shell	t_shell;

int					ft_cd(t_shell *shell);
int					ft_pwd(t_shell *shell);
int					ft_export(t_shell *shell);
int					ft_env(t_shell *shell);
int					ft_unset(t_shell *shell);
int					ft_echo(t_shell *shell);
int					ft_exit(t_shell *shell);
int					print_env(char **env);
unsigned long long	ft_atoulonglong(const char *nptr);

#endif