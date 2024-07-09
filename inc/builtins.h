/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:31:40 by aquinter          #+#    #+#             */
/*   Updated: 2024/07/08 17:13:17 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_builtins
{
	/* data */
}	t_builtins;

typedef struct s_shell	t_shell;

bool	cd(char **env, char **cmd);
bool	pwd(char **env);
bool	export(char **env, char **cmd);

#endif