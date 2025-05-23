/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 08:34:24 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/05/22 23:21:49 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_timestamp(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void *dead_scan(void *arg)
{
	int i;
	t_philo *philo = (t_philo *)arg;
	t_rules *rules = philo[0].rules;
	i = 0;
	while (1)
	{
		// if (philo->rules->scan_end == 1)
		// 	return (NULL);
		// if (rules->someone_died)
		// 	return NULL;
		if (i >= rules->philo_num)
			i = 0;
		if ((get_timestamp() - philo->rules->start_time) >= rules->time_to_die && philo->rules->philo_num == 1)
			return (die(philo[i]), philo->rules->scan_end = 1, pthread_mutex_unlock(philo[0].left_fork), NULL);
		if ((get_timestamp() - philo[i].last_meal) >= rules->time_to_die && philo[i].last_meal != 0 && philo->rules->must_eat == 0)
			return (die(philo[i]), philo->rules->scan_end = 1, NULL);
		i++;
		usleep(1000);
	}
	return (NULL);
}

void *must_eat_scan(void *arg)
{
	int i;
	int finished_eat;
	t_philo *philo = (t_philo *)arg;
	t_rules *rules = philo[0].rules;
	
	i = 0;
	finished_eat = 0;
	while (finished_eat < rules->philo_num)
	{
		if (philo->rules->scan_end == 1)
			return (NULL);
		if (i >= rules->philo_num)
			i = 0;
		if (philo[i].meals >= philo->rules->must_eat && philo->rules->must_eat != 0 && philo[i].finished_eating == 0)
		{
			philo[i].finished_eating = 1;
			finished_eat++;
		}
		i++;
		usleep(1000);
	}
	philo->rules->scan_end = 1;
	return (NULL);
}
