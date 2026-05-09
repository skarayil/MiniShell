/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_ops_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:15:05 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include "exec_bonus/exec_bonus.h"
#include "libft.h"
#include "types_bonus.h"

int	op_in_bonus(t_shell *sh, char *file, int *saved)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror(file), 1);
	ms_gc_add_fd_bonus(sh, fd, NULL);
	if (saved && *saved < 0)
	{
		*saved = dup(STDIN_FILENO);
		if (*saved < 0)
			return (ms_gc_close_fd_bonus(sh, fd), perror("dup"), 1);
		ms_gc_add_fd_bonus(sh, *saved, NULL);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		return (ms_gc_close_fd_bonus(sh, fd), perror("dup2"), 1);
	ms_gc_close_fd_bonus(sh, fd);
	return (0);
}

int	op_out_bonus(t_shell *sh, t_redir *r, int *saved)
{
	int	fd;
	int	fl;
	int	target;

	fl = O_WRONLY | O_CREAT | O_TRUNC;
	if (r->type == R_APP)
		fl = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(r->file, fl, 0666);
	if (fd < 0)
		return (perror(r->file), 1);
	ms_gc_add_fd_bonus(sh, fd, NULL);
	target = STDOUT_FILENO;
	if (r->redir_fd >= 0)
		target = r->redir_fd;
	if (saved && *saved < 0 && target == STDOUT_FILENO)
	{
		*saved = dup(STDOUT_FILENO);
		if (*saved < 0)
			return (ms_gc_close_fd_bonus(sh, fd), perror("dup"), 1);
		ms_gc_add_fd_bonus(sh, *saved, NULL);
	}
	if (dup2(fd, target) < 0)
		return (ms_gc_close_fd_bonus(sh, fd), perror("dup2"), 1);
	ms_gc_close_fd_bonus(sh, fd);
	return (0);
}

int	op_heredoc_bonus(t_shell *sh, t_redir *r, int *saved)
{
	if (r->heredoc_fd < 0)
		return (0);
	if (saved && *saved < 0)
	{
		*saved = dup(STDIN_FILENO);
		if (*saved < 0)
			return (perror("dup"), 1);
		ms_gc_add_fd_bonus(sh, *saved, NULL);
	}
	if (dup2(r->heredoc_fd, STDIN_FILENO) < 0)
		return (perror("dup2"), 1);
	close(r->heredoc_fd);
	ms_gc_remove_fd_bonus(sh, r->heredoc_fd);
	r->heredoc_fd = -1;
	return (0);
}

int	op_in_out_bonus(t_shell *sh, char *file, int *saved_in)
{
	int	fd;

	fd = open(file, O_RDWR | O_CREAT, 0666);
	if (fd < 0)
		return (perror(file), 1);
	ms_gc_add_fd_bonus(sh, fd, NULL);
	if (saved_in && *saved_in < 0)
	{
		*saved_in = dup(STDIN_FILENO);
		if (*saved_in < 0)
			return (ms_gc_close_fd_bonus(sh, fd), perror("dup"), 1);
		ms_gc_add_fd_bonus(sh, *saved_in, NULL);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		return (ms_gc_close_fd_bonus(sh, fd), perror("dup2"), 1);
	ms_gc_close_fd_bonus(sh, fd);
	return (0);
}

void	run_herestring_bonus(t_shell *sh, t_redir *r)
{
	int		fd[2];
	char	*val;

	if (r->heredoc_fd >= 0)
		ms_gc_close_fd_bonus(sh, r->heredoc_fd);
	r->heredoc_fd = -1;
	if (pipe(fd) < 0)
		return (perror("pipe"));
	ms_gc_add_fd_bonus(sh, fd[0], NULL);
	ms_gc_add_fd_bonus(sh, fd[1], NULL);
	val = r->file;
	write(fd[1], val, ft_strlen(val));
	write(fd[1], "\n", 1);
	ms_gc_close_fd_bonus(sh, fd[1]);
	ms_gc_remove_fd_bonus(sh, fd[0]);
	r->heredoc_fd = fd[0];
}
