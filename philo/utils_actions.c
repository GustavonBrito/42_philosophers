/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 08:34:24 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/08/12 10:04:42 by gserafio         ###   ########.fr       */
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
	while (1)
	{
		if (philo->rules->scan_end == 1)
			return (NULL);
		if (i >= rules->philo_num)
			i = 0;
		if ((get_timestamp() - philo->rules->start_time) >= rules->time_to_die
			&& philo->rules->philo_num == 1)
			return (die(philo[i]), philo->rules->scan_end = 1,
				pthread_mutex_unlock(philo[0].left_fork), NULL);
		if ((get_timestamp() - philo[i].last_meal) >= rules->time_to_die
			&& philo[i].last_meal != 0 && philo->rules->must_eat == 0)
			return (die(philo[i]), philo->rules->scan_end = 1, NULL);
		i++;
		usleep(1000);
	}
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
	finished_eat = 0;
	while (finished_eat < rules->philo_num)
	{
		if (philo->rules->scan_end == 1)
			return (NULL);
		if (i >= rules->philo_num)
			i = 0;
		if (philo[i].meals >= philo->rules->must_eat
			&& philo->rules->must_eat != 0 && philo[i].finished_eating == 0)
		{
			philo[i].finished_eating = 1;
			finished_eat++;
		}
		i++;
		usleep(1000);
	}
	return (philo->rules->scan_end = 1, NULL);
}

void	is_someone_dead(t_philo *philo)
{
	if (philo->rules->someone_died != 1)
		printf("%ld %d has taken a fork\n", get_timestamp()
			- philo->rules->start_time, philo->id);
}

void	handle_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		usleep(1000);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->rules->m_write);
		is_someone_dead(philo);
		pthread_mutex_unlock(&philo->rules->m_write);
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->rules->m_write);
		is_someone_dead(philo);
		pthread_mutex_unlock(&philo->rules->m_write);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->rules->m_write);
		is_someone_dead(philo);
		if (philo->rules->philo_num == 1)
			usleep(philo->rules->time_to_die * 1000);
		pthread_mutex_unlock(&philo->rules->m_write);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->rules->m_write);
		is_someone_dead(philo);
		pthread_mutex_unlock(&philo->rules->m_write);
	}
}
