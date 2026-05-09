/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parse_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:09:15 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:06 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/env.h"
#include "expand/expand.h"
#include "libft.h"
#include "types.h"

char	*exp_get_key(const char *s, int *i)
{
	char	key[256];
	int		k;

	k = 0;
	while (s[*i] && is_name_char(s[*i]) && k < 255)
	{
		key[k++] = s[*i];
		(*i)++;
	}
	key[k] = '\0';
	return (ft_strdup(key));
}

int	exp_update_q(int q, char c)
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

char	*exp_lookup(t_shell *sh, const char *s, int *i)
{
	char	*key;
	char	*val;

	key = exp_get_key(s, i);
	if (!key)
		return (ft_strdup(""));
	val = env_get(sh, key);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}
