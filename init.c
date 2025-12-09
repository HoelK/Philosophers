/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 00:10:53 by hkeromne          #+#    #+#             */
/*   Updated: 2025/12/10 00:33:26 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo_data(t_table *table, t_philo *philos, uint8_t id)
{
	philos->id = id;
	philos->full = false;
	philos->meal_count = 0;
	philos->last_meal = table->start_runtime;
	philos->table = table;
}

t_philo	*init_philos(t_table *table, uint8_t n_philos, pthread_mutex_t *forks)
{
	uint8_t	i;
	t_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * n_philos);
	if (!philos)
		return (NULL);
	table->start_runtime = timestamp();
	while (i < n_philos)
	{
		init_philo_data(table, &philos[i], i);
		philos[i].forks[LEFT] = &forks[i];
		if (i == (n_philos - 1))
		{
			philos[i].forks[LEFT] = &forks[0];
			philos[i].forks[RIGHT] = &forks[i];
		}
		else
		{
			philos[i].forks[LEFT] = &forks[i];
			philos[i].forks[RIGHT] = &forks[i + 1];
		}
		i++;
	}
	return (philos);
}

static pthread_mutex_t	*init_mutexs(uint8_t n_philos)
{
	uint8_t			i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * n_philos);
	if (!forks)
		return (NULL);
	while (i < n_philos)
		pthread_mutex_init(&forks[i++], NULL);
	return (forks);
}

bool	init_table(t_table *table, char **av)
{
	size_t	i;

	i = 0;
	table->death = false;
	table->n_philo = ft_atoi(av[++i]);
	table->ms_death = ft_atoi(av[++i]);
	table->ms_eat = ft_atoi(av[++i]);
	table->ms_sleep = ft_atoi(av[++i]);
	table->max_meal = -1;
	pthread_mutex_init(&table->meal_m, NULL);
	pthread_mutex_init(&table->write_m, NULL);
	pthread_mutex_init(&table->death_m, NULL);
	if (av[++i])
		table->max_meal = ft_atoi(av[i]);
	table->forks = init_mutexs(table->n_philo);
	if (!table->forks)
		return (false);
	table->philos = init_philos(table, table->n_philo, table->forks);
	if (!table->philos)
		return (destroy_mutexs(table->forks, table->n_philo), false);
	return (true);
}
