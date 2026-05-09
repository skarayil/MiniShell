/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:18:08 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:09 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "exec_bonus/exec_bonus.h"
#include "libft.h"
#include "signals_bonus/signals_bonus.h"
#include "types_bonus.h"

static void	exec_bg_child_bonus(t_shell *sh, t_ast *node)
{
	int	ret;

	sig_child_defaults_bonus();
	if (redir_apply_child_bonus(sh, node->redirs))
	{
		ms_gc_close_all_bonus(sh);
		ft_gc_destroy();
		exit(1);
	}
	if (node->left)
	{
		ret = exec_ast_bonus(sh, node->left);
		ms_gc_close_all_bonus(sh);
		ft_gc_destroy();
		exit(ret);
	}
	ms_gc_close_all_bonus(sh);
	ft_gc_destroy();
	exit(0);
}

static int	exec_bg_bonus(t_shell *sh, t_ast *node)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		exec_bg_child_bonus(sh, node);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

static int	exec_logic_bonus(t_shell *sh, t_ast *node)
{
	int	ret;

	ret = exec_ast_bonus(sh, node->left);
	if (node->type == NODE_AND && ret == 0)
		ret = exec_ast_bonus(sh, node->right);
	else if (node->type == NODE_OR && ret != 0)
		ret = exec_ast_bonus(sh, node->right);
	return (ret);
}

static int	exec_seq_bonus(t_shell *sh, t_ast *node)
{
	int	ret;

	ret = exec_ast_bonus(sh, node->left);
	if (node->right)
		ret = exec_ast_bonus(sh, node->right);
	return (ret);
}

int	exec_ast_bonus(t_shell *sh, t_ast *node)
{
	if (!node)
		return (0);
	if (node->type == NODE_PIPE)
		return (exec_pipe_bonus(sh, node));
	if (node->type == NODE_BG)
		return (exec_bg_bonus(sh, node));
	if (node->type == NODE_AND || node->type == NODE_OR)
		return (exec_logic_bonus(sh, node));
	if (node->type == NODE_SUBSHELL)
		return (exec_subshell_bonus(sh, node));
	if (node->type == NODE_SEQ)
		return (exec_seq_bonus(sh, node));
	return (exec_cmd_bonus(sh, node));
}
