/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_op_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:09:22 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "lexer_bonus/lexer_bonus.h"
#include "libft.h"

char	*read_double_op_bonus(char c, int *i)
{
	*i = *i + 1;
	if (c == '<')
		return (ft_strdup("<<"));
	if (c == '>')
		return (ft_strdup(">>"));
	if (c == '|')
		return (ft_strdup("||"));
	if (c == '&')
		return (ft_strdup("&&"));
	return (NULL);
}

char	*read_single_op_bonus(char c)
{
	char	s[2];

	s[0] = c;
	s[1] = '\0';
	return (ft_strdup(s));
}
