/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:23:33 by skarayil          #+#    #+#             */
/*   Updated: 2026/02/12 15:23:34 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "../types.h"

char	*apply_expansion(t_shell *sh, char *line);
char	**expand_list(t_shell *sh, char **argv);
int		expand_redirs(t_shell *sh, t_redir *r);
char	**expand_token(t_shell *sh, char *raw);
char	**exp_arr_add(char **v, char *s);
char	*exp_char_append(char *s, char c);
char	*exp_get_key(const char *s, int *i);
char	*exp_lookup(t_shell *sh, const char *s, int *i);
int		exp_update_q(int q, char c);
int		is_name_start(char c);
int		is_name_char(char c);
char	*handle_dollar(t_shell *sh, const char *s, int *i);
void	process_val(char ***res, char **buf, char *val, int q);
void	exp_loop(t_shell *sh, char *raw, char ***res, char **buf);
int		hd_process_line(t_shell *sh, t_redir *r, char *line, int fd);

#endif
