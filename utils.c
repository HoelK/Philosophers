/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 01:52:09 by hkeromne          #+#    #+#             */
/*   Updated: 2025/12/07 03:38:59 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

bool	ft_isnumber(char *s)
{
	if (!s || !*s)
		return (false);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (false);
		s++;
	}
	return (true);
}

int	ft_atoi(char *s)
{
	int	i;
	int	res;
	int	minus;

	i = 0;
	res = 0;
	minus = 0;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			minus++;
		i++;
	}
	if (!s[i])
		return (0);
	while (s[i])
	{
		res += s[i] - '0';
		if (s[i + 1] != 0)
			res *= 10;
		i++;
	}
	if (minus)
		return (-res);
	return (res);
}

unsigned long	get_time(struct timeval start)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	return (((end.tv_sec - start.tv_sec) * 1000) + ((end.tv_usec - start.tv_usec) / 1000));
}
