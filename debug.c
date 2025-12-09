#include "philo.h"

void	write_status(t_philo *philo, uint8_t status)
{
	pthread_mutex_lock(&philo->table->write_m);
	printf("%u %d ", timestamp(philo->table->start_time, MILLISECOND), philo->id);
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

void	write_philo(t_philo *philo)
{
	printf("=====PHILO No[%d]=====\n", philo->id);
	printf("meal count : %d\n", philo->meal_count);
}

void	write_table(t_table *table)
{
	size_t	i;

	i = 0;
	printf("number of philos : %d\ntime to die : %d\ntime to eat : %d\ntime to sleep: %d\nmax meal : %d\n", table->n_philo, table->ms_death, table->ms_eat, table->ms_sleep, table->max_meal);
	while (i < table->n_philo)
		write_philo(&table->philos[i++]);
}
