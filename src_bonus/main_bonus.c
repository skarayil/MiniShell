/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:11:52 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "exec_bonus/exec_bonus.h"
#include "libft.h"
#include "minishell_bonus.h"
#include "signals_bonus/signals_bonus.h"
#include "types_bonus.h"

int	main(int ac, char **av, char **envp)
{
	t_shell	sh;
	int		rc;

	(void)av;
	if (ac != 1)
		return (write(2, "minishell: no arguments expected\n", 33), 1);
	ft_gc_init();
	rc = sh_init_bonus(&sh, envp);
	if (rc != 0)
		return (ms_gc_close_all_bonus(&sh), ft_gc_destroy(), 1);
	sig_setup_bonus(&sh);
	sh_loop_bonus(&sh);
	sh_destroy_bonus(&sh);
	ms_gc_close_all_bonus(&sh);
	ft_gc_destroy();
	return (sh.exit_code);
}
