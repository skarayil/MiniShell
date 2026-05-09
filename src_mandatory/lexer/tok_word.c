/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:15:23 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:06 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "lexer/lexer.h"
#include "libft.h"

char	*read_word(const char *l, int *i)
{
	char	*t;
	int		q;

	t = NULL;
	q = 0;
	while (l[*i])
	{
		if (q == 0 && (is_ws(l[*i]) || is_op(l[*i])))
			break ;
		if (q == 0 && open_quote(l[*i]))
			q = open_quote(l[*i]);
		else if ((q == 1 && l[*i] == '\'') || (q == 2 && l[*i] == '"'))
			q = 0;
		t = tok_addc(t, l[*i]);
		*i = *i + 1;
	}
	if (!t)
		return (ft_strdup(""));
	return (t);
}
