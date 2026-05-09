/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_buf_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:09:17 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "lexer_bonus/lexer_bonus.h"
#include "libft.h"

char	*tok_addc_bonus(char *s, char c)
{
	char	*out;
	int		i;
	int		n;

	n = 0;
	if (s)
		n = (int)ft_strlen(s);
	out = ft_gc_malloc((size_t)n + 2);
	if (!out)
		return (NULL);
	i = 0;
	while (i < n)
	{
		out[i] = s[i];
		i++;
	}
	out[i++] = c;
	out[i] = '\0';
	return (out);
}
