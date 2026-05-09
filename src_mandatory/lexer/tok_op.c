/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:15:01 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:06 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "lexer/lexer.h"
#include "libft.h"

char	*read_double_op(char c, int *i)
{
	*i = *i + 1;
	if (c == '<')
		return (ft_strdup("<<"));
	if (c == '>')
		return (ft_strdup(">>"));
	return (NULL);
}

char	*read_single_op(char c)
{
	char	s[2];

	s[0] = c;
	s[1] = '\0';
	return (ft_strdup(s));
}
