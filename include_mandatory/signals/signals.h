/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:24:01 by skarayil          #+#    #+#             */
/*   Updated: 2026/02/12 15:24:02 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "../types.h"

extern t_sig_state	g_sig;

void				sig_setup(t_shell *sh);
void				sig_child_defaults(void);
void				sig_parent_ignore_exec(void);
void				sig_parent_restore_prompt(t_shell *sh);
void				sig_set_mode(t_sigmode mode);

#endif
