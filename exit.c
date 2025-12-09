/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 00:10:49 by hkeromne          #+#    #+#             */
/*   Updated: 2025/12/10 00:10:49 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexs(pthread_mutex_t *mutexs, uint8_t n_philos)
{
	size_t	i;

	i = 0;
	while (i < n_philos)
		pthread_mutex_destroy(&mutexs[i++]);
	free(mutexs);
}

void	ft_clean(t_table *table)
{
	pthread_mutex_destroy(&table->meal_m);
	pthread_mutex_destroy(&table->write_m);
	pthread_mutex_destroy(&table->death_m);
	destroy_mutexs(table->forks, table->n_philo);
	free(table->philos);
}
