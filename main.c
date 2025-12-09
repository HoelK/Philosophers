/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:03:42 by hkeromne          #+#    #+#             */
/*   Updated: 2025/12/09 04:51:18 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init(t_table *table)
{
	ssize_t	i;

	i = -1;
	while (++i < table->n_philo)
		pthread_create(&table->philos[i].thread, NULL, &lunch, &table->philos[i]);
	table->start_runtime = timestamp(table->start_time, MILLISECOND);
	gettimeofday(&table->start_time, NULL);
	table->ready = true;
	i = -1;
	while (++i < table->n_philo)
		pthread_join(table->philos[i].thread, NULL);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6 || !check_args(av) || !init_table(&table, av))
		return (EXIT_FAILURE);
	init(&table);
	ft_clean(&table);
	return (EXIT_SUCCESS);

}
