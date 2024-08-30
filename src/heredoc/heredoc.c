/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:27:36 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/30 11:31:13 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*create_filename(int temp_num)
{
	char	*num_str;
	char	*file_name;

	num_str = ft_itoa(temp_num);
	if (!num_str)
		return (NULL);
	file_name = ft_strjoin("/tmp/heredoc_", num_str);
	free(num_str);
	return (file_name);
}
