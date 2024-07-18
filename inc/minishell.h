/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:31:51 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/18 17:35:39 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <termcap.h>
# include <stdbool.h>

# include "builtins.h"
# include "constants.h"
# include "../libft_v2/inc/libft.h"
# include "../libft_v2/inc/get_next_line.h"
# include "../libft_v2/inc/ft_printf.h"
# include "../libft_v2/inc/extra.h"

typedef struct s_shell
{
	int		status;
	char	**env;
	char	**cmd;
	char	**path;
	char	*pwd;		//OJO
	char	*oldpwd;	//OJO, ft_pwd.c
}		t_shell;

void	init_shell(t_shell *shell, char **envp);

int		get_index(char **env, const char *var);
void	get_path(t_shell *shell, char **env);
void	get_pwd(t_shell *shell, char **env);
void	get_oldpwd(t_shell *shell, char **env);

bool	update_env(t_shell *shell, char **env, char *new_var);
bool	ft_setenv(char **env, char *var, char *val);
char	*ft_getenv(char **env, char *var);
bool	ft_addenv(t_shell *shell, char **env, char *var, char *val);
bool	ft_delenv(t_shell *shell, char **env, char *var);

char	**parser(char *prompt);

void	free_shell(t_shell *shell);
void	exit_matrix(char *msg, char **matrix);

#endif
