/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 01:51:56 by hkeromne          #+#    #+#             */
/*   Updated: 2025/11/27 22:34:31 by hkeromne         ###   ########.fr       */
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
	stats->t_to_die = ft_atoi(av[2]);
	stats->t_to_eat = ft_atoi(av[3]);
	stats->t_to_sleep = ft_atoi(av[4]);
	stats->philos = malloc(sizeof(t_philo) * stats->n_philo);
	stats->forks = malloc(sizeof(pthread_mutex_t) * stats->n_philo);
	if (stats->philos == NULL || stats->forks == NULL)
		return (free_stats(stats), 0);
	while (++i < stats->n_philo)
	{
		stats->philos[i].id = i;
		stats->philos[i].stats = stats;
		stats->philos[i].ms_eat = stats->t_to_eat;
		stats->philos[i].ms_sleep = stats->t_to_sleep;
		stats->philos[i].ms_death = stats->t_to_die;
		if (i == 0)
			stats->philos[i].forks[LEFT] = stats->forks[stats->n_philo - 1];
		else
			stats->philos[i].forks[LEFT] = stats->forks[i - 1];
		if (i == (stats->n_philo - 1))
			stats->philos[i].forks[RIGHT] = stats->forks[0];
		else
			stats->philos[i].forks[RIGHT] = stats->forks[i];
		pthread_mutex_init(&stats->forks[i], NULL);
	}
	return (1);
}
