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

void	sleep_ms(int sleep_time)
{
	usleep(sleep_time * 1000);
}

int	hunger(t_philo *philo, pthread_mutex_t **forks)
{
	pthread_mutex_lock(forks[LEFT]);
	print_status(philo, "is picking left fork");
	pthread_mutex_lock(forks[RIGHT]);
	print_status(philo, "is picking right fork");
	if (!philo->ms_death)
		return (philo->stats->death = true, 0);
	return (1);
}

void	eat(t_philo *philo, int time_to_eat, pthread_mutex_t **forks)
{
	if (!hunger(philo, forks))
		return ;
	sleep_ms(time_to_eat);
	print_status(philo, "is eating");
	pthread_mutex_unlock(forks[LEFT]);
	pthread_mutex_unlock(forks[RIGHT]);
}

void	*start(void *philo)
{
	t_philo *p;

	p = (t_philo *)philo;
	if (p->id % 2 == 1)
		sleep_ms(1);
	while (!p->stats->death)
	{
		eat(p, p->ms_eat, p->forks);
		if (!p->stats->death)
		{
			print_status(p, "is sleeping");
			sleep_ms(p->ms_sleep);
		}
	}
	return (philo);
}

void	init(t_stats *stats)
{
	int	i;

	i = -1;
	stats->start_time = get_time(0);
	while (++i < stats->n_philo)
		pthread_create(&stats->philos[i].philo, NULL, start, &stats->philos[i]);
	while (!stats->death);
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
