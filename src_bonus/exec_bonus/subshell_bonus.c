/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "exec_bonus/exec_bonus.h"
#include "libft.h"
#include "signals_bonus/signals_bonus.h"
#include "types_bonus.h"

int	exec_subshell_bonus(t_shell *sh, t_ast *node)
{
	pid_t	pid;
	int		status;
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
		ret = exec_ast_bonus(sh, node->left);
		ms_gc_close_all_bonus(sh);
		ft_gc_destroy();
		exit(ret);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
