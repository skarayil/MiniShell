/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:19:19 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:09 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "env_bonus/env_bonus.h"
#include "expand_bonus/expand_bonus.h"
#include "libft.h"
#include "types_bonus.h"

char	*env_get_bonus(t_shell *sh, const char *key)
{
	int	i;
	int	klen;

	if (!sh || !sh->envp || !key)
		return (NULL);
	klen = (int)ft_strlen(key);
	i = 0;
	while (sh->envp[i])
	{
		if (ft_strncmp(sh->envp[i], key, (size_t)klen) == 0)
		{
			if (sh->envp[i][klen] == '=')
				return (sh->envp[i] + klen + 1);
		}
		i++;
	}
	return (NULL);
}

int	env_len_bonus(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		i++;
	return (i);
}

int	env_key_is_valid_bonus(const char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	if (!is_name_start_bonus(s[0]))
		return (0);
	i = 1;
	while (s[i])
	{
		if (!is_name_char_bonus(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	env_find_key_bonus(char **envp, const char *key)
{
	int		i;
	size_t	klen;

	if (!envp || !key)
		return (-1);
	klen = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, klen) == 0
			&& (envp[i][klen] == '=' || envp[i][klen] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}
