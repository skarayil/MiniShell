/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:08:43 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:06 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env/env.h"
#include "expand/expand.h"
#include "types.h"

static void	handle_tilde_case(t_exp_context *ctx)
{
	char	*home;
	int		k;

	home = env_get(ctx->sh, "HOME");
	if (!home)
		home = getenv("HOME");
	if (home)
	{
		k = 0;
		while (home[k])
			*ctx->buf = exp_char_append(*ctx->buf, home[k++]);
	}
	else
		*ctx->buf = exp_char_append(*ctx->buf, '~');
	(ctx->i)++;
}

static void	handle_backslash_case(t_exp_context *ctx)
{
	if (ctx->q == 0)
	{
		(ctx->i)++;
		if (ctx->raw[ctx->i])
			*ctx->buf = exp_char_append(*ctx->buf, ctx->raw[(ctx->i)++]);
	}
	else if (ctx->q == 2 && (ctx->raw[ctx->i + 1] == '$' || ctx->raw[ctx->i
				+ 1] == '"' || ctx->raw[ctx->i + 1] == '\\'))
	{
		(ctx->i)++;
		if (ctx->raw[ctx->i])
			*ctx->buf = exp_char_append(*ctx->buf, ctx->raw[(ctx->i)++]);
	}
	else
	{
		*ctx->buf = exp_char_append(*ctx->buf, ctx->raw[ctx->i]);
		(ctx->i)++;
	}
}

static void	handle_dollar_case(t_exp_context *ctx)
{
	char	*val;

	if (ctx->q == 0 && (ctx->raw[ctx->i + 1] == '\'' || ctx->raw[ctx->i
				+ 1] == '"'))
	{
		(ctx->i)++;
		return ;
	}
	val = handle_dollar(ctx->sh, ctx->raw, &ctx->i);
	if (val)
		process_val(ctx->res, ctx->buf, val, ctx->q);
}

static void	process_char(t_exp_context *ctx)
{
	if (ctx->i == 0 && ctx->raw[0] == '~' && ctx->q == 0
		&& (ctx->raw[1] == '\0' || ctx->raw[1] == '/'))
		return (handle_tilde_case(ctx));
	if (exp_update_q(ctx->q, ctx->raw[ctx->i]) != ctx->q)
	{
		ctx->q = exp_update_q(ctx->q, ctx->raw[(ctx->i)++]);
		return ;
	}
	if (ctx->raw[ctx->i] == '\\' && ctx->q != 1)
		return (handle_backslash_case(ctx));
	if (ctx->raw[ctx->i] == '$' && ctx->q != 1)
		return (handle_dollar_case(ctx));
	*ctx->buf = exp_char_append(*ctx->buf, ctx->raw[ctx->i]);
	(ctx->i)++;
}

void	exp_loop(t_shell *sh, char *raw, char ***res, char **buf)
{
	t_exp_context	ctx;

	ctx.sh = sh;
	ctx.raw = raw;
	ctx.res = res;
	ctx.buf = buf;
	ctx.i = 0;
	ctx.q = 0;
	while (raw[ctx.i])
		process_char(&ctx);
}
