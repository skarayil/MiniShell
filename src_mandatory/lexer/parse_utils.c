/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:14:43 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:06 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"

int	is_ws(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	open_quote(char c)
{
	if (c == '\'')
		return (1);
	if (c == '"')
		return (2);
	return (0);
}

int	is_op(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == ';')
		return (1);
	return (0);
}

void	skip_ws(const char *s, int *i)
{
	while (s[*i] && is_ws(s[*i]))
		(*i)++;
}
