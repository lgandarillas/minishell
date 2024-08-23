/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:34:13 by lgandari          #+#    #+#             */
/*   Updated: 2024/08/22 21:40:29 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

void	expander(t_token *head, t_shell *shell);
char	*add_quotes_to_result(char *result, char quote_char);
char	*handle_expansion(char *str, size_t *i, char **env);

char	**word_splitter(char *str);
int		find_quote_block_end(const char *str, int start_index);
char	*handle_quote_block(const char *str, size_t *index);
char	*handle_word_block(const char *str, size_t *index);
bool	is_quote(char c);

char	**quote_cleaner(char **argv);
char	*expand_status(char *str, int status);

#endif
