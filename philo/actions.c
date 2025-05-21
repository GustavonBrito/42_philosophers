/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:49:01 by gustavo-lin       #+#    #+#             */
/*   Updated: 2025/05/20 23:37:02 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo);
void	sleep_philo(t_philo *philo);
void	die(t_philo *philo);
void	think(t_philo *philo);
void	*dead_scan(void *arg);

void think(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->m_write);
	printf("%ld %d is thinking\n", get_timestamp() - philo->rules->start_time, philo->id);
	pthread_mutex_unlock(&philo->rules->m_write);
};

void eat(t_philo *philo)
{
	// if (philo->last_meal - get_timestamp() >= philo->rules->time_to_die)
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
	pthread_mutex_unlock(&philo->rules->m_write);
	usleep(philo->rules->time_to_eat * 1000);
	philo->last_meal = get_timestamp();
	philo->meals++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void sleep_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->m_write);
	printf("%ld %d is sleeping\n", get_timestamp() - philo->rules->start_time, philo->id);
	pthread_mutex_unlock(&philo->rules->m_write);
	usleep(philo->rules->time_to_sleep * 1000);
}

void die(t_philo *philo)
{	
	pthread_mutex_lock(&philo->rules->m_write);
	printf("%ld %d: died\n", get_timestamp() - philo->rules->start_time, philo->id);
	pthread_mutex_unlock(&philo->rules->m_write);
}

void *dead_scan(void *arg)
{	
	t_philo *philo = (t_philo *)arg;
	//pthread_mutex_init(philo->rules.dead_philo, NULL);
	
	while (1)
	{
		sleep(5);
		printf("%ld\n", philo[2].last_meal);
		// if (philo->last_meal - get_timestamp() >= philo->rules->time_to_die)
		// {
		// 	//die(philo);
		// 	//pthread_mutex_lock(philo->rules->dead_philo);
		// 	//philo->rules->someone_died = 1;
		// 	//pthread_mutex_unlock(philo->rules->dead_philo);
		// 	return (NULL);
		// 	//Verificar melhor retorno depois e tambem todos os frees que é preciso fazer.
		// }
	}
}
