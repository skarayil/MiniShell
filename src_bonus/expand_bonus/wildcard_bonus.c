/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:13:47 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stddef.h>
#include "expand_bonus/expand_bonus.h"
#include "libft.h"

static void	handle_no_matches_bonus(char *pattern, char ***res)
{
	char	*p_res;

	p_res = restore_pattern_bonus(pattern);
	*res = exp_arr_add_bonus(NULL, p_res);
}

static char	**scan_dir_bonus(DIR *dir, char *pattern)
{
	struct dirent	*entry;
	char			**res;

	res = NULL;
	entry = readdir(dir);
	while (entry)
	{
		if (ft_streq(entry->d_name, ".") || ft_streq(entry->d_name, ".."))
		{
			entry = readdir(dir);
			continue ;
		}
		if (!(entry->d_name[0] == '.' && pattern[0] != '.')
			&& is_match_bonus(pattern, entry->d_name))
			res = exp_arr_add_bonus(res, ft_strdup(entry->d_name));
		entry = readdir(dir);
	}
	return (res);
}

static char	**get_matches_bonus(char *pattern)
{
	DIR		*dir;
	char	**res;

	res = NULL;
	if (!ft_strchr(pattern, '*'))
	{
		handle_no_matches_bonus(pattern, &res);
		return (res);
	}
	dir = opendir(".");
	if (!dir)
	{
		handle_no_matches_bonus(pattern, &res);
		return (res);
	}
	res = scan_dir_bonus(dir, pattern);
	closedir(dir);
	if (!res)
		handle_no_matches_bonus(pattern, &res);
	else
		sort_list_bonus(res);
	return (res);
}

static char	**append_matches_bonus(char **final, char **matches, char *pat)
{
	int	j;

	if (!matches)
		return (exp_arr_add_bonus(final, restore_pattern_bonus(pat)));
	j = 0;
	while (matches[j])
		final = exp_arr_add_bonus(final, matches[j++]);
	return (final);
}

char	**expand_wildcards_bonus(char **args)
{
	char	**final;
	char	**matches;
	int		i;

	if (!args)
		return (NULL);
	final = NULL;
	i = 0;
	while (args[i])
	{
		matches = get_matches_bonus(args[i]);
		final = append_matches_bonus(final, matches, args[i]);
		i++;
	}
	return (final);
}
