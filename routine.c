#include "philo.h"

static void	eat_rout(t_philo *philo)
{
	pthread_mutex_lock(philo->forks[LEFT]);
	pthread_mutex_lock(philo->forks[RIGHT]);
	if (timestamp(philo->table->start_time, MILLISECOND) - philo->last_meal > philo->table->ms_death)
	{
		printf("time : %d\n", timestamp(philo->table->start_time, MILLISECOND) - philo->last_meal);
		write_status(philo, DIE);
		philo->table->death = true;
	}
	philo->last_meal = timestamp(philo->table->start_time, MILLISECOND);
	write_status(philo, FORK_L);
	write_status(philo, FORK_R);
	pthread_mutex_unlock(philo->forks[LEFT]);
	pthread_mutex_unlock(philo->forks[RIGHT]);
}

static void	sleep_rout(t_philo *philo)
{
	write_status(philo, SLEEP);
	ft_sleep(philo->table->start_time, timestamp(philo->table->start_time, MICROSECOND), philo->table->ms_sleep * 1000);
}

static void	think_rout(t_philo *philo)
{
	write_status(philo, THINK);
}

void	*lunch(void *p)
{
	t_philo *philo;

	philo = (t_philo *)p;
	while (!philo->table->ready);
	philo->last_meal = timestamp(philo->table->start_time, MILLISECOND);
	if (philo->id % 2 == 0)
		ft_sleep(philo->table->start_time, timestamp(philo->table->start_time, MICROSECOND), philo->table->ms_sleep * 1000);
	while (!philo->table->death)
	{
		eat_rout(philo);
		sleep_rout(philo);
		think_rout(philo);
	}
	return (p);
}
