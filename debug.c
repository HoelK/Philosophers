/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 01:52:03 by hkeromne          #+#    #+#             */
/*   Updated: 2025/12/06 18:19:13 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_status(t_philo *philo, const char *status)
{
	fprintf(stderr, "%ld %d %s\n", get_time(philo->stats->start_time), philo->id, status);
}

void	print_philo(t_philo *philo)
{
	printf("id : %d\n", philo->id);
	printf("eat count : %lu\n", philo->stats->ms_eat);
	printf("death count : %lu\n", philo->stats->ms_death);
	printf("sleep count : %lu\n", philo->stats->ms_sleep);
}

void	print_stats(t_stats *stats)
{
	int	i;

	i = 0;
	printf("number of philos : %d\n", stats->n_philo);
	printf("time to eat : %lu\n", stats->ms_eat);
	printf("time to sleep : %lu\n", stats->ms_sleep);
	printf("time to die : %lu\n", stats->ms_death);
	while (i < stats->n_philo)
		print_philo(&stats->philos[i++]);
}
