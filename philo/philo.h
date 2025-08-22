/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:20:03 by gserafio          #+#    #+#             */
/*   Updated: 2025/08/22 17:41:23 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

struct				s_timeval
{
	time_t			tv_sec;
	suseconds_t		tv_usec;
};

typedef struct s_rules
{
	int				philo_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat;
	int				someone_died;
	long			start_time;
	int				scan_end;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_philo;
	pthread_mutex_t	m_write;
}					t_rules;

typedef struct s_philo
{
	int				id;
	int				meals;
	long			last_meal;
	int				finished_eating;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_rules			*rules;
}					t_philo;

int					init_validations(int argc, char **argv);
int					ft_atol(const char *nptr);
int					valid_just_numbers(char *argv);
t_rules				*init_rules(int argc, char **argv, t_rules *rules);
int					init_forks_mutexes(t_rules *rules);
long				get_timestamp(void);
int					init_philo(t_philo **philo, t_rules *rules);
void				think(t_philo *philo);
void				sleep_philo(t_philo *philo);
void				eat(t_philo *philo);
void				die(t_philo philo);
void				handle_threads(t_rules	*rules, t_philo	*philo);
void				take_fork(t_philo *philo);
void				handle_forks(t_philo *philo);
void				*dead_scan(void *arg);
void				*must_eat_scan(void *arg);
void				*philo_routine(void *arg);

#endif