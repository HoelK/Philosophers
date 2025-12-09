/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 00:11:18 by hkeromne          #+#    #+#             */
/*   Updated: 2025/12/10 00:32:41 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->meal_m);
	if (timestamp() - philo->last_meal > philo->table->ms_death)
		return (write_status(philo, DIE),
			pthread_mutex_unlock(&philo->table->meal_m), true);
	return (pthread_mutex_unlock(&philo->table->meal_m), false);
}

bool	ate_well(t_philo *philos, uint8_t n_philos)
{
	ssize_t	i;

	i = -1;
	pthread_mutex_lock(&philos[0].table->meal_m);
	if (philos->table->max_meal == -1)
		return ((pthread_mutex_unlock(&philos[0].table->meal_m), false));
	while (++i < n_philos && philos[i].full)
		;
	if (i == n_philos)
		return ((pthread_mutex_unlock(&philos[0].table->meal_m), true));
	pthread_mutex_unlock(&philos[0].table->meal_m);
	return (false);
}

void	monitor(t_table *table)
{
	ssize_t	i;

	i = -1;
	while (!ate_well(table->philos, table->n_philo))
	{
		while (++i < table->n_philo)
		{
			if (is_dead(&table->philos[i]))
			{
				access_death(&table->death_m, &table->death, SET);
				return ;
			}
		}
		i = -1;
		usleep(80);
	}
	access_death(&table->death_m, &table->death, SET);
}
