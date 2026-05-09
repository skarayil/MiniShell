/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export_print_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:19:39 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:09 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "env_bonus/env_bonus.h"
#include "libft.h"
#include "parser_bonus/parser_bonus.h"
#include "types_bonus.h"

static void	print_one_bonus(const char *s, int use_dollar)
{
	int	i;

	write(1, "declare -x ", 11);
	i = 0;
	while (s[i] && s[i] != '=')
	{
		write(1, &s[i], 1);
		i++;
	}
	if (!s[i])
	{
		write(1, "\n", 1);
		return ;
	}
	if (use_dollar && env_has_nonascii_bonus(s + i + 1))
		env_print_val_dollar_bonus(s, i + 1);
	else
		env_print_val_quoted_bonus(s, i + 1);
}

static char	**copy_env_bonus(t_shell *sh, int n)
{
	char	**v;
	int		i;

	v = ft_gc_malloc(sizeof(char *) * (n + 1));
	if (!v)
		return (NULL);
	i = 0;
	while (i < n)
	{
		v[i] = ft_strdup(sh->envp[i]);
		if (!v[i])
			return (argv_free_bonus(v), NULL);
		i++;
	}
	v[n] = NULL;
	return (v);
}

void	env_print_export_sorted_bonus(t_shell *sh)
{
	char	**v;
	int		n;
	int		i;
	int		dollar;

	n = env_len_bonus(sh->envp);
	v = copy_env_bonus(sh, n);
	if (!v)
		return ;
	env_sort_envp_bonus(v, n);
	dollar = (!env_get_bonus(sh, "LANG") && !env_get_bonus(sh, "LC_ALL")
			&& !env_get_bonus(sh, "LC_CTYPE"));
	i = 0;
	while (i < n)
	{
		if (v[i][0] != '_' || (v[i][1] != '=' && v[i][1] != '\0'))
			print_one_bonus(v[i], dollar);
		i++;
	}
	argv_free_bonus(v);
}
