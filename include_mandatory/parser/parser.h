/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:06:28 by skarayil          #+#    #+#             */
/*   Updated: 2026/02/13 13:06:29 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../types.h"

void	argv_free(char **v);
t_ast	*new_node(t_node_type type);
void	delete_ast(t_ast *node);
int		tok_len(char **tok);
int		find_op(char **tok, int s, int e, char *op);
int		syn_err(const char *tok);
int		handle_redir(t_ast *n, char **tok, int *i, int e);
void	add_redir(t_ast *node, int type, char *file);
t_ast	*parse_simple(char **tok, int s, int e);
t_ast	*parse_primary(char **tok, int s, int e);
t_ast	*parse_pipeline_scope(char **tok, int s, int e);
t_ast	*parse_line(char **toks);
int		cmd_count_args(char **tok, int s, int e);
int		pre_process_heredocs(t_shell *sh, t_ast *node);

#endif
