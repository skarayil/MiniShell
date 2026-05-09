/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:04:09 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:06 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "builtins/builtins.h"
#include "env/env.h"
#include "exec/exec.h"
#include "expand/expand.h"
#include "libft.h"
#include "parser/parser.h"
#include "signals/signals.h"
#include "types.h"

int	exec_external(t_shell *sh, t_ast *node, char **xv)
{
	pid_t	pid;
	int		ret;

	pid = fork();
	if (pid == 0)
	{
		sig_child_defaults();
		if (redir_apply_child(sh, node->redirs))
		{
			ms_gc_close_all(sh);
			ft_gc_destroy();
			exit(1);
		}
		exec_child_execve(sh, xv);
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

int	exec_builtin(t_shell *sh, t_ast *node, char **xv)
{
	int	sin;
	int	sout;
	int	ret;

	sin = -1;
	sout = -1;
	if (redir_apply_parent(sh, node->redirs, &sin, &sout))
	{
		redir_restore_parent(sh, sin, sout);
		return (1);
	}
	ret = run_builtin(sh, xv);
	redir_restore_parent(sh, sin, sout);
	return (ret);
}

int	exec_cmd_empty(t_shell *sh, t_ast *node, char **xv)
{
	int	sin;
	int	sout;

	if (xv)
		argv_free(xv);
	if (expand_redirs(sh, node->redirs))
		return (1);
	sin = -1;
	sout = -1;
	if (redir_apply_parent(sh, node->redirs, &sin, &sout))
	{
		redir_restore_parent(sh, sin, sout);
		return (1);
	}
	redir_restore_parent(sh, sin, sout);
	return (0);
}

int	exec_cmd(t_shell *sh, t_ast *node)
{
	char	**xv;
	int		ret;

	xv = NULL;
	if (node->argv && node->argv[0])
		xv = expand_list(sh, node->argv);
	if (!xv || !xv[0])
		return (exec_cmd_empty(sh, node, xv));
	env_update_underscore(sh, xv[0]);
	if (expand_redirs(sh, node->redirs))
	{
		argv_free(xv);
		return (1);
	}
	if (is_builtin(xv[0]) && !(ft_streq(xv[0], "env") && xv[1]))
		ret = exec_builtin(sh, node, xv);
	else
		ret = exec_external(sh, node, xv);
	argv_free(xv);
	return (ret);
}
