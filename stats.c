/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 01:51:56 by hkeromne          #+#    #+#             */
/*   Updated: 2025/12/07 03:33:37 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	free_stats(t_stats *stats)
{
	int	i;

	if (stats->philos)
	{
		i = -1;
		while (++i < stats->n_philo)
			pthread_detach(stats->philos[i].philo);
		free(stats->philos);
	}
	if (stats->forks)
	{
		i = -1;
		while (++i < stats->n_philo)
			pthread_mutex_destroy(&stats->forks[i]);
		free(stats->forks);
	}
}

int	get_stats(t_stats *stats, char **av)
{
	int	i;

	i = -1;
	stats->death = false;
	stats->n_philo = ft_atoi(av[1]);
	stats->ms_death = ft_atoi(av[2]);
	stats->ms_eat = ft_atoi(av[3]);
	stats->ms_sleep = ft_atoi(av[4]);
	stats->max_meal = -1;
	if (av[5])
		stats->max_meal = ft_atoi(av[5]);
	stats->philos = malloc(sizeof(t_philo) * stats->n_philo);
	stats->forks = malloc(sizeof(pthread_mutex_t) * stats->n_philo);
	if (stats->philos == NULL || stats->forks == NULL)
		return (free_stats(stats), 0);
	pthread_mutex_init(&stats->hunger_m, NULL);
	pthread_mutex_init(&stats->death_m, NULL);
	while (++i < stats->n_philo)
	{
		stats->philos[i].id = i;
		stats->philos[i].n_meal = 0;
		stats->philos[i].stats = stats;
		pthread_mutex_init(&stats->forks[i], NULL);
		stats->philos[i].forks[LEFT] = &stats->forks[i];
		if (i == (stats->n_philo - 1))
		{
			stats->philos[i].forks[LEFT] = &stats->forks[0];
			stats->philos[i].forks[RIGHT] = &stats->forks[i];
		}
		else
			stats->philos[i].forks[RIGHT] = &stats->forks[i + 1];
	}
	return (1);
}
