/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 04:33:35 by hkeromne          #+#    #+#             */
/*   Updated: 2025/11/27 22:25:17 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	sleep(int sleep_time)
{
	usleep(sleep_time * 1000);
}

int	hunger(t_philo *philo, int time_to_eat, pthread_mutex_t *forks)
{
	while (pthread_mutex_lock(forks[LEFT]) == EDEADLK || pthread_mutex_lock(forks[RIGHT]) == EDEADLK)
	{
		usleep(1000);
		philo->ms_death--;
		if (!philo->ms_death)
		{
			philo->stats->death = 1;
			return (0);
		}
	}
	philo->ms_death = philo->stats->t_to_die;
	return (1);
}

void	eat(t_philo *philo, int time_to_eat, pthread_mutex_t *forks)
{
	if (!hunger(philo, time_to_eat, forks))
		return ;
	print_status("is eating");
	usleep(time_to_eat * 1000);
	pthread_mutex_unlock(forks[LEFT]);
	pthread_mutex_unlock(forks[RIGHT]);
}

bool	end(t_stats *stats)
{
	return (stats->death);
}

void	*start(void *philo)
{
	t_philo *p;

	p = (t_philo *)philo;
	if (p->id % 2 == 1)
		wait(1000);
	while (!end(p->stats))
	{
		eat(p, p->ms_eat, p->forks);
		sleep(p->ms_sleep);
	}
	return (philo);
}

void	init(t_stats *stats)
{
	int	i;

	i = -1;
	while (++i < stats->n_philo)
		pthread_create(&stats->philos[i].philo, NULL, start, &stats->philos[i]);
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
