/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_handle_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:15:47 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:06 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <unistd.h>
#include "exec/exec.h"
#include "lexer/lexer.h"
#include "minishell.h"
#include "parser/parser.h"
#include "signals/signals.h"
#include "types.h"

static void	free_toks(char **t)
{
	(void)t;
}

static int	handle_parse_err(t_shell *sh)
{
	sh->last_exit_status = 2;
	sh->exit_code = 2;
	if (!isatty(STDIN_FILENO))
		sh->running = 0;
	return (2);
}

static int	run_ast(t_shell *sh, t_ast *ast)
{
	if (pre_process_heredocs(sh, ast) != 0)
	{
		sh->exit_code = sh->last_exit_status;
		delete_ast(ast);
		return (0);
	}
	sig_parent_ignore_exec();
	sh->last_exit_status = exec_ast(sh, ast);
	sig_parent_restore_prompt(sh);
	delete_ast(ast);
	return (0);
}

int	sh_handle_line(t_shell *sh, char *line)
{
	char	**tok;
	t_ast	*ast;

	if (line && line[0])
		add_history(line);
	tok = tokenize(sh, line);
	if (!tok)
		return (0);
	if (!tok[0])
		return (free_toks(tok), 0);
	ast = parse_line(tok);
	free_toks(tok);
	if (!ast)
		return (handle_parse_err(sh));
	return (run_ast(sh, ast));
}
