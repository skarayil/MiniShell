/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:06:18 by skarayil          #+#    #+#             */
/*   Updated: 2026/02/13 13:06:19 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../types.h"

char	**tokenize(t_shell *sh, const char *line);
char	*tok_addc(char *s, char c);
char	**tok_push(char **v, int n, char *s);
void	tok_free_all(char **v);
char	*tok_itoa_pos(int n);
int		is_ws(char c);
int		open_quote(char c);
int		is_op(char c);
void	skip_ws(const char *s, int *i);
char	*read_double_op(char c, int *i);
char	*read_single_op(char c);
char	*read_word(const char *l, int *i);

#endif
