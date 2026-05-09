/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 20:32:34 by skarayil          #+#    #+#             */
/*   Updated: 2026/02/09 08:13:00 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_BONUS_H
# define SIGNALS_BONUS_H

# include "../types_bonus.h"

extern t_sig_state	g_sig;

void				sig_setup_bonus(t_shell *sh);
void				sig_child_defaults_bonus(void);
void				sig_parent_ignore_exec_bonus(void);
void				sig_parent_restore_prompt_bonus(t_shell *sh);
void				sig_set_mode_bonus(t_sigmode mode);

#endif
