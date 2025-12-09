/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 00:11:00 by hkeromne          #+#    #+#             */
/*   Updated: 2025/12/10 00:14:35 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_philo *philo, uint8_t status)
{
	if (access_death(&philo->table->death_m, &philo->table->death, GET))
		return ;
	pthread_mutex_lock(&philo->table->write_m);
	printf("%u %d ", timestamp() - philo->table->start_runtime, philo->id);
	if (status == DIE)
		printf("died\n");
	else if (status == EAT)
		printf("is eating\n");
	else if (status == SLEEP)
		printf("is sleeping\n");
	else if (status == THINK)
		printf("is thinking\n");
	else if (status == FORK_L)
		printf("has taken a left fork\n");
	else if (status == FORK_R)
		printf("has taken a right fork\n");
	pthread_mutex_unlock(&philo->table->write_m);
}
