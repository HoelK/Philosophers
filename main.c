/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:03:42 by hkeromne          #+#    #+#             */
/*   Updated: 2025/12/10 00:24:44 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init(t_table *table)
{
	ssize_t	i;

	i = -1;
	if (table->n_philo == 1)
		pthread_create(&table->philos[0].thread,
			NULL, &solo_lunch, &table->philos[0]);
	else
	{
		while (++i < table->n_philo)
			pthread_create(&table->philos[i].thread,
				NULL, &lunch, &table->philos[i]);
	}
	monitor(table);
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
