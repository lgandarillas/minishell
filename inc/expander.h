/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:34:13 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/15 16:17:01 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

void	expander(t_token *head, t_shell *shell);
char	*add_quotes_to_result(char *result, char quote_char);
char	*handle_expansion(char *str, size_t *i, char **env);

#endif
