/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:11:03 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:06 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "exec/exec.h"
#include "libft.h"
#include "minishell.h"
#include "signals/signals.h"
#include "types.h"

int	main(int ac, char **av, char **envp)
{
	t_shell	sh;
	int		rc;

	(void)av;
	if (ac != 1)
		return (write(2, "minishell: no arguments expected\n", 33), 1);
	ft_gc_init();
	rc = sh_init(&sh, envp);
	if (rc != 0)
		return (ms_gc_close_all(&sh), ft_gc_destroy(), 1);
	sig_setup(&sh);
	sh_loop(&sh);
	sh_destroy(&sh);
	ms_gc_close_all(&sh);
	ft_gc_destroy();
	return (sh.exit_code);
}
