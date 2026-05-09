/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:03:41 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:06 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "env/env.h"
#include "exec/exec.h"
#include "libft.h"
#include "types.h"

static char	*get_system_path(const char *cmd)
{
	char	*path;

	path = ft_strjoin("/usr/bin/", cmd);
	if (path)
	{
		if (access(path, X_OK) == 0)
			return (path);
	}
	path = ft_strjoin("/bin/", cmd);
	if (path)
	{
		if (access(path, X_OK) == 0)
			return (path);
	}
	return (NULL);
}

int	env_update_underscore(t_shell *sh, char *val)
{
	char	*path;

	if (!val)
		return (0);
	if (ft_strchr(val, '/'))
		return (env_set(sh, "_", val));
	path = find_in_path(sh, val);
	if (!path)
		path = get_system_path(val);
	if (path)
		return (env_set(sh, "_", path));
	return (env_set(sh, "_", val));
}
