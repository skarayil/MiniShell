/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:13:38 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "expand_bonus/expand_bonus.h"
#include "libft.h"

int	is_match_bonus(const char *pattern, const char *name)
{
	if (*pattern == '\0')
		return (*name == '\0');
	if (*pattern == QUOTE_MARKER)
	{
		if (*name != '*')
			return (0);
		return (is_match_bonus(pattern + 1, name + 1));
	}
	if (*pattern == '*')
	{
		while (*pattern == '*')
			pattern++;
		if (*pattern == '\0')
			return (1);
		while (*name)
		{
			if (is_match_bonus(pattern, name))
				return (1);
			name++;
		}
		return (is_match_bonus(pattern, name));
	}
	if (*pattern == *name)
		return (is_match_bonus(pattern + 1, name + 1));
	return (0);
}

char	*restore_pattern_bonus(char *s)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	len = ft_strlen(s);
	res = ft_gc_malloc(len + 1);
	if (!res)
		return (NULL);
	while (s[i])
	{
		if (s[i] == QUOTE_MARKER)
			res[i] = '*';
		else
			res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static int	cmp_sort_bonus(const char *s1, const char *s2)
{
	size_t	l1;
	size_t	l2;
	size_t	len;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	if (l1 > l2)
		len = l1;
	else
		len = l2;
	return (ft_strncmp(s1, s2, len + 1));
}

void	sort_list_bonus(char **list)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (list && list[i])
	{
		j = i + 1;
		while (list[j])
		{
			if (cmp_sort_bonus(list[i], list[j]) > 0)
			{
				tmp = list[i];
				list[i] = list[j];
				list[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
