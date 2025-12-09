/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 04:33:14 by hkeromne          #+#    #+#             */
/*   Updated: 2025/12/10 00:24:26 by hkeromne         ###   ########.fr       */
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

uint32_t	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

void	ft_sleep(uint32_t u_time)
{
	uint32_t	start;

	start = timestamp();
	while (timestamp() - start < u_time)
		usleep(50);
}

bool	access_death(pthread_mutex_t *lock, bool *death, uint8_t mode)
{
	bool	ret;

	pthread_mutex_lock(lock);
	if (mode == SET)
		*death = true;
	ret = false;
	if (*death == true)
		ret = true;
	pthread_mutex_unlock(lock);
	return (ret);
}
