/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:03:11 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:06 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "env/env.h"
#include "expand/expand.h"
#include "libft.h"
#include "types.h"

char	*env_get(t_shell *sh, const char *key)
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

int	env_len(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		i++;
	return (i);
}

int	env_key_is_valid(const char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	if (!is_name_start(s[0]))
		return (0);
	i = 1;
	while (s[i])
	{
		if (!is_name_char(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	env_find_key(char **envp, const char *key)
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
