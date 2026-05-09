/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_destroy_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:12:47 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stddef.h>
#include "env_bonus/env_bonus.h"
#include "minishell_bonus.h"
#include "types_bonus.h"

void	sh_destroy_bonus(t_shell *sh)
{
	env_free_bonus(sh->envp);
	sh->envp = NULL;
	rl_clear_history();
	sh->running = 0;
}
