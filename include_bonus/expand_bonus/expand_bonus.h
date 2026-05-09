/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:25:07 by skarayil          #+#    #+#             */
/*   Updated: 2026/02/12 15:25:08 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_BONUS_H
# define EXPAND_BONUS_H

# include "../types_bonus.h"

char	*apply_expansion_bonus(t_shell *sh, char *line);
char	**expand_list_bonus(t_shell *sh, char **argv);
int		expand_redirs_bonus(t_shell *sh, t_redir *r);
char	**expand_token_bonus(t_shell *sh, char *raw);
char	**exp_arr_add_bonus(char **v, char *s);
char	*exp_char_append_bonus(char *s, char c);
char	*exp_get_key_bonus(const char *s, int *i);
char	*exp_lookup_bonus(t_shell *sh, const char *s, int *i);
int		exp_update_q_bonus(int q, char c);
int		is_name_start_bonus(char c);
int		is_name_char_bonus(char c);
char	*handle_dollar_bonus(t_shell *sh, const char *s, int *i);
void	process_val_bonus(char ***res, char **buf, char *val, int q);
void	exp_loop_bonus(t_shell *sh, char *raw, char ***res, char **buf);
int		hd_process_line_bonus(t_shell *sh, t_redir *r, char *line, int fd);
char	**expand_wildcards_bonus(char **args);
int		is_match_bonus(const char *pattern, const char *name);
char	*restore_pattern_bonus(char *s);
void	sort_list_bonus(char **list);

#endif
