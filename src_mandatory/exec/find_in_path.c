/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:04:57 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:06 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <sys/stat.h>
#include <unistd.h>
#include "env/env.h"
#include "exec/exec.h"
#include "libft.h"
#include "types.h"

static int	has_slash(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static char	*join_path(const char *p, int st, int ln, const char *cmd)
{
	char	*out;
	int		i;
	int		j;

	if (ln == 0)
		return (ft_strdup(cmd));
	out = ft_gc_malloc((size_t)ln + 1 + ft_strlen(cmd) + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (i < ln)
	{
		out[i] = p[st + i];
		i++;
	}
	out[i++] = '/';
	j = 0;
	while (cmd[j])
		out[i++] = cmd[j++];
	out[i] = '\0';
	return (out);
}

static char	*try_path(char *try, char **found)
{
	struct stat	sb;

	if (!try)
		return (NULL);
	if (access(try, F_OK) != 0)
		return (NULL);
	if (stat(try, &sb) != 0 || S_ISDIR(sb.st_mode))
		return (NULL);
	if (access(try, X_OK) == 0)
		return (try);
	if (!*found)
		*found = try;
	return (NULL);
}

static char	*search_loop(const char *path, const char *cmd)
{
	int		i;
	int		st;
	char	*found;
	char	*res;

	i = 0;
	found = NULL;
	while (1)
	{
		st = i;
		while (path[i] && path[i] != ':')
			i++;
		res = try_path(join_path(path, st, i - st, cmd), &found);
		if (res)
			return (res);
		if (!path[i])
			break ;
		i++;
	}
	return (found);
}

char	*find_in_path(t_shell *sh, const char *cmd)
{
	char	*path;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (has_slash(cmd))
		return (ft_strdup(cmd));
	path = env_get(sh, "PATH");
	if (!path)
	{
		if (sh->default_path)
			return (search_loop("/usr/local/bin:/usr/bin:/bin:", cmd));
		return (search_loop("", cmd));
	}
	return (search_loop(path, cmd));
}
