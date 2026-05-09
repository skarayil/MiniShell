/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:16:04 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:06 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>
#include "exec/exec.h"
#include "minishell.h"
#include "signals/signals.h"
#include "types.h"

static void	handle_eof(t_shell *sh)
{
	if (isatty(STDIN_FILENO))
		write(2, "exit\n", 5);
	sh->exit_code = sh->last_exit_status;
}

static void	process_line(t_shell *sh, char *line)
{
	line = join_continuation(line);
	if (line)
		sh_handle_line(sh, line);
	else
	{
		g_sig.sig = 0;
		sh->last_exit_status = 130;
	}
}

void	sh_loop(t_shell *sh)
{
	char	*line;

	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	while (sh->running)
	{
		line = get_input("minishell$ ", STDIN_FILENO);
		if (!line && g_sig.sig == SIGINT)
		{
			g_sig.sig = 0;
			sh->last_exit_status = 130;
			continue ;
		}
		if (!line)
		{
			handle_eof(sh);
			break ;
		}
		if (line[0] != '\0')
			process_line(sh, line);
		ms_gc_close_all(sh);
	}
	sh->running = 0;
}
