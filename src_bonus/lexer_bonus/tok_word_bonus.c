/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_word_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:09:38 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "lexer_bonus/lexer_bonus.h"
#include "libft.h"

char	*read_word_bonus(const char *l, int *i)
{
	char	*t;
	int		q;

	t = NULL;
	q = 0;
	while (l[*i])
	{
		if (q == 0 && (is_ws_bonus(l[*i]) || is_op_bonus(l[*i])))
			break ;
		if (q == 0 && open_quote_bonus(l[*i]))
			q = open_quote_bonus(l[*i]);
		else if ((q == 1 && l[*i] == '\'') || (q == 2 && l[*i] == '"'))
			q = 0;
		t = tok_addc_bonus(t, l[*i]);
		*i = *i + 1;
	}
	if (!t)
		return (ft_strdup(""));
	return (t);
}
