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

void	sleep(t_philo *philo)
{
}

void	eat(t_philo *philo, pthread_mutex_t *forks)
{

}

void	start(t_stats *stats)
{
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
	start(&stats);
	return (0);
}
