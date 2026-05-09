/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:07:39 by skarayil          #+#    #+#             */
/*   Updated: 2026/04/12 00:03:09 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_bonus/builtins_bonus.h"
#include "libft.h"

int	exit_is_num_bonus(const char *s)
{
	int	i;

	if (!s || s[0] == '\0')
		return (0);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	overflow_digits_bonus(const char *str, int i, int sign)
{
	unsigned long long	res;

	res = 0;
	while (str[i])
	{
		res = res * 10 + (str[i] - '0');
		if (sign == 1 && res > 9223372036854775807ULL)
			return (1);
		if (sign == -1 && res > 9223372036854775808ULL)
			return (1);
		i++;
	}
	return (0);
}

int	exit_check_overflow_bonus(const char *str)
{
	int	sign;
	int	i;

	i = 0;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] == '0')
		i++;
	if (ft_strlen(str + i) > 19)
		return (1);
	return (overflow_digits_bonus(str, i, sign));
}

int	exit_to_code_bonus(const char *s)
{
	unsigned long long	n;
	int					sign;
	int					i;

	n = 0;
	sign = 1;
	i = 0;
	if (s[i] == '-')
		sign = -1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
		n = n * 10 + (s[i++] - '0');
	return ((int)((long long)(n * sign)));
}
