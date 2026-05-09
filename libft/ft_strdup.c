/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:35:21 by skarayil          #+#    #+#             */
/*   Updated: 2026/02/10 02:14:49 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	int		index;
	char	*new_str;

	index = 0;
	while (s[index])
		index++;
	new_str = (char *)ft_gc_malloc(sizeof(char) * (index + 1));
	if (!new_str)
		return (NULL);
	index = 0;
	while (s[index])
	{
		new_str[index] = s[index];
		index++;
	}
	new_str[index] = '\0';
	return (new_str);
}
