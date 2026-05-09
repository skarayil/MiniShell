/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:18:57 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:09 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "env_bonus/env_bonus.h"
#include "libft.h"
#include "types_bonus.h"

static char	*mk_entry_bonus(const char *k, const char *v)
{
	size_t	kl;
	size_t	vl;
	char	*s;

	if (!v)
		return (ft_strdup(k));
	kl = ft_strlen(k);
	vl = ft_strlen(v);
	s = ft_gc_malloc(kl + vl + 2);
	if (!s)
		return (NULL);
	ft_memcpy(s, k, kl);
	s[kl] = '=';
	ft_memcpy(s + kl + 1, v, vl);
	s[kl + 1 + vl] = '\0';
	return (s);
}

static int	env_append_bonus(t_shell *sh, char *entry)
{
	int		n;
	char	**newp;
	int		i;

	n = env_len_bonus(sh->envp);
	newp = ft_gc_malloc(sizeof(char *) * (n + 2));
	if (!newp)
		return (1);
	i = 0;
	while (i < n)
	{
		newp[i] = sh->envp[i];
		i++;
	}
	newp[n] = entry;
	newp[n + 1] = NULL;
	sh->envp = newp;
	return (0);
}

int	env_set_bonus(t_shell *sh, const char *key, const char *val)
{
	int		i;
	char	*entry;

	if (!sh || !key)
		return (1);
	i = env_find_key_bonus(sh->envp, key);
	entry = mk_entry_bonus(key, val);
	if (!entry)
		return (1);
	if (i >= 0)
	{
		sh->envp[i] = entry;
		return (0);
	}
	return (env_append_bonus(sh, entry));
}

int	env_unset_bonus(t_shell *sh, const char *key)
{
	int	i;

	if (!sh || !key)
		return (1);
	i = env_find_key_bonus(sh->envp, key);
	if (i < 0)
		return (0);
	while (sh->envp[i + 1])
	{
		sh->envp[i] = sh->envp[i + 1];
		i++;
	}
	sh->envp[i] = NULL;
	return (0);
}
