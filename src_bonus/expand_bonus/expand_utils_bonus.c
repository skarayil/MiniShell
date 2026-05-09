/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:14:13 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "expand_bonus/expand_bonus.h"
#include "libft.h"

char	**exp_arr_add_bonus(char **v, char *s)
{
	int		c;
	char	**n;
	int		i;

	c = 0;
	while (v && v[c])
		c++;
	n = ft_gc_malloc(sizeof(char *) * (c + 2));
	if (!n)
		return (NULL);
	i = 0;
	while (i < c)
	{
		n[i] = v[i];
		i++;
	}
	n[i] = s;
	n[i + 1] = NULL;
	return (n);
}

char	*exp_char_append_bonus(char *s, char c)
{
	int		l;
	char	*n;

	l = 0;
	if (s)
		l = ft_strlen(s);
	n = ft_gc_malloc(l + 2);
	if (!n)
		return (NULL);
	if (s)
		ft_memcpy(n, s, l);
	n[l] = c;
	n[l + 1] = '\0';
	return (n);
}

int	is_name_start_bonus(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	return (0);
}

int	is_name_char_bonus(char c)
{
	if (is_name_start_bonus(c))
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
