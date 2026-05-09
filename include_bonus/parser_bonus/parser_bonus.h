/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:04:41 by skarayil          #+#    #+#             */
/*   Updated: 2026/02/13 13:04:42 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_BONUS_H
# define PARSER_BONUS_H

# include "../types_bonus.h"

void	argv_free_bonus(char **v);
t_ast	*new_node_bonus(t_node_type type);
void	delete_ast_bonus(t_ast *node);
int		tok_len_bonus(char **tok);
int		find_op_bonus(char **tok, int s, int e, char *op);
int		syn_err_bonus(const char *tok);
int		handle_redir_bonus(t_ast *n, char **tok, int *i, int e);
int		cmd_count_args_bonus(char **tok, int s, int e);
void	add_redir_bonus(t_ast *node, int type, char *file);
t_ast	*parse_simple_bonus(char **tok, int s, int e);
t_ast	*parse_subshell_bonus(char **tok, int s, int e);
t_ast	*parse_primary_bonus(char **tok, int s, int e);
t_ast	*parse_pipeline_scope_bonus(char **tok, int s, int e);
t_ast	*parse_logic_scope_bonus(char **tok, int s, int e);
t_ast	*parse_list_scope_bonus(char **tok, int s, int e);
t_ast	*parse_line_bonus(char **toks);
int		find_matching_paren_bonus(char **tok, int s, int e);
int		is_logic_bonus(char *s);
int		find_logic_op_bonus(char **tok, int s, int e);
int		pre_process_heredocs_bonus(t_shell *sh, t_ast *node);

#endif
