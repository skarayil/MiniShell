/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:07:45 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:09 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "builtins_bonus/builtins_bonus.h"
#include "env_bonus/env_bonus.h"
#include "libft.h"
#include "types_bonus.h"

static int	export_err_bonus(const char *arg)
{
	write(2, "minishell: export: `", 20);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
	return (1);
}

static int	handle_append_bonus(t_shell *sh, const char *arg, char *plus)
{
	char	*key;
	char	*old;
	char	*nval;

	key = ft_substr(arg, 0, (int)(plus - arg));
	if (!key)
		return (1);
	if (!env_key_is_valid_bonus(key))
		return (export_err_bonus(arg));
	old = env_get_bonus(sh, key);
	if (!old)
		old = "";
	nval = ft_strjoin(old, plus + 2);
	if (!nval)
		return (1);
	return (env_set_bonus(sh, key, nval));
}

static int	do_one_bonus(t_shell *sh, const char *arg)
{
	char	*eq;
	char	*plus;
	char	*key;

	plus = ft_strnstr(arg, "+=", ft_strlen(arg));
	if (plus)
		return (handle_append_bonus(sh, arg, plus));
	eq = ft_strchr(arg, '=');
	if (!eq)
	{
		if (!env_key_is_valid_bonus(arg))
			return (export_err_bonus(arg));
		if (env_find_key_bonus(sh->envp, arg) >= 0)
			return (0);
		return (env_set_bonus(sh, arg, NULL));
	}
	key = ft_substr(arg, 0, (int)(eq - arg));
	if (!key)
		return (1);
	if (!env_key_is_valid_bonus(key))
		return (export_err_bonus(arg));
	return (env_set_bonus(sh, key, eq + 1));
}

static int	export_opt_err_bonus(char **argv)
{
	write(2, "minishell: export: -", 20);
	if (argv[1][1])
	{
		write(2, &argv[1][1], 1);
		write(2, ": invalid option\n", 17);
	}
	else
		write(2, ": invalid option\n", 17);
	return (2);
}

int	ft_export_bonus(t_shell *sh, char **argv)
{
	int	i;
	int	rc;

	if (!argv[1])
		return (env_print_export_sorted_bonus(sh), 0);
	if (argv[1][0] == '-')
		return (export_opt_err_bonus(argv));
	i = 1;
	rc = 0;
	while (argv[i])
	{
		if (do_one_bonus(sh, argv[i]) != 0)
			rc = 1;
		i++;
	}
	return (rc);
}
