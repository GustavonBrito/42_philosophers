/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:49:01 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/05/19 00:35:48 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int eat(t_philo *philo);
int sleep_philo(t_philo *philo);
int die(t_philo *philo);
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

int sleep_philo(t_philo *philo)
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

void *dead_scan(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	pthread_mutex_init(philo->rules->dead_philo, NULL);
	
	while (1)
	{
		if (philo->last_meal - get_timestamp() > philo->rules->time_to_die)
		{
			pthread_mutex_lock(philo->rules->dead_philo);
			philo->rules->someone_died = 1;
			pthread_mutex_unlock(philo->rules->dead_philo);
			return (&philo->rules->someone_died); //Verificar melhor retorno depois e tambem todos os frees que é preciso fazer.
		}
	}
	return (NULL);
}
