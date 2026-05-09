/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:04:19 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:06 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "env/env.h"
#include "exec/exec.h"
#include "libft.h"
#include "types.h"

static void	exit_err(const char *cmd, const char *msg, int code)
{
	write(2, "minishell: ", 11);
	if (cmd)
		write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	ft_gc_destroy();
	exit(code);
}

static int	is_dir_path(const char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
		return (0);
	if (S_ISDIR(st.st_mode))
		return (1);
	return (0);
}

static char	*resolve_cmd(t_shell *sh, const char *cmd)
{
	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	return (find_in_path(sh, cmd));
}

static char	**filter_env(char **envp)
{
	int		i;
	int		n;
	char	**out;

	n = 0;
	i = -1;
	while (envp[++i])
		if (ft_strchr(envp[i], '='))
			n++;
	out = malloc(sizeof(char *) * (n + 1));
	if (!out)
		return (envp);
	n = 0;
	i = -1;
	while (envp[++i])
		if (ft_strchr(envp[i], '='))
			out[n++] = envp[i];
	out[n] = NULL;
	return (out);
}

void	exec_child_execve(t_shell *sh, char **argv)
{
	char	*path;
	char	**fenv;

	if (!argv || !argv[0])
	{
		ms_gc_close_all(sh);
		ft_gc_destroy();
		exit(0);
	}
	path = resolve_cmd(sh, argv[0]);
	if (!path)
		exit_err(argv[0], "command not found", 127);
	if (is_dir_path(path))
		exit_err(argv[0], "is a directory", 126);
	env_update_underscore(sh, path);
	fenv = filter_env(sh->envp);
	execve(path, argv, fenv);
	if (errno == ENOENT)
		exit_err(argv[0], strerror(errno), 127);
	exit_err(argv[0], strerror(errno), 126);
}
