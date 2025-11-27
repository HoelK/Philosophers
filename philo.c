/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 04:33:35 by hkeromne          #+#    #+#             */
/*   Updated: 2025/11/26 02:26:33 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*void	sleep(t_philo *philo)
{
}

void	eat(t_philo *philo, pthread_mutex_t *forks)
{

}*/

void	*start(void *philo)
{
	t_philo *p;

	p = (t_philo *)philo;
	print_philo(p);
	if (philo->id % 2 == 0)
	else
	return (philo);
}

void	init(t_stats *stats)
{
	int	i;

	i = -1;
	while (++i < stats->n_philo)
	{
		pthread_create(&stats->philos[i].philo, NULL, start, &stats->philos[i]);
		usleep (1000);
	}
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
