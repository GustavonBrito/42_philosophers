/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo <gustavo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 22:56:00 by gustavo           #+#    #+#             */
/*   Updated: 2025/08/28 01:21:46 by gustavo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*must_eat_loop(t_philo *philo, t_rules *rules, int i, int finished_eat)
{
	while (++finished_eat >= rules->philo_num)
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
		if (philo[i].meals >= philo->rules->must_eat
			&& philo->rules->must_eat != 0 && philo[i].finished_eating == 0)
			return (pthread_mutex_unlock(&rules->dead_philo),
				philo[i].finished_eating = 1, NULL);
		else
			pthread_mutex_unlock(&rules->dead_philo);
		usleep(1000);
		i++;
	}
	return (NULL);
}

int	check_death(t_philo *philo, t_rules *rules, int i)
{
	if ((get_timestamp() - philo->rules->start_time) > rules->time_to_die
		&& philo->rules->philo_num == 1)
	{
		philo->rules->scan_end = 1;
		pthread_mutex_unlock(&rules->dead_philo);
		die(philo[0]);
		return (1);
	}
	if ((get_timestamp() - philo[i].last_meal) > rules->time_to_die + 3
		&& philo[i].last_meal != 0 && philo->rules->must_eat == 0)
	{
		philo->rules->scan_end = 1;
		pthread_mutex_unlock(&rules->dead_philo);
		die(philo[i]);
		return (1);
	}
	return (0);
}

void	*dead_scan_loop(t_philo *philo, t_rules *rules, int i)
{
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
		if (check_death(philo, rules, i))
			return (NULL);
		pthread_mutex_unlock(&rules->dead_philo);
		usleep(1000);
		i++;
	}
	return (NULL);
}

void	check_philo_num(t_philo *philo)
{
	if (philo->rules->philo_num == 1)
	{
		while (1)
		{
			if (get_timestamp()
				- philo->rules->start_time > philo->rules->time_to_die)
			{
				pthread_mutex_lock(&philo->rules->dead_philo);
				philo->rules->someone_died = 1;
				pthread_mutex_unlock(&philo->rules->dead_philo);
				return ;
			}
		}
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->rules->m_write);
		take_fork(philo);
		pthread_mutex_unlock(&philo->rules->m_write);
	}
}
