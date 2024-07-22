/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:56:25 by lgandari          #+#    #+#             */
/*   Updated: 2024/07/22 18:10:56 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

char	**parser(char *prompt);
bool	check_prompt_errors(char *prompt);

bool	is_token(char c);
bool	is_space(char c);

#endif
