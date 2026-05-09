/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:24:10 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/10 20:27:08 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 200809L
# endif

# include "types.h"

int		sh_init(t_shell *sh, char **envp);
void	sh_loop(t_shell *sh);
void	sh_destroy(t_shell *sh);
int		sh_handle_line(t_shell *sh, char *line);
char	*get_input(const char *prompt, int fd);
char	*join_continuation(char *line);

#endif
