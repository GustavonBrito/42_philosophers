/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo <gustavo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:20:11 by gserafio          #+#    #+#             */
/*   Updated: 2025/08/28 01:21:01 by gustavo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	*dead_scan(void *arg)
{
	int		i;
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)arg;
	rules = philo[0].rules;
	i = 0;
	dead_scan_loop(philo, rules, i);
	return (NULL);
}

void	*must_eat_scan(void *arg)
{
	int		i;
	int		finished_eat;
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)arg;
	rules = philo[0].rules;
	i = 0;
	finished_eat = -1;
	must_eat_loop(philo, rules, i, finished_eat);
	return (pthread_mutex_lock(&rules->dead_philo), philo->rules->scan_end = 1,
		pthread_mutex_unlock(&rules->dead_philo), NULL);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->dead_philo);
	if (philo->rules->someone_died != 1)
	{
		pthread_mutex_unlock(&philo->rules->dead_philo);
		printf("%ld %d has taken a fork\n", get_timestamp()
			- philo->rules->start_time, philo->id);
	}
	else
		pthread_mutex_unlock(&philo->rules->dead_philo);
}

void	handle_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		usleep(500);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->rules->m_write);
		take_fork(philo);
		pthread_mutex_unlock(&philo->rules->m_write);
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->rules->m_write);
		take_fork(philo);
		pthread_mutex_unlock(&philo->rules->m_write);
	}
	else
	{
		usleep(500);
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->rules->m_write);
		take_fork(philo);
		pthread_mutex_unlock(&philo->rules->m_write);
		check_philo_num(philo);
	}
}
