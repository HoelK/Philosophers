/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 04:33:14 by hkeromne          #+#    #+#             */
/*   Updated: 2025/12/09 04:37:26 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		minus;
	int		result;

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

uint32_t	timestamp(struct timeval start, uint8_t mode)
{
	struct timeval	now;
	long			usec;

	usec = 0;
	if (gettimeofday(&now, NULL) == -1)
		return (0);
	usec = (now.tv_usec - start.tv_sec);
	if (usec < 0)
	{
		now.tv_usec += 1000000;
		now.tv_sec -= 1;
	}
	if (mode == MICROSECOND)
		return (((now.tv_sec - start.tv_sec) * 1000000) + ((now.tv_usec - start.tv_usec)));
	if (mode == MILLISECOND)
		return (((now.tv_sec - start.tv_sec) * 1000) + ((now.tv_usec - start.tv_usec) / 1000));
	if (mode == SECOND)
		return (now.tv_sec - start.tv_sec);
	return (0);
}

void ft_sleep(struct timeval start, uint32_t start_timestamp, uint32_t u_time) //15 microsec delay
{
	while ((timestamp(start, MICROSECOND) - start_timestamp) < u_time);
}
