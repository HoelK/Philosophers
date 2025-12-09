/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 21:22:42 by hkeromne          #+#    #+#             */
/*   Updated: 2025/12/08 21:32:50 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	return (0);
}

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static long	ft_atol(const char *nptr)
{
	size_t	i;
	int		minus;
	long		result;

	i = 0;
	minus = 0;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] > 8 && nptr[i] < 14))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			minus = 1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		result += nptr[i] - '0';
		if (ft_isdigit(nptr[i + 1]))
			result *= 10;
		i++;
	}
	if (minus)
		return (-result);
	return (result);
}

static bool	ft_isnum(char *s)
{
	int	i;

	if (!s)
		return (false);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		return (false);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	check_args(char **av)
{
	size_t	i;

	i = 0;
	while (av[++i])
	{
		if ((!ft_isnum(av[i])) || ft_strlen(av[i]) > 10 || (ft_atol(av[i]) < 0 || ft_atol(av[i]) > INT_MAX))
			return (false);
	}
	return (true);
}
