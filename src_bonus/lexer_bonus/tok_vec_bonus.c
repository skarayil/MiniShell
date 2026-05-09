/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_vec_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:09:33 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "lexer_bonus/lexer_bonus.h"
#include "libft.h"

char	**tok_push_bonus(char **v, int n, char *s)
{
	char	**out;
	int		i;

	out = ft_gc_malloc(sizeof(char *) * (n + 2));
	if (!out)
		return (NULL);
	i = 0;
	while (i < n)
	{
		out[i] = v[i];
		i++;
	}
	out[n] = s;
	out[n + 1] = NULL;
	return (out);
}

void	tok_free_all_bonus(char **v)
{
	(void)v;
}
