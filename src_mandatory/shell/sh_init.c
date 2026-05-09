/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:15:57 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:06 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "env/env.h"
#include "minishell.h"
#include "types.h"

int	sh_init(t_shell *sh, char **envp)
{
	sh->envp = NULL;
	sh->last_exit_status = 0;
	sh->exit_code = 0;
	sh->running = 1;
	sh->default_path = 0;
	sh->fd_head = NULL;
	if (!envp || !envp[0])
	{
		sh->envp = env_init_minimal(envp);
		if (!sh->envp)
			return (sh->running = 0, 1);
		sh->default_path = 1;
		return (0);
	}
	sh->envp = env_copy(envp);
	if (!sh->envp)
		return (sh->running = 0, 1);
	if (env_increment_shlvl(&sh->envp))
		return (sh->running = 0, 1);
	return (0);
}
