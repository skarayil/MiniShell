/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_helpers_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:11:41 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser_bonus/parser_bonus.h"

int	find_op_bonus(char **tok, int s, int e, char *op)
{
	int	i;
	int	p;

	i = e - 1;
	p = 0;
	while (i >= s)
	{
		if (ft_streq(tok[i], ")"))
			p++;
		else if (ft_streq(tok[i], "("))
			p--;
		else if (p == 0 && ft_streq(tok[i], op))
			return (i);
		i--;
	}
	return (-1);
}

int	find_logic_op_bonus(char **tok, int s, int e)
{
	int	i;
	int	p;

	i = e - 1;
	p = 0;
	while (i >= s)
	{
		if (ft_streq(tok[i], ")"))
			p++;
		else if (ft_streq(tok[i], "("))
			p--;
		else if (p == 0 && is_logic_bonus(tok[i]))
			return (i);
		i--;
	}
	return (-1);
}

int	find_matching_paren_bonus(char **tok, int s, int e)
{
	int	depth;
	int	i;

	depth = 0;
	i = s;
	while (i < e)
	{
		if (ft_streq(tok[i], "("))
			depth++;
		else if (ft_streq(tok[i], ")"))
			depth--;
		if (depth == 0)
			return (i);
		i++;
	}
	return (-1);
}
