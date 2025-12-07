/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 04:34:36 by hkeromne          #+#    #+#             */
/*   Updated: 2025/12/06 23:57:43 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <sys/time.h>
# include <limits.h>
# ifndef LEFT
#  define LEFT 0
# endif
# ifndef RIGHT
#  define RIGHT 1
# endif
# ifndef ADD
#  define ADD 1
# endif

typedef struct s_stats t_stats;

typedef struct s_philo
{
	int				id;
	int				n_meal;			
	pthread_t		philo;
	pthread_mutex_t	*forks[2];
	t_stats			*stats;
}	t_philo;

typedef struct s_stats
{
	int				n_philo;
	unsigned long	ms_death;
	unsigned long	ms_eat;
	unsigned long	ms_sleep;
	int				max_meal;
	bool			death;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	struct timeval	start_time;
	pthread_mutex_t	hunger_m;
	pthread_mutex_t	death_m;
}	t_stats;

//philosopher
bool	check_args(int ac, char **av);
void	init(t_stats *stats);
void	*start(void *philo);

//stats
void	free_stats(t_stats *stats);
int		get_stats(t_stats *stats, char **av);

//debug
void	print_philo(t_philo *philo);
void	print_stats(t_stats *stats);
void	print_status(t_philo *philo, const char *status);

//utils
int		ft_atoi(char *s);
int		ft_isdigit(char c);
unsigned long	get_time(struct timeval start);
bool	ft_isnumber(char *s);

#endif
