/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_apply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:05:41 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:06 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "exec/exec.h"
#include "types.h"

static int	apply_one_child(t_shell *sh, t_redir *r)
{
	if (r->type == R_HEREDOC)
		return (op_heredoc(sh, r, NULL));
	if (r->type == R_IN)
		return (op_in(sh, r->file, NULL));
	if (r->type == R_OUT || r->type == R_APP)
		return (op_out(sh, r, NULL));
	if (r->type == R_INOUT)
		return (op_in_out(sh, r->file, NULL));
	return (0);
}

int	redir_apply_child(t_shell *sh, t_redir *r)
{
	while (r)
	{
		if (apply_one_child(sh, r))
			return (1);
		r = r->next;
	}
	return (0);
}

static int	apply_one_parent(t_shell *sh, t_redir *r, int *si, int *so)
{
	if (r->type == R_HEREDOC)
		return (op_heredoc(sh, r, si));
	if (r->type == R_IN)
		return (op_in(sh, r->file, si));
	if (r->type == R_OUT || r->type == R_APP)
		return (op_out(sh, r, so));
	if (r->type == R_INOUT)
		return (op_in_out(sh, r->file, si));
	return (0);
}

int	redir_apply_parent(t_shell *sh, t_redir *r, int *save_in,
		int *save_out)
{
	*save_in = -1;
	*save_out = -1;
	while (r)
	{
		if (apply_one_parent(sh, r, save_in, save_out))
			return (1);
		r = r->next;
	}
	return (0);
}

void	redir_restore_parent(t_shell *sh, int save_in, int save_out)
{
	if (save_in >= 0)
	{
		dup2(save_in, STDIN_FILENO);
		ms_gc_close_fd(sh, save_in);
	}
	if (save_out >= 0)
	{
		dup2(save_out, STDOUT_FILENO);
		ms_gc_close_fd(sh, save_out);
	}
}
