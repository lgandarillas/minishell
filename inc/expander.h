/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:34:13 by lgandari          #+#    #+#             */
/*   Updated: 2024/09/04 21:06:02 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

void	expander(t_lexer *lexer_node, t_shell *shell);
char	*expand_variables(char *str, char **env);
char	*add_quotes_to_result(char *result, char quote_char);
char	*handle_expansion(char *str, size_t *i, char **env);

char	**word_splitter(char *str);
bool	is_quote(char c);

char	**quote_cleaner(char **argv);
char	*expand_status(char *str, int status);

#endif
