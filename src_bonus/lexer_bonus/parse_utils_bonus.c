/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:09:10 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_bonus/lexer_bonus.h"

int	is_ws_bonus(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	open_quote_bonus(char c)
{
	if (c == '\'')
		return (1);
	if (c == '"')
		return (2);
	return (0);
}

int	is_op_bonus(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&' || c == '(' || c == ')'
		|| c == ';')
		return (1);
	return (0);
}

void	skip_ws_bonus(const char *s, int *i)
{
	while (s[*i] && is_ws_bonus(s[*i]))
		(*i)++;
}
