/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parse_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:14:32 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_bonus/env_bonus.h"
#include "expand_bonus/expand_bonus.h"
#include "libft.h"
#include "types_bonus.h"

char	*exp_get_key_bonus(const char *s, int *i)
{
	char	key[256];
	int		k;

	k = 0;
	while (s[*i] && is_name_char_bonus(s[*i]) && k < 255)
	{
		key[k++] = s[*i];
		(*i)++;
	}
	key[k] = '\0';
	return (ft_strdup(key));
}

int	exp_update_q_bonus(int q, char c)
{
	if (q == 0 && c == '\'')
		return (1);
	if (q == 0 && c == '"')
		return (2);
	if (q == 1 && c == '\'')
		return (0);
	if (q == 2 && c == '"')
		return (0);
	return (q);
}

char	*exp_lookup_bonus(t_shell *sh, const char *s, int *i)
{
	char	*key;
	char	*val;

	key = exp_get_key_bonus(s, i);
	if (!key)
		return (ft_strdup(""));
	val = env_get_bonus(sh, key);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}
