/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:24:23 by aquinter          #+#    #+#             */
/*   Updated: 2024/11/13 21:02:20 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_shell	t_shell;
typedef struct s_lexer	t_lexer;

int	parser(t_lexer *lexer_node, t_shell *shell);

#endif
