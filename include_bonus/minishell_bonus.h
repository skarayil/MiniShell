/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:25:17 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

# ifndef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 200809L
# endif

# include "types_bonus.h"

int		sh_init_bonus(t_shell *sh, char **envp);
void	sh_loop_bonus(t_shell *sh);
void	sh_destroy_bonus(t_shell *sh);
int		sh_handle_line_bonus(t_shell *sh, char *line);
int		is_incomplete_bonus(t_shell *sh, char *line);
char	*get_input_bonus(const char *prompt, int fd);
char	*join_continuation_bonus(t_shell *sh, char *line);

#endif
