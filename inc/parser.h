/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:24:23 by aquinter          #+#    #+#             */
/*   Updated: 2024/09/02 17:50:08 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_shell	t_shell;
typedef struct s_lexer	t_lexer;

bool	parser(t_lexer *lexer_node, t_shell *shell);

#endif
