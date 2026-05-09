/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:15:11 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:06 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "lexer/lexer.h"
#include "libft.h"

static int	intlen(int n)
{
	int	len;

	len = 1;
	while (n >= 10)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*tok_itoa_pos(int n)
{
	char	*s;
	int		len;

	len = intlen(n);
	s = ft_gc_malloc(len + 1);
	if (!s)
		return (NULL);
	s[len] = '\0';
	while (len > 0)
	{
		s[len - 1] = (char)('0' + (n % 10));
		n = n / 10;
		len--;
	}
	return (s);
}
