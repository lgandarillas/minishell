/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:15:56 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/30 17:17:17 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

typedef struct s_command
{
	struct s_command	*next;
	char				**cmd;
}	t_command;

#endif
