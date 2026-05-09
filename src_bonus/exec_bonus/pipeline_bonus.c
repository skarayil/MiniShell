/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:15:29 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "exec_bonus/exec_bonus.h"
#include "libft.h"
#include "types_bonus.h"

static void	init_pl_bonus(t_ast *node, t_pl *pl)
{
	int		i;
	t_ast	*tmp;

	pl->n = 1;
	tmp = node;
	while (tmp && tmp->type == NODE_PIPE)
	{
		pl->n++;
		tmp = tmp->left;
	}
	pl->cmds = ft_gc_malloc(sizeof(t_ast *) * pl->n);
	pl->fds = ft_gc_malloc(sizeof(int *) * (pl->n - 1));
	pl->pids = ft_gc_malloc(sizeof(pid_t) * pl->n);
	i = pl->n - 1;
	tmp = node;
	while (tmp && tmp->type == NODE_PIPE)
	{
		pl->cmds[i--] = tmp->right;
		tmp = tmp->left;
	}
	pl->cmds[i] = tmp;
}

static int	create_pipes_bonus(t_shell *sh, t_pl *pl)
{
	int	i;

	i = -1;
	while (++i < pl->n - 1)
	{
		pl->fds[i] = ft_gc_malloc(sizeof(int) * 2);
		if (pipe(pl->fds[i]) < 0)
			return (perror("pipe"), 1);
		ms_gc_add_fd_bonus(sh, pl->fds[i][0], NULL);
		ms_gc_add_fd_bonus(sh, pl->fds[i][1], NULL);
	}
	return (0);
}

static void	child_pipe_io_bonus(t_shell *sh, t_pl *pl, int i)
{
	int	j;

	if (i > 0)
		dup2(pl->fds[i - 1][0], STDIN_FILENO);
	if (i < pl->n - 1)
		dup2(pl->fds[i][1], STDOUT_FILENO);
	j = -1;
	while (++j < pl->n - 1)
	{
		ms_gc_close_fd_bonus(sh, pl->fds[j][0]);
		ms_gc_close_fd_bonus(sh, pl->fds[j][1]);
	}
}

static pid_t	spawn_pl_cmd_bonus(t_shell *sh, t_pl *pl, int i)
{
	pid_t	pid;
	int		ret;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		child_pipe_io_bonus(sh, pl, i);
		ret = exec_ast_bonus(sh, pl->cmds[i]);
		ms_gc_close_all_bonus(sh);
		ft_gc_destroy();
		exit(ret);
	}
	return (pid);
}

int	exec_pipe_bonus(t_shell *sh, t_ast *node)
{
	t_pl	pl;
	int		i;
	int		s;

	init_pl_bonus(node, &pl);
	if (create_pipes_bonus(sh, &pl))
		return (1);
	i = -1;
	while (++i < pl.n)
		pl.pids[i] = spawn_pl_cmd_bonus(sh, &pl, i);
	i = -1;
	while (++i < pl.n - 1)
	{
		ms_gc_close_fd_bonus(sh, pl.fds[i][0]);
		ms_gc_close_fd_bonus(sh, pl.fds[i][1]);
	}
	i = -1;
	while (++i < pl.n - 1)
		waitpid(pl.pids[i], NULL, 0);
	waitpid(pl.pids[pl.n - 1], &s, 0);
	if (WIFEXITED(s))
		return (WEXITSTATUS(s));
	return (1);
}
