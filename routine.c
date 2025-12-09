/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 00:11:06 by hkeromne          #+#    #+#             */
/*   Updated: 2025/12/10 00:35:51 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*solo_lunch(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	pthread_mutex_lock(philo->forks[LEFT]);
	write_status(philo, FORK_L);
	usleep(philo->table->ms_death * 1000);
	pthread_mutex_unlock(philo->forks[LEFT]);
	return (philo);
}

static void	eat_rout(t_philo *philo)
{
	pthread_mutex_lock(philo->forks[LEFT]);
	if (access_death(&philo->table->death_m, &philo->table->death, GET))
		return ((void)pthread_mutex_unlock(philo->forks[LEFT]));
	write_status(philo, FORK_L);
	pthread_mutex_lock(philo->forks[RIGHT]);
	if (access_death(&philo->table->death_m, &philo->table->death, GET))
		return (pthread_mutex_unlock(philo->forks[LEFT]),
			(void)pthread_mutex_unlock(philo->forks[RIGHT]));
	write_status(philo, FORK_R);
	pthread_mutex_lock(&philo->table->meal_m);
	philo->last_meal = timestamp();
	philo->meal_count++;
	if (philo->meal_count == philo->table->max_meal)
		philo->full = true;
	pthread_mutex_unlock(&philo->table->meal_m);
	write_status(philo, EAT);
	ft_sleep(philo->table->ms_eat);
	pthread_mutex_unlock(philo->forks[LEFT]);
	pthread_mutex_unlock(philo->forks[RIGHT]);
}

static void	sleep_rout(t_philo *philo)
{
	if (access_death(&philo->table->death_m, &philo->table->death, GET))
		return ;
	write_status(philo, SLEEP);
	ft_sleep(philo->table->ms_sleep);
}

static void	think_rout(t_philo *philo)
{
	if (access_death(&philo->table->death_m, &philo->table->death, GET))
		return ;
	write_status(philo, THINK);
}

void	*lunch(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->id % 2 == 0)
		usleep(50);
	while (!access_death(&philo->table->death_m, &philo->table->death, GET))
	{
		eat_rout(philo);
		sleep_rout(philo);
		think_rout(philo);
	}
	return (p);
}
