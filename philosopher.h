/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 04:34:36 by hkeromne          #+#    #+#             */
/*   Updated: 2025/11/26 01:59:16 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <pthread.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# define LEFT 0
# define RIGHT 1

typedef struct s_philo
{
	int				id;
	int				ms_death;
	int				ms_eat;
	int				ms_sleep;
	pthread_t		philo;
	pthread_mutex_t	forks[2];
}	t_philo;

typedef struct s_stats
{
	int				n_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	t_philo			*philos;
	pthread_mutex_t	*forks;
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

//utils
int		ft_isdigit(char c);
bool	ft_isnumber(char *s);
int		ft_atoi(char *s);

#endif
