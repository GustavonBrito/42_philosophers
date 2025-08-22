/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:20:11 by gserafio          #+#    #+#             */
/*   Updated: 2025/08/22 18:24:42 by ubuntu           ###   ########.fr       */
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
		pthread_mutex_lock(&rules->dead_philo);
		if (philo->rules->scan_end == 1)
			return (pthread_mutex_unlock(&rules->dead_philo), NULL);
		pthread_mutex_unlock(&rules->dead_philo);
		pthread_mutex_lock(&rules->dead_philo);
		if (i >= rules->philo_num)
		{
			pthread_mutex_unlock(&rules->dead_philo);
			i = 0;
		}
		else
			pthread_mutex_unlock(&rules->dead_philo);
		pthread_mutex_lock(&rules->dead_philo);
		if ((get_timestamp() - philo->rules->start_time) >= rules->time_to_die
			&& philo->rules->philo_num == 1)
		{
			philo->rules->scan_end = 1;
			die(philo[i]);
			pthread_mutex_unlock(&rules->dead_philo);
			pthread_mutex_unlock(philo[0].left_fork);
			return (NULL);
		}
		pthread_mutex_unlock(&rules->dead_philo);
		pthread_mutex_lock(&rules->dead_philo);
		if ((get_timestamp() - philo[i].last_meal) >= rules->time_to_die
			&& philo[i].last_meal != 0 && philo->rules->must_eat == 0)
		{
			philo->rules->scan_end = 1;
			pthread_mutex_unlock(&rules->dead_philo);
			return (die(philo[i]), NULL);
		}
		pthread_mutex_unlock(&rules->dead_philo);
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
		pthread_mutex_lock(&rules->dead_philo);
		if (philo->rules->scan_end == 1)
		{
			pthread_mutex_unlock(&rules->dead_philo);
			return (NULL);
		}
		pthread_mutex_unlock(&rules->dead_philo);
		pthread_mutex_lock(&rules->dead_philo);
		if (i >= rules->philo_num)
		{
			pthread_mutex_unlock(&rules->dead_philo);
			i = 0;
		}
		else
			pthread_mutex_unlock(&rules->dead_philo);
		pthread_mutex_lock(&rules->dead_philo);
		if (philo[i].meals >= philo->rules->must_eat
			&& philo->rules->must_eat != 0 && philo[i].finished_eating == 0)
		{
			pthread_mutex_unlock(&rules->dead_philo);
			philo[i].finished_eating = 1;
			finished_eat++;
		}
		else
			pthread_mutex_unlock(&rules->dead_philo);
		i++;
		usleep(1000);
	}
	pthread_mutex_lock(&rules->dead_philo);
	philo->rules->scan_end = 1;
	pthread_mutex_unlock(&rules->dead_philo);
	return (NULL);
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
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->rules->m_write);
		take_fork(philo);
		pthread_mutex_unlock(&philo->rules->m_write);
	}
}
