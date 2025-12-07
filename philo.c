/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 04:33:35 by hkeromne          #+#    #+#             */
/*   Updated: 2025/12/07 04:04:49 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

bool	access_death(bool *death, pthread_mutex_t *mutex, int mode)
{
	bool ret;

	pthread_mutex_lock(mutex);
	if (mode == ADD)
		*death = true;
	ret = false;
	if (*death == true)
		ret = true;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	sleep_ms(int sleep_time)
{
	usleep(sleep_time * 1000);
}

int	hunger(t_philo *philo, pthread_mutex_t **forks)
{
	unsigned long start;

	start = get_time(philo->stats->start_time);
	pthread_mutex_lock(&philo->stats->hunger_m);
	pthread_mutex_lock(forks[LEFT]);
	print_status(philo, "is picking left fork");
	pthread_mutex_lock(forks[RIGHT]);
	print_status(philo, "is picking right fork");
	if ((get_time(philo->stats->start_time) - start > philo->stats->ms_death)
		|| (philo->stats->max_meal != -1 && philo->n_meal == philo->stats->max_meal))
		return (access_death(&philo->stats->death, &philo->stats->death_m, ADD), print_status(philo, "died"), 0);
	return (1);
}

void	eat(t_philo *philo, int time_to_eat, pthread_mutex_t **forks)
{
	if (!hunger(philo, forks))
	{
		pthread_mutex_unlock(forks[LEFT]);
		pthread_mutex_unlock(forks[RIGHT]);
		pthread_mutex_unlock(&philo->stats->hunger_m);
		return ;
	}
	sleep_ms(time_to_eat);
	print_status(philo, "is eating");
	philo->n_meal++;
	pthread_mutex_unlock(forks[LEFT]);
	pthread_mutex_unlock(forks[RIGHT]);
	pthread_mutex_unlock(&philo->stats->hunger_m);
}

void	*start(void *philo)
{
	t_philo *p;

	p = (t_philo *)philo;
	if (p->id % 2 == 1)
		usleep(100);
	while (!access_death(&p->stats->death, &p->stats->death_m, 0))
	{
		eat(p, p->stats->ms_eat, p->forks);
		if (!access_death(&p->stats->death, &p->stats->death_m, 0))
		{
			print_status(p, "is sleeping");
			sleep_ms(p->stats->ms_sleep);
		}
	}
	return (philo);
}

void	*solo(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	pthread_mutex_lock(philo->forks[LEFT]);
	print_status(philo, "is picking left fork");
	sleep_ms(philo->stats->ms_death);
	print_status(philo, "died");
	pthread_mutex_unlock(philo->forks[LEFT]);
	philo->stats->death = true;
	return (philo);
}

void	init(t_stats *stats)
{
	int	i;

	i = -1;
	gettimeofday(&stats->start_time, NULL);
	if (stats->n_philo == 1)
		pthread_create(&stats->philos[0].philo, NULL, solo, &stats->philos[0]);
	else
	{
		while (++i < stats->n_philo)
			pthread_create(&stats->philos[i].philo, NULL, start, &stats->philos[i]);
	}
	i = -1;
	while (pthread_join(stats->philos[++i].philo, NULL));
	while (!access_death(&stats->death, &stats->death_m, 0));
}

bool	check_args(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (false);
	while (i < ac)
	{
		if (!ft_isnumber(av[i]))
			return (false);
		i++;
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_stats	stats;

	if (!check_args(ac, av))
		return (1);
	get_stats(&stats, av);
	init(&stats);
	free_stats(&stats);
	return (0);
}
