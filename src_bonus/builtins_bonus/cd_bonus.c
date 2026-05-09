/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:07:07 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:09 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "builtins_bonus/builtins_bonus.h"
#include "env_bonus/env_bonus.h"
#include "libft.h"
#include "types_bonus.h"

static int	cd_err_bonus(const char *s)
{
	if (s)
		write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	return (1);
}

static char	*resolve_path_bonus(t_shell *sh, char **argv)
{
	char	*path;

	path = argv[1];
	if (!path || ft_streq(path, "--"))
	{
		path = env_get_bonus(sh, "HOME");
		if (!path)
			return ((char *)-1);
	}
	else if (ft_streq(path, "-"))
	{
		path = env_get_bonus(sh, "OLDPWD");
		if (!path)
			return ((char *)-2);
		write(1, path, ft_strlen(path));
		write(1, "\n", 1);
	}
	return (path);
}

int	ft_cd_bonus(t_shell *sh, char **argv)
{
	char	*path;
	char	cwd[4096];
	char	*oldpwd;

	if (argv[1] && argv[2] && !ft_streq(argv[1], "--"))
		return (cd_err_bonus("minishell: cd: too many arguments"));
	oldpwd = getcwd(cwd, sizeof(cwd));
	path = resolve_path_bonus(sh, argv);
	if (path == (char *)-1)
		return (cd_err_bonus("cd: HOME not set"));
	if (path == (char *)-2)
		return (cd_err_bonus("minishell: cd: OLDPWD not set"));
	if (chdir(path) != 0)
		return (perror("cd"), 1);
	if (oldpwd)
		env_set_bonus(sh, "OLDPWD", cwd);
	if (getcwd(cwd, sizeof(cwd)))
		env_set_bonus(sh, "PWD", cwd);
	return (0);
}
