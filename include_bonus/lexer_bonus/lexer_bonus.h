/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:04:32 by skarayil          #+#    #+#             */
/*   Updated: 2026/02/13 13:04:33 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_BONUS_H
# define LEXER_BONUS_H

# include "../types_bonus.h"

char	**tokenize_bonus(t_shell *sh, const char *line);
char	*tok_addc_bonus(char *s, char c);
char	**tok_push_bonus(char **v, int n, char *s);
void	tok_free_all_bonus(char **v);
char	*tok_itoa_pos_bonus(int n);
int		is_ws_bonus(char c);
int		open_quote_bonus(char c);
int		is_op_bonus(char c);
void	skip_ws_bonus(const char *s, int *i);
char	*read_double_op_bonus(char c, int *i);
char	*read_single_op_bonus(char c);
char	*read_word_bonus(const char *l, int *i);

#endif
