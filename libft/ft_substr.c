/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:02:44 by skarayil          #+#    #+#             */
/*   Updated: 2026/02/06 21:30:22 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*mem;
	size_t	index;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	else if (ft_strlen(s) < len + start)
		len = ft_strlen(s) - start;
	mem = (char *)ft_gc_malloc((len + 1) * sizeof(char));
	if (!mem)
		return (NULL);
	index = 0;
	while (index < len && s[start + index])
	{
		mem[index] = s[start + index];
		index++;
	}
	mem[index] = '\0';
	return (mem);
}
