/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_buf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:14:52 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:06 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "lexer/lexer.h"
#include "libft.h"

char	*tok_addc(char *s, char c)
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
