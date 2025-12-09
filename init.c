#include "philo.h"


static t_philo	*init_philos(t_table *table, uint8_t n_philos, pthread_mutex_t *forks)
{
	uint8_t	i;
	t_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * n_philos);
	if (!philos)
		return (NULL);
	while (i < n_philos)
	{
		philos[i].id = i;
		philos[i].full = false;
		philos[i].meal_count = 0;
		philos[i].table = table;
		if (i == (n_philos - 1))
		{
			philos[i].forks[LEFT] = &forks[0];
			philos[i].forks[RIGHT] = &forks[i];
		}
		else
		{
			philos[i].forks[LEFT] = &forks[i];
			philos[i].forks[RIGHT] = &forks[i + 1];
		}
		i++;
	}
	return (philos);
}

static pthread_mutex_t	*init_mutexs(uint8_t n_philos)
{
	uint8_t			i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * n_philos);
	if (!forks)
		return (NULL);
	while (i < n_philos)
		pthread_mutex_init(&forks[i++], NULL);
	return (forks);
}

bool	init_table(t_table *table, char **av)
{
	size_t	i;

	i = 0;
	table->ready = false;
	table->n_philo = ft_atoi(av[++i]);
	table->ms_death = ft_atoi(av[++i]);
	table->ms_eat = ft_atoi(av[++i]);
	table->ms_sleep = ft_atoi(av[++i]);
	table->max_meal = 0;
	pthread_mutex_init(&table->write_m, NULL);
	if (av[++i])
		table->max_meal = ft_atoi(av[i]);
	table->forks = init_mutexs(table->n_philo);
	if (!table->forks)
		return (false);
	table->philos = init_philos(table, table->n_philo, table->forks);
	if (!table->philos)
		return (destroy_mutexs(table->forks, table->n_philo), false);
	return (true);
}
