/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:13:49 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:05 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "builtins/builtins.h"
#include "env/env.h"
#include "libft.h"
#include "types.h"

static int	cd_err(const char *s)
{
	if (s)
		write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	return (1);
}

static char	*resolve_path(t_shell *sh, char **argv)
{
	char	*path;

	path = argv[1];
	if (!path || ft_streq(path, "--"))
	{
		path = env_get(sh, "HOME");
		if (!path)
			return ((char *)-1);
	}
	else if (ft_streq(path, "-"))
	{
		path = env_get(sh, "OLDPWD");
		if (!path)
			return ((char *)-2);
		write(1, path, ft_strlen(path));
		write(1, "\n", 1);
	}
	return (path);
}

int	ft_cd(t_shell *sh, char **argv)
{
	char	*path;
	char	cwd[4096];
	char	*oldpwd;

	if (argv[1] && argv[2] && !ft_streq(argv[1], "--"))
		return (cd_err("minishell: cd: too many arguments"));
	oldpwd = getcwd(cwd, sizeof(cwd));
	path = resolve_path(sh, argv);
	if (path == (char *)-1)
		return (cd_err("cd: HOME not set"));
	if (path == (char *)-2)
		return (cd_err("minishell: cd: OLDPWD not set"));
	if (chdir(path) != 0)
		return (perror("cd"), 1);
	if (oldpwd)
		env_set(sh, "OLDPWD", cwd);
	if (getcwd(cwd, sizeof(cwd)))
		env_set(sh, "PWD", cwd);
	return (0);
}
