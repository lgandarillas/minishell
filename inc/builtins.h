/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:31:40 by aquinter          #+#    #+#             */
/*   Updated: 2024/07/22 18:16:08 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_shell	t_shell;
typedef int				(*t_builtin_func)(t_shell *shell);

typedef struct s_builtin
{
	char			*name;
	t_builtin_func	func;
}	t_builtin;

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