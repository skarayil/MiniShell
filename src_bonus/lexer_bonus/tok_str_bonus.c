/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_str_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:09:28 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "lexer_bonus/lexer_bonus.h"
#include "libft.h"

static int	intlen_bonus(int n)
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

char	*tok_itoa_pos_bonus(int n)
{
	char	*s;
	int		len;

	len = intlen_bonus(n);
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
