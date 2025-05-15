/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:49:01 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/05/15 20:18:11 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int eat(t_philo *philo);
int sleep(t_philo *philo);
// int die(t_philo *philo);
int	think(t_philo *philo);

int think(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->m_write);
	printf("%ld %d: is thinking\n", get_timestamp() - philo->rules->start_time, philo->id);
	pthread_mutex_unlock(&philo->rules->m_write);
	return (1);
};

int eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->rules->m_write);
		printf("%ld %d has taken a fork\n", get_timestamp() - philo->rules->start_time, philo->id);
		pthread_mutex_unlock(&philo->rules->m_write);
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->rules->m_write);
		printf("%ld %d has taken a fork\n", get_timestamp() - philo->rules->start_time, philo->id);
		pthread_mutex_unlock(&philo->rules->m_write);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->rules->m_write);
		printf("%ld %d has taken a fork\n", get_timestamp() - philo->rules->start_time, philo->id);
		pthread_mutex_unlock(&philo->rules->m_write);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->rules->m_write);
		printf("%ld %d has taken a fork\n", get_timestamp() - philo->rules->start_time, philo->id);
		pthread_mutex_unlock(&philo->rules->m_write);
	}
	pthread_mutex_lock(&philo->rules->m_write);
	printf("%ld %d is eating\n", get_timestamp() - philo->rules->start_time, philo->id);
	philo->last_meal = get_timestamp();
	usleep(philo->rules->time_to_eat * 1000);
	philo->meals++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (1);
}

int sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->m_write);
	printf("%ld %d: is sleeping\n", get_timestamp() - philo->rules->start_time, philo->id);
	pthread_mutex_unlock(&philo->rules->m_write);
	usleep(philo->rules->time_to_sleep * 1000);
	return (1);
}

int die(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->m_write);
	printf("%ld %d: died\n", get_timestamp() - philo->rules->start_time, philo->id);
	pthread_mutex_unlock(&philo->rules->m_write);
	philo->rules->someone_died = 1;
	return (-1);
}