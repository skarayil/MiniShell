/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:05:07 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:06 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include "exec/exec.h"
#include "signals/signals.h"
#include "types.h"

static void	restore_stdin(t_shell *sh, int *saved)
{
	if (*saved >= 0)
	{
		dup2(*saved, STDIN_FILENO);
		ms_gc_close_fd(sh, *saved);
		*saved = -1;
	}
}

static int	hd_open_pipe(t_shell *sh, int fd[2], int *saved)
{
	if (pipe(fd) < 0)
	{
		restore_stdin(sh, saved);
		perror("pipe");
		return (1);
	}
	ms_gc_add_fd(sh, fd[0], NULL);
	ms_gc_add_fd(sh, fd[1], NULL);
	return (0);
}

static int	hd_finish(t_shell *sh, t_redir *r, int *fd, int *saved)
{
	int	ret;

	g_sig.sig = 0;
	sig_set_mode(SM_HEREDOC);
	ret = hd_loop(sh, r, fd[1]);
	ms_gc_close_fd(sh, fd[1]);
	sig_set_mode(SM_PROMPT);
	restore_stdin(sh, saved);
	if (ret == 0)
		r->heredoc_fd = fd[0];
	else
		ms_gc_close_fd(sh, fd[0]);
	return (ret);
}

int	run_heredoc(t_shell *sh, t_redir *r)
{
	int	fd[2];
	int	saved;

	if (r->heredoc_fd >= 0)
		ms_gc_close_fd(sh, r->heredoc_fd);
	r->heredoc_fd = -1;
	saved = dup(STDIN_FILENO);
	if (saved < 0)
		return (perror("dup"), 1);
	ms_gc_add_fd(sh, saved, NULL);
	if (hd_open_pipe(sh, fd, &saved) != 0)
		return (1);
	return (hd_finish(sh, r, fd, &saved));
}
