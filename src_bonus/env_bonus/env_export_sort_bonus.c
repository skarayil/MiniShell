/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export_sort_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:19:30 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:09 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "env_bonus/env_bonus.h"
#include "libft.h"

static void	swap_bonus(char **a, char **b)
{
	char	*t;

	t = *a;
	*a = *b;
	*b = t;
}

void	env_sort_envp_bonus(char **v, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j + 1 < n)
		{
			if (ft_strncmp(v[j], v[j + 1], ft_strlen(v[j])
					+ ft_strlen(v[j + 1]) + 1) > 0)
				swap_bonus(&v[j], &v[j + 1]);
			j++;
		}
		i++;
	}
}

int	env_has_nonascii_bonus(const char *s)
{
	while (*s)
	{
		if ((unsigned char)*s > 126)
			return (1);
		s++;
	}
	return (0);
}

void	env_print_val_dollar_bonus(const char *s, int i)
{
	char	oct[5];

	write(1, "=$'", 3);
	while (s[i])
	{
		if ((unsigned char)s[i] > 126)
		{
			oct[0] = '\\';
			oct[1] = '0' + (((unsigned char)s[i] >> 6) & 7);
			oct[2] = '0' + (((unsigned char)s[i] >> 3) & 7);
			oct[3] = '0' + ((unsigned char)s[i] & 7);
			write(1, oct, 4);
		}
		else
			write(1, &s[i], 1);
		i++;
	}
	write(1, "'\n", 2);
}

void	env_print_val_quoted_bonus(const char *s, int i)
{
	write(1, "=\"", 2);
	while (s[i])
	{
		if (s[i] == '"')
			write(1, "\\\"", 2);
		else if (s[i] == '\\')
			write(1, "\\\\", 2);
		else if (s[i] == '$')
			write(1, "\\$", 2);
		else if (s[i] == '`')
			write(1, "\\`", 2);
		else
			write(1, &s[i], 1);
		i++;
	}
	write(1, "\"\n", 2);
}
