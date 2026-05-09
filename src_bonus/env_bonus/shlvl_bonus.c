/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:18:34 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:09 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "env_bonus/env_bonus.h"
#include "libft.h"

static int	shlvl_parse_sign_bonus(const char **s)
{
	int	sign;

	sign = 1;
	while (**s == ' ' || **s == '\t')
		(*s)++;
	if (**s == '+' || **s == '-')
	{
		if (**s == '-')
			sign = -1;
		(*s)++;
	}
	return (sign);
}

static int	shlvl_next_bonus(const char *s, int *out)
{
	long	n;
	int		sign;

	if (!s || !*s)
		return (0);
	sign = shlvl_parse_sign_bonus(&s);
	if (!*s)
		return (0);
	n = 0;
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		n = (n * 10) + (*s - '0');
		if (n >= 1000)
			break ;
		s++;
	}
	n = n * sign;
	if (n < 0 || n >= 1000)
		*out = 1;
	else
		*out = (int)n + 1;
	return (1);
}

static int	env_add_shlvl_one_bonus(char ***env_ptr)
{
	char	**new_env;
	int		len;
	int		i;

	if (!env_ptr)
		return (1);
	len = env_len_bonus(*env_ptr);
	new_env = ft_gc_malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (1);
	i = 0;
	while (i < len)
	{
		new_env[i] = (*env_ptr)[i];
		i++;
	}
	new_env[i] = ft_strdup("SHLVL=1");
	if (!new_env[i])
		return (1);
	new_env[i + 1] = NULL;
	*env_ptr = new_env;
	return (0);
}

static int	do_shlvl_incr_bonus(char ***env, int i)
{
	int		new_lvl;
	char	*num;
	char	*line;

	if ((*env)[i][5] == '=')
	{
		if (!shlvl_next_bonus((*env)[i] + 6, &new_lvl))
			new_lvl = 1;
	}
	else
		new_lvl = 1;
	num = ft_itoa(new_lvl);
	if (!num)
		return (1);
	line = ft_strjoin("SHLVL=", num);
	if (!line)
		return (1);
	(*env)[i] = line;
	return (0);
}

int	env_increment_shlvl_bonus(char ***env)
{
	int	i;

	if (!env || !*env)
		return (env_add_shlvl_one_bonus(env));
	i = 0;
	while ((*env)[i])
	{
		if ((ft_strncmp((*env)[i], "SHLVL=", 6) == 0)
			|| (ft_strncmp((*env)[i], "SHLVL", 6) == 0))
			return (do_shlvl_incr_bonus(env, i));
		i++;
	}
	return (env_add_shlvl_one_bonus(env));
}
