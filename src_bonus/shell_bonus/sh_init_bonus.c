/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:12:59 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "env_bonus/env_bonus.h"
#include "minishell_bonus.h"
#include "types_bonus.h"

int	sh_init_bonus(t_shell *sh, char **envp)
{
	sh->envp = NULL;
	sh->last_exit_status = 0;
	sh->exit_code = 0;
	sh->running = 1;
	sh->default_path = 0;
	sh->fd_head = NULL;
	if (!envp || !envp[0])
	{
		sh->envp = env_init_minimal_bonus(envp);
		if (!sh->envp)
			return (sh->running = 0, 1);
		sh->default_path = 1;
		return (0);
	}
	sh->envp = env_copy_bonus(envp);
	if (!sh->envp)
		return (sh->running = 0, 1);
	if (env_increment_shlvl_bonus(&sh->envp))
		return (sh->running = 0, 1);
	return (0);
}
