/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handle_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:14:40 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:10 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env_bonus/env_bonus.h"
#include "expand_bonus/expand_bonus.h"
#include "types_bonus.h"

static void	handle_tilde_case_bonus(t_exp_context *ctx)
{
	char	*home;
	int		k;

	home = env_get_bonus(ctx->sh, "HOME");
	if (!home)
		home = getenv("HOME");
	if (home)
	{
		k = 0;
		while (home[k])
			*ctx->buf = exp_char_append_bonus(*ctx->buf, home[k++]);
	}
	else
		*ctx->buf = exp_char_append_bonus(*ctx->buf, '~');
	(ctx->i)++;
}

static void	handle_backslash_case_bonus(t_exp_context *ctx)
{
	if (ctx->q == 0)
	{
		(ctx->i)++;
		if (ctx->raw[ctx->i])
		{
			if (ctx->raw[ctx->i] == '*')
				*ctx->buf = exp_char_append_bonus(*ctx->buf, QUOTE_MARKER);
			else
				*ctx->buf = exp_char_append_bonus(*ctx->buf, ctx->raw[ctx->i]);
			(ctx->i)++;
		}
	}
	else if (ctx->q == 2 && (ctx->raw[ctx->i + 1] == '$' || ctx->raw[ctx->i
				+ 1] == '"' || ctx->raw[ctx->i + 1] == '\\'))
	{
		(ctx->i)++;
		if (ctx->raw[ctx->i])
			*ctx->buf = exp_char_append_bonus(*ctx->buf, ctx->raw[(ctx->i)++]);
	}
	else
	{
		*ctx->buf = exp_char_append_bonus(*ctx->buf, ctx->raw[ctx->i]);
		(ctx->i)++;
	}
}

static void	handle_dollar_case_bonus(t_exp_context *ctx)
{
	char	*val;

	if (ctx->q == 0 && (ctx->raw[ctx->i + 1] == '\'' || ctx->raw[ctx->i
				+ 1] == '"'))
	{
		(ctx->i)++;
		return ;
	}
	val = handle_dollar_bonus(ctx->sh, ctx->raw, &ctx->i);
	if (val)
		process_val_bonus(ctx->res, ctx->buf, val, ctx->q);
}

static void	process_char_bonus(t_exp_context *ctx)
{
	if (ctx->i == 0 && ctx->raw[0] == '~' && ctx->q == 0
		&& (ctx->raw[1] == '\0' || ctx->raw[1] == '/'))
		return (handle_tilde_case_bonus(ctx));
	if (exp_update_q_bonus(ctx->q, ctx->raw[ctx->i]) != ctx->q)
	{
		ctx->q = exp_update_q_bonus(ctx->q, ctx->raw[(ctx->i)++]);
		return ;
	}
	if (ctx->raw[ctx->i] == '\\' && ctx->q != 1)
		return (handle_backslash_case_bonus(ctx));
	if (ctx->raw[ctx->i] == '$' && ctx->q != 1)
		return (handle_dollar_case_bonus(ctx));
	if (ctx->raw[ctx->i] == '*' && ctx->q != 0)
	{
		*ctx->buf = exp_char_append_bonus(*ctx->buf, QUOTE_MARKER);
		(ctx->i)++;
		return ;
	}
	*ctx->buf = exp_char_append_bonus(*ctx->buf, ctx->raw[ctx->i]);
	(ctx->i)++;
}

void	exp_loop_bonus(t_shell *sh, char *raw, char ***res, char **buf)
{
	t_exp_context	ctx;

	ctx.sh = sh;
	ctx.raw = raw;
	ctx.res = res;
	ctx.buf = buf;
	ctx.i = 0;
	ctx.q = 0;
	while (raw[ctx.i])
		process_char_bonus(&ctx);
}
