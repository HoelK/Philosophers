#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <stdint.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# define LEFT 0
# define RIGHT 1
# define GET 0
# define SET 1

enum e_timemode
{
	MICROSECOND,
	MILLISECOND,
	SECOND
};

enum e_status
{
	DIE,
	EAT,
	SLEEP,
	THINK,
	FORK_L,
	FORK_R
};

typedef struct s_table t_table;

typedef struct s_philo
{
	uint8_t			id;
	uint32_t		meal_count;
	uint32_t		last_meal;
	bool			full;
	pthread_mutex_t *forks[2];
	t_table			*table;
	pthread_t		thread;
}	t_philo;

typedef struct s_table
{
	bool			ready;
	bool			death;
	uint8_t			n_philo;
	uint32_t		ms_eat;
	uint32_t		ms_sleep;
	uint32_t		ms_death;
	uint32_t		max_meal;
	struct timeval	start_time;
	uint32_t		start_runtime;
	t_philo			*philos;
	pthread_mutex_t write_m;
	pthread_mutex_t *forks;
}	t_table;

bool		check_args(char **av);
void		write_status(t_philo *philo, uint8_t status);
bool		init_table(t_table *table, char **av);
int			ft_atoi(const char *nptr);
void		destroy_mutexs(pthread_mutex_t *mutexs, uint8_t n_philos);
void		write_table(t_table *table);
void		write_philo(t_philo *philo);
void		write_status(t_philo *philo, uint8_t status);
void		ft_clean(t_table *table);
uint32_t	timestamp(struct timeval start, uint8_t mode);
void ft_sleep(struct timeval start, uint32_t start_timestamp, uint32_t u_time); //15 microsec delay
void	*lunch(void *p);


#endif
