/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_loop_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:13:15 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>
#include "exec_bonus/exec_bonus.h"
#include "minishell_bonus.h"
#include "signals_bonus/signals_bonus.h"
#include "types_bonus.h"

static void	handle_eof_bonus(t_shell *sh)
{
	if (isatty(STDIN_FILENO))
		write(2, "exit\n", 5);
	sh->exit_code = sh->last_exit_status;
}

static void	process_line_bonus(t_shell *sh, char *line)
{
	line = join_continuation_bonus(sh, line);
	if (line)
		sh_handle_line_bonus(sh, line);
	else
	{
		g_sig.sig = 0;
		sh->last_exit_status = 130;
	}
}

void	sh_loop_bonus(t_shell *sh)
{
	char	*line;

	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	while (sh->running)
	{
		line = get_input_bonus("minishell$ ", STDIN_FILENO);
		if (!line && g_sig.sig == SIGINT)
		{
			g_sig.sig = 0;
			sh->last_exit_status = 130;
			continue ;
		}
		if (!line)
		{
			handle_eof_bonus(sh);
			break ;
		}
		if (line[0] != '\0')
			process_line_bonus(sh, line);
		ms_gc_close_all_bonus(sh);
	}
	sh->running = 0;
}
