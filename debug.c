/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 01:52:03 by hkeromne          #+#    #+#             */
/*   Updated: 2025/11/27 22:30:57 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_status(t_philo *philo, const char *status)
{
	printf("%d %d %s", get_time(), philo->id, status);
}

void	print_philo(t_philo *philo)
{
	printf("id : %d\n", philo->id);
	printf("eat count : %d\n", philo->ms_eat);
	printf("death count : %d\n", philo->ms_death);
	printf("sleep count : %d\n", philo->ms_sleep);
}

void	print_stats(t_stats *stats)
{
	int	i;

	i = 0;
	printf("number of philos : %d\n", stats->n_philo);
	printf("time to eat : %d\n", stats->t_to_eat);
	printf("time to sleep : %d\n", stats->t_to_sleep);
	printf("time to die : %d\n", stats->t_to_die);
	while (i < stats->n_philo)
		print_philo(&stats->philos[i++]);
}
