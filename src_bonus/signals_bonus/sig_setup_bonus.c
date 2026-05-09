/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_setup_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:12:03 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 18:37:23 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include <readline/readline.h>
#include <signal.h>
#include <stddef.h>
#include <unistd.h>
#include "signals_bonus/signals_bonus.h"
#include "types_bonus.h"

t_sig_state	g_sig = {0, SM_PROMPT};

static void	sig_on_int_bonus(int signo)
{
	(void)signo;
	g_sig.sig = SIGINT;
	if (g_sig.mode == SM_PROMPT)
	{
		write(1, "^C", 2);
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	else if (g_sig.mode == SM_HEREDOC)
	{
		write(1, "^C", 2);
		rl_done = 1;
		close(STDIN_FILENO);
	}
}

void	sig_setup_bonus(t_shell *sh)
{
	struct sigaction	sa;

	(void)sh;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = sig_on_int_bonus;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
