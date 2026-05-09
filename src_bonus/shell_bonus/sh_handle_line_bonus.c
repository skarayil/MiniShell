/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_handle_line_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:12:53 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <unistd.h>
#include "exec_bonus/exec_bonus.h"
#include "lexer_bonus/lexer_bonus.h"
#include "minishell_bonus.h"
#include "parser_bonus/parser_bonus.h"
#include "signals_bonus/signals_bonus.h"
#include "types_bonus.h"

static void	free_toks_bonus(char **t)
{
	(void)t;
}

static int	handle_parse_err_bonus(t_shell *sh)
{
	sh->last_exit_status = 2;
	sh->exit_code = 2;
	if (!isatty(STDIN_FILENO))
		sh->running = 0;
	return (2);
}

static int	run_ast_bonus(t_shell *sh, t_ast *ast)
{
	if (pre_process_heredocs_bonus(sh, ast) != 0)
	{
		sh->exit_code = sh->last_exit_status;
		delete_ast_bonus(ast);
		return (0);
	}
	sig_parent_ignore_exec_bonus();
	sh->last_exit_status = exec_ast_bonus(sh, ast);
	sig_parent_restore_prompt_bonus(sh);
	delete_ast_bonus(ast);
	return (0);
}

int	sh_handle_line_bonus(t_shell *sh, char *line)
{
	char	**tok;
	t_ast	*ast;

	if (line && line[0])
		add_history(line);
	tok = tokenize_bonus(sh, line);
	if (!tok)
		return (0);
	if (!tok[0])
		return (free_toks_bonus(tok), 0);
	ast = parse_line_bonus(tok);
	free_toks_bonus(tok);
	if (!ast)
		return (handle_parse_err_bonus(sh));
	return (run_ast_bonus(sh, ast));
}
