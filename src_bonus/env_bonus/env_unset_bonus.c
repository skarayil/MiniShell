/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:18:45 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:09 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "env_bonus/env_bonus.h"
#include "exec_bonus/exec_bonus.h"
#include "libft.h"
#include "types_bonus.h"

static char	*get_system_path_bonus(const char *cmd)
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

int	env_update_underscore_bonus(t_shell *sh, char *val)
{
	char	*path;

	if (!val)
		return (0);
	if (ft_strchr(val, '/'))
		return (env_set_bonus(sh, "_", val));
	path = find_in_path_bonus(sh, val);
	if (!path)
		path = get_system_path_bonus(val);
	if (path)
		return (env_set_bonus(sh, "_", path));
	return (env_set_bonus(sh, "_", val));
}
