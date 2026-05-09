/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:03:21 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/11 00:33:06 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "env/env.h"
#include "libft.h"

static int	fill_minimal_env(char **env, char *pwd)
{
	env[0] = ft_strdup("OLDPWD");
	if (!env[0])
		return (1);
	env[1] = pwd;
	env[2] = ft_strdup("SHLVL=1");
	if (!env[2])
		return (1);
	env[3] = ft_strdup("_=./minishell");
	if (!env[3])
		return (1);
	env[4] = NULL;
	return (0);
}

char	**env_init_minimal(char **envp)
{
	char	**env;
	char	*cwd;
	char	*pwd;

	(void)envp;
	env = ft_gc_malloc(sizeof(char *) * 5);
	if (!env)
		return (NULL);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (env_free(env), NULL);
	pwd = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (!pwd)
		return (env_free(env), NULL);
	if (fill_minimal_env(env, pwd))
		return (env_free(env), NULL);
	return (env);
}

char	**env_copy(char **envp)
{
	char	**copy;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	copy = ft_gc_malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
			return (env_free(copy), NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	env_free(char **envp)
{
	(void)envp;
}
