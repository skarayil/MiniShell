/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:17:26 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:09 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "builtins_bonus/builtins_bonus.h"
#include "env_bonus/env_bonus.h"
#include "exec_bonus/exec_bonus.h"
#include "expand_bonus/expand_bonus.h"
#include "libft.h"
#include "parser_bonus/parser_bonus.h"
#include "signals_bonus/signals_bonus.h"
#include "types_bonus.h"

int	exec_external_bonus(t_shell *sh, t_ast *node, char **xv)
{
	pid_t	pid;
	int		ret;

	pid = fork();
	if (pid == 0)
	{
		sig_child_defaults_bonus();
		if (redir_apply_child_bonus(sh, node->redirs))
		{
			ms_gc_close_all_bonus(sh);
			ft_gc_destroy();
			exit(1);
		}
		exec_child_execve_bonus(sh, xv);
	}
	waitpid(pid, &ret, 0);
	if (WIFEXITED(ret))
		return (WEXITSTATUS(ret));
	if (WIFSIGNALED(ret))
	{
		if (WTERMSIG(ret) == SIGINT)
			write(1, "\n", 1);
		return (128 + WTERMSIG(ret));
	}
	return (ret);
}

int	exec_builtin_bonus(t_shell *sh, t_ast *node, char **xv)
{
	int	sin;
	int	sout;
	int	ret;

	sin = -1;
	sout = -1;
	if (redir_apply_parent_bonus(sh, node->redirs, &sin, &sout))
	{
		redir_restore_parent_bonus(sh, sin, sout);
		return (1);
	}
	ret = run_builtin_bonus(sh, xv);
	redir_restore_parent_bonus(sh, sin, sout);
	return (ret);
}

int	exec_cmd_empty_bonus(t_shell *sh, t_ast *node, char **xv)
{
	int	sin;
	int	sout;

	if (xv)
		argv_free_bonus(xv);
	if (expand_redirs_bonus(sh, node->redirs))
		return (1);
	sin = -1;
	sout = -1;
	if (redir_apply_parent_bonus(sh, node->redirs, &sin, &sout))
	{
		redir_restore_parent_bonus(sh, sin, sout);
		return (1);
	}
	redir_restore_parent_bonus(sh, sin, sout);
	return (0);
}

int	exec_cmd_bonus(t_shell *sh, t_ast *node)
{
	char	**xv;
	int		ret;

	xv = NULL;
	if (node->argv && node->argv[0])
		xv = expand_list_bonus(sh, node->argv);
	if (!xv || !xv[0])
		return (exec_cmd_empty_bonus(sh, node, xv));
	env_update_underscore_bonus(sh, xv[0]);
	if (expand_redirs_bonus(sh, node->redirs))
	{
		argv_free_bonus(xv);
		return (1);
	}
	if (is_builtin_bonus(xv[0]) && !(ft_streq(xv[0], "env") && xv[1]))
		ret = exec_builtin_bonus(sh, node, xv);
	else
		ret = exec_external_bonus(sh, node, xv);
	argv_free_bonus(xv);
	return (ret);
}
